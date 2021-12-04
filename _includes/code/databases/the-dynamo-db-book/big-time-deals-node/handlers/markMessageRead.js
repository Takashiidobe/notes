const { makeHandler } = require('./utils')
const { markMessageRead } = require('../data')
const { Message } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    pathParameters: {
      type: 'object',
      properties: {
        username: { type: 'string' },
        messageId: { type: 'string' },
      },
      required: [ 'username', 'messageId' ]
    }
  },
  required: [ 'pathParameters' ]
}

const handler = async event => {
  const message = new Message({
    username: event.pathParameters.username,
    messageId: event.pathParameters.messageId
  })
  const { error } = await markMessageRead({ message })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ message: 'OK'})
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })