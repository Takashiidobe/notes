const AWS = require('aws-sdk')
const dynamodb = new AWS.DynamoDB()
const { userFromItem, organizationFromItem } = require('../entities')

const migrateAllAccounts = async () => {
    let accounts = []
    try {
        const scanParams = {
            TableName: process.env.TABLE_NAME,
            FilterExpression: "#type IN (:user, :org)",
            ExpressionAttributeNames: {
                "#type": "Type"
            },
            ExpressionAttributeValues: {
                ':user': { 'S': 'User' },
                ':org': { 'S': 'Organization' }
            }
        }
        let exclusiveStartKey = ''
        while (true) {
            if (exclusiveStartKey) {
                scanParams.exclusiveStartKey = exclusiveStartKey
            }
            const results = await dynamodb.scan(scanParams).promise()
            if (results.Items) {
                const promises = results.Items.map((item) => { return updateAccount(item) })
                await Promise.all(promises)
                accounts = accounts.concat(results.Items)
            }
            if (results.LastEvaluatedKey) {
                exclusiveStartKey = results.LastEvaluatedKey
            } else {
                break
            }
        }
        console.log(`Finished migration of ${accounts.length} accounts`)
    } catch(error) {
        console.log('Error migrating accounts')
        console.log(error)
    }
}

const updateAccount = async (item) => {
    const deserializer = item.Type.S === 'User' ? userFromItem : organizationFromItem
    const entity = deserializer(item)
    return dynamodb.updateItem({
        TableName: process.env.TABLE_NAME,
        Key: entity.key(),
        UpdateExpression: "SET #gsi1pk = :gsi1pk, #gsi1sk = :gsi1sk",
        ExpressionAttributeNames: {
            '#gsi1pk': 'GSI1PK',
            '#gsi1sk': 'GSI1SK',
        },
        ExpressionAttributeValues: {
            ':gsi1pk': entity.gsi1pk(),
            ':gsi1sk': entity.gsi1sk()
        }
    }).promise()
}

module.exports = {
    migrateAllAccounts
}