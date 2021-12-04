const { makeHandler } = require('./utils')
const { getUserAndGists} = require('../data')
const { User } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    pathParameters: {
      type: 'object',
      properties: {
        username: { type: 'string' }
      },
      required: [ 'username' ]
    }
  },
  required: [ 'pathParameters' ]
}

const handler = async event => {
  const user_obj = new User({
    username: event.pathParameters.username
  })
  const { user, gists, error } = await getUserAndGists({ user: user_obj })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ user, gists })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })