const AWS = require('aws-sdk')
const dynamodb = new AWS.DynamoDB()
const { repoFromItem, issueFromItem, pullRequestFromItem } = require('../entities')

const migrateReposIssuesPrs = async () => {
    let migrated = []
    try {
        const scanParams = {
            TableName: process.env.TABLE_NAME,
            FilterExpression: "#type IN (:repo, :issue, :pr)",
            ExpressionAttributeNames: {
                "#type": "Type"
            },
            ExpressionAttributeValues: {
                ':repo': { 'S': 'Repo' },
                ':issue': { 'S': 'Issue' },
                ':pr': { 'S': 'PullRequest' }
            }
        }
        let exclusiveStartKey = ''
        while (true) {
            if (exclusiveStartKey) {
                scanParams.exclusiveStartKey = exclusiveStartKey
            }
            const results = await dynamodb.scan(scanParams).promise()
            if (results.Items) {
                const repoPromises = results.Items.filter((item) => {
                    return item.Type.S === 'Repo'
                }). map((item) => { return updateRepo(item) })
                const issuePromises = results.Items.filter((item) => {
                    return item.Type.S === 'Issue'
                }). map((item) => { return updateIssue(item) })
                const pullRequestPromises = results.Items.filter((item) => {
                    return item.Type.S === 'PullRequest'
                }). map((item) => { return updatePullRequest(item) })
                const resolved = await Promise.all([...repoPromises, ...issuePromises, ...pullRequestPromises])
                migrated = migrated.concat(resolved)
            }
            if (results.LastEvaluatedKey) {
                exclusiveStartKey = results.LastEvaluatedKey
            } else {
                break
            }
        }
        console.log(`Finished migration of ${migrated.length} items`)
    } catch(error) {
        console.log('Error migrating items')
        console.log(error)
    }
}

const updateRepo = async (item) => {
    const repo = repoFromItem(item)
    return dynamodb.updateItem({
        TableName: process.env.TABLE_NAME,
        Key: repo.key(),
        UpdateExpression: "SET #gsi4pk = :gsi4pk, #gsi4sk = :gsi4sk, #gsi5pk = :gsi5pk, #gsi5sk = :gsi5sk",
        ExpressionAttributeNames: {
            '#gsi4pk': 'GSI4PK',
            '#gsi4sk': 'GSI4SK',
            '#gsi5pk': 'GSI5PK',
            '#gsi5sk': 'GSI5SK',
        },
        ExpressionAttributeValues: {
            ':gsi4pk': repo.gsi4pk(),
            ':gsi4sk': repo.gsi4sk(),
            ':gsi5pk': repo.gsi5pk(),
            ':gsi5sk': repo.gsi5sk(),
        }
    }).promise()
}

const updateIssue = async (item) => {
    const issue = issueFromItem(item)
    return dynamodb.updateItem({
        TableName: process.env.TABLE_NAME,
        Key: issue.key(),
        UpdateExpression: "SET #gsi4pk = :gsi4pk, #gsi4sk = :gsi4sk",
        ExpressionAttributeNames: {
            '#gsi4pk': 'GSI4PK',
            '#gsi4sk': 'GSI4SK',
        },
        ExpressionAttributeValues: {
            ':gsi4pk': issue.gsi4pk(),
            ':gsi4sk': issue.gsi4sk()
        }
    }).promise()
}

const updatePullRequest = async (item) => {
    const pullRequest = pullRequestFromItem(item)
    return dynamodb.updateItem({
        TableName: process.env.TABLE_NAME,
        Key: pullRequest.key(),
        UpdateExpression: "SET #gsi5pk = :gsi5pk, #gsi5sk = :gsi5sk",
        ExpressionAttributeNames: {
            '#gsi5pk': 'GSI5PK',
            '#gsi5sk': 'GSI5SK',
        },
        ExpressionAttributeValues: {
            ':gsi5pk': pullRequest.gsi5pk(),
            ':gsi5sk': pullRequest.gsi5sk()
        }
    }).promise()
}

module.exports = {
    migrateReposIssuesPrs
}