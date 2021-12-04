const { makeHandler } = require('./utils')
const { addMemberToOrganization } = require('../data')
const { Membership, ROLES } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        username: { type: 'string' },
        role: { 
          type: 'string',
          enum: ROLES
        }
      },
      required: [ 'username', 'role' ]
    },
    pathParameters: {
      type: 'object',
      properties: {
        organizationName: { type: 'string' }
      },
      required: ['organizationName']
    }
  },
  required: [ 'body' ]
}

const handler = async event => {
  const membership = new Membership({
    organizationName: event.pathParameters.organizationName,
    username: event.body.username,
    role: event.body.role
  })
  const { error } = await addMemberToOrganization(membership)
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ membership })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })