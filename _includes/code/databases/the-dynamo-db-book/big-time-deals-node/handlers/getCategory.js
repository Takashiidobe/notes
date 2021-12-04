const { makeHandler } = require('./utils')
const { getCategoryAndLatestDealsForCategory } = require('../data')
const { Category, getCategoryName } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    pathParameters: {
      type: 'object',
      properties: {
        name: { type: 'string' }
      },
      required: [ 'name' ]
    }
  },
  required: [ 'pathParameters' ]
}

const handler = async event => {
  const name = getCategoryName(event.pathParameters.name)
  const category_obj = new Category({
    name
  })
  const { category, deals, error } = await getCategoryAndLatestDealsForCategory({ category: category_obj })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ category, deals })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })