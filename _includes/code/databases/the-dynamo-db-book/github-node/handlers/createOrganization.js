const { makeHandler } = require('./utils')
const { createOrganization } = require('../data')
const { Organization } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        organizationName: { type: 'string' },
        ownerName: { type: 'string' }
      },
      required: [ 'organizationName', 'ownerName' ]
    }
  },
  required: [ 'body' ]
}

const handler = async event => {
  const organization = new Organization({
    organizationName: event.body.organizationName,
    ownerName: event.body.ownerName
  })
  const { error } = await createOrganization(organization)
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ organization })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })