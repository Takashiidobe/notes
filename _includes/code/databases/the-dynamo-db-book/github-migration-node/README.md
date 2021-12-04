# DynamoDB GitHub metadata example

This repo contains example code for replicating the GitHub metadata backend using DynamoDB. It contains 13 different entities, including Users, Organizations, Repos, Issues, and Pull Requests. It is intended to accompany Chapters 21 and 22 of the DynamoDB Book.

## Table of Contents

- [Setup](#setup)
- [Repo structure](#repo-structure)
- [Access patterns](#access-patterns)
- [Walkthrough](#walkthrough)
- [Table structure](#table-structure)

# Setup

**NOTE:** 

There are two important notes about this application, particularly if you're coming from the previous `github-node` migration from Chapter 21.

1. You'll need to perform your first deploy in this repo in two steps. CloudFormation only allows you to create one new secondary index in each update, and this service has two new indexes.

  First, comment out the `GSI5` index at the bottom of the `serverless.yml` and deploy. After that's successful, uncomment it and deploy again.

2. CloudFormation has a limit of 200 resources per stack, and each HTTP endpoint uses 5-6 resources. As such, we ran out of room at the end. I've commented out some functions and endpoints from the previous chapter that weren't relevant to the migration here.

**End Note**

This example uses [AWS Lambda](https://aws.amazon.com/lambda/) for compute, and it uses the [Serverless Framework](https://github.com/serverless/serverless) to deploy the DynamoDB table, AWS Lambda functions, and API Gateway endpoints.

If you have Node.js and NPM installed, you can install the Serverless Framework with the following command:

```bash
npm install -g serverless
```

Then, install the dependencies for this service:

```bash
npm i
```

Finally, deploy the service to AWS:

```bash
serverless deploy
```

After the deploy, Serverless will print out the URLs for your endpoints:

```bash
Service Information
service: github-node
stage: prod
region: us-east-1
stack: github-node-prod
resources: 100
api keys:
  None
endpoints:
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos
  GET - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/issues
  GET - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/issues
  GET - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/issues/{issueNumber}
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/issues/{issueNumber}
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/issues/{issueNumber}/comments
  GET - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/issues/{issueNumber}/comments
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/issues/{issueNumber}/reactions
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/pulls
  GET - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/pulls
  GET - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/pulls/{pullRequestNumber}
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/pulls/{pullRequestNumber}
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/pulls/{pullRequestNumber}/comments
  GET - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/pulls/{pullRequestNumber}/comments
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/pulls/{pullRequestNumber}/reactions
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/stars
  GET - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/stars
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/forks
  GET - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/forks
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/repos/{ownerName}/{repoName}/comments/{commentId}/reactions
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/users
  GET - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/users/{username}
  GET - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/users/{username}/repos
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/users/{username}/payment
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/organizations
  GET - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/organizations/{organizationName}
  GET - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/organizations/{organizationName}/members
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/organizations/{organizationName}/members
  GET - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/organizations/{organizationName}/repos
  POST - https://i8tpsmohvd.execute-api.us-east-1.amazonaws.com/prod/organizations/{organizationName}/payment
functions:
  createRepo: github-node-prod-createRepo
  getRepo: github-node-prod-getRepo
  addIssueToRepo: github-node-prod-addIssueToRepo
  getRepoAndIssues: github-node-prod-getRepoAndIssues
  getIssue: github-node-prod-getIssue
  updateIssue: github-node-prod-updateIssue
  addCommentToIssue: github-node-prod-addCommentToIssue
  getCommentsForIssue: github-node-prod-getCommentsForIssue
  addReactionToIssue: github-node-prod-addReactionToIssue
  addPullRequestToRepo: github-node-prod-addPullRequestToRepo
  getRepoAndPullRequests: github-node-prod-getRepoAndPullRequests
  getPullRequest: github-node-prod-getPullRequest
  updatePullRequest: github-node-prod-updatePullRequest
  addCommentToPullRequest: github-node-prod-addCommentToPullRequest
  getCommentsForPullRequest: github-node-prod-getCommentsForPullRequest
  addReactionToPullRequest: github-node-prod-addReactionToPullRequest
  addStarToRepo: github-node-prod-addStarToRepo
  getStargazersForRepo: github-node-prod-getStargazersForRepo
  forkRepo: github-node-prod-forkRepo
  getForksForRepo: github-node-prod-getForksForRepo
  addReactionToComment: github-node-prod-addReactionToComment
  createUser: github-node-prod-createUser
  getUser: github-node-prod-getUser
  getUserAndRepos: github-node-prod-getUserAndRepos
  updatePaymentPlanForUser: github-node-prod-updatePaymentPlanForUser
  createOrganization: github-node-prod-createOrganization
  getOrganization: github-node-prod-getOrganization
  getOrganizationAndMembers: github-node-prod-getOrganizationAndMembers
  addMemberToOrganization: github-node-prod-addMemberToOrganization
  getOrganizationAndRepos: github-node-prod-getOrganizationAndRepos
  updatePaymentPlanForOrganization: github-node-prod-updatePaymentPlanForOrganization
layers:
  None
```


Copy and paste the base URL (`https://<restApiId>.execute-api.<region>.amazonaws.com/prod`) into an environment variable:

```bash
export BASE_URL=<yourBaseURL>
```

# Repo structure

There are four parts to consider in this repository:

1. `serverless.yml`: This is the file for deploying the application using the [Serverless Framework](https://github.com/serverless/serverless). It contains the provisioning logic for the DynamoDB table as well as the AWS Lambda functions and API Gateway endpoint configuration.

2. `entities`: This is where the code for interacting with our application objects live. Objects are things like Users, Organizations, and Repos. Each object that will be stored in DynamoDB has a `toItem()` method that knows how to create the DynamoDB representation of the item, including indexing attributes like `PK` and `SK` as well as formatting to include type information about each attribute for DynamoDB.

    For each object that will be read from DynamoDB, there is also an `<object>FromItem` method (e.g. `repoFromItem`, `userFromItem`) that can parse a DynamoDB item back into the application object. Note that a few entity types (e.g. all the Reaction types) are only used for tracking purposes and are never read from DynamoDB. Thus, there is no `issueReactionFromItem` method.

3. `data`: This directory contains the code for saving, reading, updating, and deleting our objects as items in DynamoDB. Each module in the directory contains a particular use case, such as "createRepo" or "getRepoAndIssues". The main function in the module will perform the necessary operations in DynamoDB and return the resulting objects or an error.

4. `handlers`: This directory contains the code that will be used as handlers for our Lambda functions. Generally, these handlers validate the incoming request payload, instantiate the core object to be retrieve or manipulated in the request, and pass it to the proper method in the `data` directory for handling. It then receives a response or an error to return to the user.

**Caveat:** There is no authorization in this application as it increases the scope without adding useful DynamoDB detail. When using this in your application, you would authenticate each request and verify that the requesting User has access to the User or Message data it is requesting.

# Walkthrough

If you want to walk through the endpoints and request flow, there is a Postman collection at `github-postman.json` in this repository. Import it into your Postman client and set the `baseUrl` property in your environment to your deployed endpoint (`https://<restApiId>.execute-api.<region>.amazonaws.com/prod`). There are example requests with paths and payloads for all endpoints to use.

# Table structure

The basic table structure is as follows:

- **Primary key:** `PK` & `SK`
- **GSI1 secondary index:** `GSI1PK` & `GSI1SK`
- **GSI2 secondary index:** `GSI2PK` & `GSI2SK`
- **GSI3 secondary index:** `GSI3PK` & `GSI3SK`
- **GSI4 secondary index:** `GSI4PK` & `GSI4SK`
- **GSI5 secondary index:** `GSI5PK` & `GSI5SK`

And the entity chart for the table is:

| **Entity**          | **PK**                                                                 | **SK**                                                                 | **GSI1PK**                    | **GSI1SK**                         | **GSI2PK**                        | **GSI2SK**                     | **GSI3PK**                   | **GSI3SK**                   |
|---------------------|------------------------------------------------------------------------|------------------------------------------------------------------------|-------------------------------|------------------------------------|-----------------------------------|--------------------------------|------------------------------|------------------------------|
| Repo (Not forked)   | `REPO#<OwnerName>#<RepoName>`                                          | `REPO#<OwnerName>#<RepoName>`                                          | `REPO#<OwnerName>#<RepoName>` | `REPO#<OwnerName>#<RepoName>`      | `REPO#<OwnerName>#<RepoName>`     | `#REPO#<OwnerName>#<RepoName>` | `ACCOUNT#<OwnerName>`        | `#<UpdatedAt>`               |
| Repo (forked)       | SAME AS ABOVE                                                          | SAME AS ABOVE                                                          | SAME AS ABOVE                 | SAME AS ABOVE                      | `REPO#<OriginalOwner>#<RepoName>` | `FORK#<OwnerName>`             | SAME AS ABOVE                | SAME AS ABOVE                |
| Star                | `REPO#<OwnerName>#<RepoName>`                                          | `STAR#<Username>`                                                      |                               |                                    |                                   |                                |                              |                              |
| Issue               | `REPO#<OwnerName>#<RepoName>`                                          | `ISSUE#<ZeroPaddedIssueNumber>`                                        |                               |                                    |                                   |                                |                              |                              |
| IssueComment        | `ISSUECOMMENT#<OwnerName>#<RepoName>#<ZeroPaddedIssueNumber>`          | `ISSUECOMMENT#<CommentId>`                                             |                               |                                    |                                   |                                |                              |                              |
| IssueReaction       | `ISSUEREACTION#<OwnerName>#<RepoName>#<IssueNumber>#<ReactingUser>`     | `ISSUEREACTION#<OwnerName>#<RepoName>#<IssueNumber>#<ReactingUser>`    |                               |                                    |                                   |                                |                              |                              |
| PullRequest         | `PR#<OwnerName>#<RepoName>#<ZeroPaddedPullRequestNumber>`              | `PR#<OwnerName>#<RepoName>#<ZeroPaddedPullRequestNumber>`              | `REPO#<OwnerName>#<RepoName>` | `PR#<ZeroPaddedPullRequestNumber>` |                                   |                                |                              |                              |
| PullRequestComment  | `PRCOMMENT#<OwnerName>#<RepoName>#<ZeroPaddedPullRequestNumber>`       | `PRCOMMENT#<CommentId>`                                                |                               |                                    |                                   |                                |                              |                              |
| PullRequestReaction | `PRREACTION#<OwnerName>#<RepoName>#<PullRequestNumber>#<ReactingUser>` | `PRREACTION#<OwnerName>#<RepoName>#<PullRequestNumber>#<ReactingUser>` |                               |                                    |                                   |                                |                              |                              |
| CommentReaction     | `COMMENTREACTION#<OwnerName>#<RepoName>#<CommentId>#<ReactingUser>`    | `COMMENTREACTION#<OwnerName>#<RepoName>#<CommentId>#<ReactingUser>`    |                               |                                    |                                   |                                |                              |                              |
| Organization        | `ACCOUNT#<OrganizationName>`                                           | `ACCOUNT#<OrganizationName>`                                           |                               |                                    |                                   |                                | `ACCOUNT#<OrganizationName>` | `ACCOUNT#<OrganizationName>` |
| User                | `ACCOUNT#<Username>`                                                   | `ACCOUNT#<Username>`                                                   |                               |                                    |                                   |                                | `ACCOUNT#<Username>`         | `ACCOUNT#<Username>`         |
| Membership          | `ACCOUNT#<OrganizationName>`                                           | `MEMBERSHIP#<Username>`                                                |                               |                                    |                                   |                                |                              |                              |
| PaymentPlans        | N/A -- attached directly to Users and Organizations                    |                                                                        |                               |                                    |                                   |                                |                              |                              |