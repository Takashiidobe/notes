const { makeHandler } = require('./utils')
const { getOrganization } = require('../data')
const { Organization } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    pathParameters: {
      type: 'object',
      properties: {
        organizationName: { type: 'string' }
      },
      required: [ 'organizationName' ]
    }
  },
  required: [ 'pathParameters' ]
}

const handler = async event => {
  const organization_obj = new Organization({
    organizationName: event.pathParameters.organizationName
  })
  const { organization, error } = await getOrganization({ organization: organization_obj })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ organization })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })