# DynamoDB Session Store

This repo contains example code for creating a Session Store in DynamoDB. It is intended to accompany Chapter 18 of the DynamoDB Book.

## Table of Contents

- [Setup](#setup)
- [Usage](#usage)

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
service: session-store-node
stage: prod
region: us-east-1
stack: session-store-node-prod
resources: 23
api keys:
 None
endpoints:
 POST - https://lrv84vh673.execute-api.us-east-1.amazonaws.com/prod/sessions
 GET - https://lrv84vh673.execute-api.us-east-1.amazonaws.com/prod/sessions
 DELETE - https://lrv84vh673.execute-api.us-east-1.amazonaws.com/prod/sessions/{username}
functions:
 createSession: session-store-node-prod-createSession
 getSession: session-store-node-prod-getSession
 deleteSessionsForUser: session-store-node-prod-deleteSessionsForUser
layers:
 None
```

Copy and paste the base URL (`https://<apiGWId>.execute-api.<region>.amazonaws.com/prod`) into an environment variable:

```bash
export BASE_URL=<yourBaseURL>
```

# Usage

There are three endpoints deployed in this service:

1. `CreateSession`: Create a new session. Available by making a `POST` request to `/sessions`
2. `GetSession`: Retrieve the username for a given session. Available by making a `GET` request to `/sessions` with an `Authorization` token of `Bearer <Token>`. 
3. `DeleteSessionsForUser`: Delete all available sessions for a given user. Available by making a `DELETE` request to `/sessions/<username>` with an `Authorization` token of `Bearer <Token>`.

You can test them out with the following steps.

### 1. Create a session

Execute the following `curl` request to create a new session:

```bash
curl -X POST \
    ${BASE_URL}/sessions \
    -H "Content-Type: application/json" \
    --data '{ "username": "myuser", "password": "Password1" }'
```

This will return a sessionId:

```
{"sessionId":"1f5fc757-0a05-42f7-9cf8-09c2752da98a"}
```

Note that this is just an example, so there's no verification of the username and password. In your application, you will want to add that.

### 2. Get a session

You can verify a session by running the following command:

```bash
curl -X GET \
    ${BASE_URL}/sessions \
    -H "Content-Type: application/json" \
    -H "Authorization: Bearer <Token>"
```

Substitute the sessionId you just received in the `<Token>` spot.

You should get a reponse that shows the username for the token:

```
{"username":"myuser"}
```

### 3. Delete all sessions for a user

You can delete all existing sessions for a user with the following command:

```bash
curl -X DELETE \
    ${BASE_URL}/sessions/<username> \
    -H "Content-Type: application/json" \
    -H "Authorization: Bearer <Token>"
```

Be sure to replace `<username>` with the username you used to create the session, and `<Token>` with your sessionId.

You should see the following response:

```
{"username":"myuser"}
```

Now try running the GetSession endpoint again. You should get a message indicating the session does not exist:

```
{"error":"Session does not exist."}
```