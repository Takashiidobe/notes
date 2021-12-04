const { makeHandler } = require('./utils')
const { deleteSessionsForUser, getSession } = require('../data')

const inputSchema = {
  type: 'object',
  properties: {
    pathParameters: {
      type: 'object',
      properties: {
        'username': { type: 'string' }
      },
      required: [ 'username' ]
    },
    headers: {
      type: 'object',
      properties: {
        Authorization: { type: 'string' }
      },
      required: ['Authorization']
    }
  },
  required: [ 'pathParameters', 'headers' ]
}

const handler = async event => {
  const sessionId = event.headers.Authorization.toLowerCase().replace('bearer ', '')
  let { username, error } = await getSession({ sessionId })
  // User is trying to delete someone else's tokens
  if (username !== event.pathParameters.username) {
    error = 'Invalid session.'
  }
  if (!error) {
    error = await deleteSessionsForUser({ username })
  }
  const statusCode = error ? 401 : 200 
  return {
    statusCode, 
    body: JSON.stringify({
      username,
      error
    })
  }
}

module.exports.deleteSessionsForUser = makeHandler({ handler, inputSchema })