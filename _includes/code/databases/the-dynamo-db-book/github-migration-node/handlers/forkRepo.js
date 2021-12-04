const { makeHandler } = require('./utils')
const { forkRepo } = require('../data')
const { Repo } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        description: { type: 'string' },
        username: { type: 'string' }
      },
      required: [ 'description', 'username' ]
    },
    pathParameters: {
      type: 'object',
      properties: {
        ownerName: { type: 'string' },
        repoName: { type: 'string' },
      },
      required: [ 'ownerName', 'repoName' ]
    }
  },
  required: [ 'body' ]
}

const handler = async event => {
  const fork = new Repo({
    ownerName: event.body.username,
    repoName: event.pathParameters.repoName,
    description: event.body.description,
    forkOwner: event.pathParameters.ownerName
  })
  const { error } = await forkRepo(fork)
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ fork })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })