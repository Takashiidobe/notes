# DynamoDB E-commerce example

This repo contains example code for an e-commerce data model in DynamoDB. It contains Customers, Orders, and Order Iems. It is intended to accompany Chapter 19 of the DynamoDB Book.

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
service: e-commerce-node
stage: prod
region: us-east-1
stack: e-commerce-node-prod
resources: 48
api keys:
 None
endpoints:
 POST - https://crh9dzck0l.execute-api.us-east-1.amazonaws.com/prod/customers
 POST - https://crh9dzck0l.execute-api.us-east-1.amazonaws.com/prod/customers/{username}/addresses
 DELETE - https://crh9dzck0l.execute-api.us-east-1.amazonaws.com/prod/customers/{username}/addresses/{name}
 POST - https://crh9dzck0l.execute-api.us-east-1.amazonaws.com/prod/customers/{username}/orders
 POST - https://crh9dzck0l.execute-api.us-east-1.amazonaws.com/prod/customers/{username}/orders/{orderId}/status
 GET - https://crh9dzck0l.execute-api.us-east-1.amazonaws.com/prod/customers/{username}/orders
 GET - https://crh9dzck0l.execute-api.us-east-1.amazonaws.com/prod/customers/{username}/orders/{orderId}
functions:
 createCustomer: e-commerce-node-prod-createCustomer
 editAddressForCustomer: e-commerce-node-prod-editAddressForCustomer
 deleteAddressForCustomer: e-commerce-node-prod-deleteAddressForCustomer
 createOrder: e-commerce-node-prod-createOrder
 updateStatusForOrder: e-commerce-node-prod-updateStatusForOrder
 getOrdersForCustomer: e-commerce-node-prod-getOrdersForCustomer
 getOrder: e-commerce-node-prod-getOrder
```


Copy and paste the base URL (`https://<apiGWId>.execute-api.<region>.amazonaws.com/prod`) into an environment variable:

```bash
export BASE_URL=<yourBaseURL>
```

# Repo structure

There are four parts to consider in this repository:

1. `serverless.yml`: This is the file for deploying the application using the [Serverless Framework](https://github.com/serverless/serverless). It contains the provisioning logic for the DynamoDB table as well as the AWS Lambda functions and API Gateway endpoint configuration.

2. `entities`: This is where the code for interacting with our application objects live. Objects are things like Customers, Orders, and OrderItems. Each object has a `toItem()` method that knows how to create the DynamoDB representation of the item, including indexing attributes like `PK` and `SK` as well as formatting to include type information about each attribute for DynamoDB.

    For each object, there is also an `<object>FromItem` method (e.g. `customerFromItem`, `orderFromItem`) that can parse a DynamoDB item back into the application object.

3. `data`: This directory contains the code for saving, reading, updating, and deleting our objects as items in DynamoDB. Each module in the directory contains a particular use case, such as "getCustomer" or "updateStatusForOrder". The main function in the module will perform the necessary operations in DynamoDB and return the resulting objects or an error.

4. `handlers`: This directory contains the code that will be used as handlers for our Lambda functions. Generally, these handlers validate the incoming request payload, instantiate the core object to be retrieve or manipulated in the request, and pass it to the proper method in the `data` directory for handling. It then receives a response or an error to return to the user.

# Access patterns

There are two 'core' entities in this application: Customers and Orders. Within these categories, there are a few access patterns for the core entities:

**Customers:**

- **Create Customer:** Available at `POST /customers`. Used to create a new Customer. Will throw an error if either the username or email address used is already in our system.
- **Add Mailing Address to Customer:** Available at `POST /customers/<username>/addresses`. Used to add a new named address (e.g. "Home", "Work", etc.) to an existing Customer. Will overwrite any existing address with the same name.
- **Delete Mailing Address for Customer:** Available at `DELETE /customers/<username>/addresses/<addressName>`. used to remove an existing address. Will not throw an error if the address does not exist but will throw an error if the Customer does not exist.
- **Get Customer:** Available at `GET /customers/<username>`. Retrieve a Customer and core data. Will include all saved mailing address for Customer.

**Orders:**

- **CreateOrder:** Available at `POST /customer/<username>/orders`. Used to create a new Order for a Customer. Will throw an error if the Customer does not exist.
- **UpdateStatusForOrder:** Available at `POST /customer/<username>/orders/<orderId>`. Used to update the status of an existing Order (e.g. "Placed" --> "Shipped" --> "Delivered").
- **GetOrdersForUser:** Available at `GET /customer/<username>/orders`. Used to retrieve all Orders for a Customer. Will retrieve both the Customer object as well as all Order objects for the Customer. This includes only the summary of the Order (e.g. date placed, status, total amount, number of items) but not specific detail on each item in the Order.
- **GetOrder:** Available at `GET /customer/<username>/orders/<orderId>`. Used to retrieve a specific Order for a Customer. Will retrieve both the Order summary object as well as the OrderItems objects for specific detail about each item in the Order.

**Caveat:** There is no authorization in this application as it increases the scope without adding useful DynamoDB detail. When using this in your application, you would authenticate each request and verify that the requesting Customer has access to the Customer or Order data it is requesting.

# Walkthrough

If you want to walk through the endpoints and request flow, there is a Postman collection at `ecommerce-postman.json` in this repository. Import it into your Postman client and set the `baseUrl` property in your environment to your deployed endpoint (`https://<restApiId>.execute-api.<region>.amazonaws.com/prod`). There are example requests with paths and payloads for all eight endpoints to use.

# Table structure

The basic table structure is as follows:

- **Primary key:** `PK` & `SK`
- **GSI1 secondary index:** `GSI1PK` & `GSI1SK`

And the entity chart for the table is:

| **Entity**    | **PK**                          | **SK**                          | **GSI1PK**        | **GSI1SK**        |
|---------------|---------------------------------|---------------------------------|-------------------|-------------------|
| Customer      | `CUSTOMER#<Username>`           | `CUSTOMER#<Username>`           |                   |                   |
| CustomerEmail | `CUSTOMEREMAIL#<Email>`         | `CUSTOMEREMAIL#<Email>`         |                   |                   |
| Order         | `CUSTOMER#<Username>`           | `#ORDER#<OrderId>`              | `ORDER#<OrderId>` | `ORDER#<OrderId>` |
| OrderItem     | `ORDER#<OrderId>#ITEM#<ItemId>` | `ORDER#<OrderId>#ITEM#<ItemId>` | `ORDER#<OrderId>` | `Item#<ItemId>`   |