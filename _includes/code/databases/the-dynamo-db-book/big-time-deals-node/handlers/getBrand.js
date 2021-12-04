const { makeHandler } = require('./utils')
const { getBrandAndLatestDealsForBrand } = require('../data')
const { Brand } = require('../entities')

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
  const brand_obj = new Brand({
    name: event.pathParameters.name
  })
  const { brand, deals, error } = await getBrandAndLatestDealsForBrand({ brand: brand_obj })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ brand, deals })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })