const { makeHandler } = require('./utils')
const { createRepo } = require('../data')
const { Repo } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        ownerName: { type: 'string' },
        repoName: { type: 'string' },
        description: { type: 'string' },
      },
      required: [ 'ownerName', 'repoName' ]
    }
  },
  required: [ 'body' ]
}

const handler = async event => {
  const repo = new Repo({
    ownerName: event.body.ownerName,
    repoName: event.body.repoName,
    description: event.body.description,
  })
  const { error } = await createRepo(repo)
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ repo })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })