const { makeHandler } = require('./utils')
const { updateCategory } = require('../data')
const { Category, getCategoryName } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        featuredDeals: {
          type: 'array',
          items: {
            type: 'object',
            properties: {
              dealId: { type: 'string' },
              title: { type: 'string' },
              link: { type: 'string' },
              price: { type: 'number' },
              category: { type: 'string' },
              brand: { type: 'string' }
            },
            required: ['dealId', 'title', 'link', 'price', 'category', 'brand']
          },
          minItems: 1
        }
      },
      required: [ 'featuredDeals' ]
    },
    pathParameters: {
      type: 'object',
      properties: {
        name: { type: 'string' },
      },
      required: [ 'name' ]
    }
  },
  required: [ 'body', 'pathParameters' ]
}

const handler = async event => {
  const name = getCategoryName(event.pathParameters.name)
  const category = new Category({
    name,
    featuredDeals: event.body.featuredDeals,
  })
  const { error } = await updateCategory({ category })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ category })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })