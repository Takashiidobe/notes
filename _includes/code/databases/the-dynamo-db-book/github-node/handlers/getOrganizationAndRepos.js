const { makeHandler } = require('./utils')
const { getOrganizationAndRepos } = require('../data')
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
  const { organization, repos, error } = await getOrganizationAndRepos({ organization: organization_obj })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ organization, repos })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })