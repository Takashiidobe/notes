const { makeHandler } = require('./utils')
const { getMessagesForUser } = require('../data')
const { Message } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    pathParameters: {
      type: 'object',
      properties: {
        username: { type: 'string' }
      },
      required: [ 'username' ]
    },
  },
  required: [ 'pathParameters' ]
}

const handler = async event => {
  const message = new Message({
    username: event.pathParameters.username
  })
  const unread = event.queryStringParameters && event.queryStringParameters.unread ? event.queryStringParameters.unread === 'true' : false
  const { messages, error } = await getMessagesForUser({ message, unread })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ messages })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })