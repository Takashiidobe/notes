const { makeHandler } = require('./utils')
const { createSession } = require('../data')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        username: { type: 'string' },
        password: { type: 'string' },
      },
      required: ['username', 'password']
    }
  }
}

const handler = async event => {
  // authenticate username & password here ...

  const { sessionId, error } = await createSession({ username: event.body.username })
  const statusCode = error ? 500 : 200
  return {
    statusCode: statusCode,
    body: JSON.stringify({
      sessionId,
      error
    })
  }
}

module.exports.createSession = makeHandler({ handler, inputSchema })