# DynamoDB Big Time Deals example

This repo contains example code for an online deals site using DynamoDB. It contains 12 different entities, including Deals, Brands, Categories, Users, and Messages. It is intended to accompany Chapter 20 of the DynamoDB Book.

## Table of Contents

- [Setup](#setup)
- [Repo structure](#repo-structure)
- [Access patterns](#access-patterns)
- [Walkthrough](#walkthrough)
- [Table structure](#table-structure)

# Setup

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
service: big-time-deals-node
stage: prod
region: us-east-1
stack: big-time-deals-node-prod
resources: 100
api keys:
  None
endpoints:
  POST - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/deals
  GET - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/deals/{dealId}
  POST - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/brands
  GET - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/brands
  GET - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/brands/{name}
  POST - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/brands/{name}/likes/{username}
  POST - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/brands/{name}/watches/{username}
  POST - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/categories/{name}
  GET - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/categories/{name}
  POST - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/categories/{name}/likes/{username}
  POST - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/categories/{name}/watches/{username}
  POST - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/frontpage
  GET - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/frontpage
  POST - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/editorschoice
  GET - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/editorschoice
  POST - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/users
  GET - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/users/{username}
  GET - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/users/{username}/messages
  POST - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/users/{username}/messages/{messageId}
  POST - https://zbyhhyvchc.execute-api.us-east-1.amazonaws.com/prod/hotdealblast
functions:
  createDeal: big-time-deals-node-prod-createDeal
  getDeal: big-time-deals-node-prod-getDeal
  createBrand: big-time-deals-node-prod-createBrand
  listBrands: big-time-deals-node-prod-listBrands
  getBrand: big-time-deals-node-prod-getBrand
  likeBrandForUser: big-time-deals-node-prod-likeBrandForUser
  watchBrandForUser: big-time-deals-node-prod-watchBrandForUser
  updateCategory: big-time-deals-node-prod-updateCategory
  getCategory: big-time-deals-node-prod-getCategory
  likeCategoryForUser: big-time-deals-node-prod-likeCategoryForUser
  watchCategoryForUser: big-time-deals-node-prod-watchCategoryForUser
  updateFrontPage: big-time-deals-node-prod-updateFrontPage
  getFrontPage: big-time-deals-node-prod-getFrontPage
  updateEditorsChoice: big-time-deals-node-prod-updateEditorsChoice
  getEditorsChoice: big-time-deals-node-prod-getEditorsChoice
  createUser: big-time-deals-node-prod-createUser
  getUser: big-time-deals-node-prod-getUser
  getMessagesForUser: big-time-deals-node-prod-getMessagesForUser
  markMessageRead: big-time-deals-node-prod-markMessageRead
  sendHotDealToAllUsers: big-time-deals-node-prod-sendHotDealToAllUsers
  streamHandler: big-time-deals-node-prod-streamHandler
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

2. `entities`: This is where the code for interacting with our application objects live. Objects are things like Deals, Brands, Categories, and Users. Each object has a `toItem()` method that knows how to create the DynamoDB representation of the item, including indexing attributes like `PK` and `SK` as well as formatting to include type information about each attribute for DynamoDB.

    For each object, there is also an `<object>FromItem` method (e.g. `dealFromItem`, `userFromItem`) that can parse a DynamoDB item back into the application object.

3. `data`: This directory contains the code for saving, reading, updating, and deleting our objects as items in DynamoDB. Each module in the directory contains a particular use case, such as "createDeal" or "getBrandAndLatestDealsForBrand". The main function in the module will perform the necessary operations in DynamoDB and return the resulting objects or an error.

4. `handlers`: This directory contains the code that will be used as handlers for our Lambda functions. Generally, these handlers validate the incoming request payload, instantiate the core object to be retrieve or manipulated in the request, and pass it to the proper method in the `data` directory for handling. It then receives a response or an error to return to the user.

**Caveat:** There is no authorization in this application as it increases the scope without adding useful DynamoDB detail. When using this in your application, you would authenticate each request and verify that the requesting User has access to the User or Message data it is requesting.

# Walkthrough

If you want to walk through the endpoints and request flow, there is a Postman collection at `big-time-deals-postman.json` in this repository. Import it into your Postman client and set the `baseUrl` property in your environment to your deployed endpoint (`https://<restApiId>.execute-api.<region>.amazonaws.com/prod`). There are example requests with paths and payloads for all endpoints to use.

# Table structure

The basic table structure is as follows:

- **Primary key:** `PK` & `SK`
- **GSI1 secondary index:** `GSI1PK` & `GSI1SK`
- **GSI2 secondary index:** `GSI2PK` & `GSI2SK`
- **GSI3 secondary index:** `GSI3PK` & `GSI3SK`
- **UserIndex secondary index:** `UserIndex`

And the entity chart for the table is:

| **Entity**        | **PK**                                   | **SK**                                   | **GSI1PK**                                   | **GSI1SK**                                    | **GSI2PK**                               | **GSI2SK**      | **GSI3PK**                                     | **GSI3SK**      | **UserIndex**     |
|-------------------|------------------------------------------|------------------------------------------|----------------------------------------------|-----------------------------------------------|------------------------------------------|-----------------|------------------------------------------------|-----------------|-------------------|
| Deal              | `DEAL#<DealId>`                          | `DEAL#<DealId>`                          | `DEALS#<TruncatedTimestamp>`                 | `DEAL#<DealId>`                               | `BRAND#<BrandName>#<TruncatedTimestamp>` | `DEAL#<DealId>` | `CATEGORY#<CategoryName>#<TruncatedTimestamp>` | `DEAL#<DealId>` |                   |
| Brand             | `BRAND#<BrandName>`                      | `BRAND#<BrandName>`                      |                                              |                                               |                                          |                 |                                                |                 |                   |
| BrandsContainer   | `BRANDS`                                 | `BRANDS`                                 |                                              |                                               |                                          |                 |                                                |                 |                   |
| Category          | `CATEGORY#<CategoryName>`                | `CATEGORY#<CategoryName>`                |                                              |                                               |                                          |                 |                                                |                 |                   |
| FrontPage         | `FRONTPAGE`                              | `FRONTPAGE`                              |                                              |                                               |                                          |                 |                                                |                 |                   |
| EditorsChoicePage | `EDITORPAGE`                             | `EDITORPAGE`                             |                                              |                                               |                                          |                 |                                                |                 |                   |
| User              | `USER#<Username>`                        | `USER#<Username>`                        |                                              |                                               |                                          |                 |                                                |                 | `USER#<Username>` |
| Message           | `MESSAGES#<Username>`                    | `MESSAGES#<MessageId>`                   | `MESSAGES#<Username>` (if Message is unread) | `MESSAGES#<MessageId>` (if Message is Unread) |                                          |                 |                                                |                 |                   |
| BrandLike         | `BRANDLIKE#<BrandName>#<Username>        | `BRANDLIKE#<BrandName>#<Username>`       |                                              |                                               |                                          |                 |                                                |                 |                   |
| BrandWatch        | `BRANDWATCH#<BrandName>`                 | `USER#<Username>`                        |                                              |                                               |                                          |                 |                                                |                 |                   |
| CategoryLike      | `CATEGORYLIKE#<CategoryName>#<Username>` | `CATEGORYLIKE#<CategoryName>#<Username>` |                                              |                                               |                                          |                 |                                                |                 |                   |
| CategoryWatch     | `CATEGORYWATCH#<CategoryName>`           | `USER#<Username>`                        |                                              |                                               |                                          |                 |                                                |                 |                   |