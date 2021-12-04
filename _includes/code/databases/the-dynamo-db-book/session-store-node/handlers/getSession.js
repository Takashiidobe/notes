const { makeHandler } = require('./utils')
const { getSession } = require('../data')

const inputSchema = {
  type: 'object',
  properties: {
    headers: {
      type: 'object',
      properties: {
        Authorization: { type: 'string' }
      },
      required: ['Authorization']
    }
  },
  required: [ 'headers' ]
}

const handler = async event => {
  const sessionId = event.headers.Authorization.toLowerCase().replace('bearer ', '')
  const { username, error } = await getSession({ sessionId })
  const statusCode = error ? 401 : 200
  return {
    statusCode: statusCode,
    body: JSON.stringify({
      username,
      error
    })
  }
}

module.exports.getSession = makeHandler({ handler, inputSchema })