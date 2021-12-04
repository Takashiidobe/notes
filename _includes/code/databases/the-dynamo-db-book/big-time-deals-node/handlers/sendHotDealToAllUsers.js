const { makeHandler } = require('./utils')
const { sendHotDealToAllUsers } = require('../data')
const { User } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        subject: { type: 'string' },
        message: { type: 'string' },
        dealId: { type: 'string' }
      },
      required: ['subject', 'message', 'dealId']
    }
  },
  required: [ 'body' ]
}

const handler = async event => {
  const { users, error } = await sendHotDealToAllUsers({ subject: event.body.subject, message: event.body.message, dealId: event.body.dealId })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ users })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })