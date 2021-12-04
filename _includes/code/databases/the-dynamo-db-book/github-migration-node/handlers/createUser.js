const { makeHandler } = require('./utils')
const { createUser } = require('../data')
const { User } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        username: { type: 'string' },
        name: { type: 'string' },
        email: { type: 'string' },
      },
      required: [ 'username', 'name', 'email' ]
    }
  },
  required: [ 'body' ]
}

const handler = async event => {
  const user = new User({
    username: event.body.username,
    name: event.body.name,
    email: event.body.email
  })
  const { error } = await createUser(user)
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ user })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })