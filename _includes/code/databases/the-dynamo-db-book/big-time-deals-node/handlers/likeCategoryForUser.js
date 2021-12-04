const { makeHandler } = require('./utils')
const { likeCategoryForUser } = require('../data')
const { CategoryLike, getCategoryName } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    pathParameters: {
      type: 'object',
      properties: {
        name: { type: 'string' },
        username: { type: 'string' },
      },
      required: [ 'name', 'username' ]
    }
  },
  required: [ 'pathParameters' ]
}

const handler = async event => {
  const name = getCategoryName(event.pathParameters.name)
  const categoryLike = new CategoryLike({
    username: event.pathParameters.username,
    name
  })
  const { error } = await likeCategoryForUser({ categoryLike })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ message: 'OK' })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })