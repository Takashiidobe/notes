const { makeHandler } = require('./utils')
const { getPullRequest } = require('../data')
const { PullRequest } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    pathParameters: {
      type: 'object',
      properties: {
        ownerName: { type: 'string' },
        repoName: { type: 'string' },
        pullRequestNumber: { type: 'number' }
      },
      required: [ 'ownerName', 'repoName', 'pullRequestNumber' ]
    }
  },
  required: [ 'pathParameters' ]
}

const handler = async event => {
  const pullRequest_obj = new PullRequest({
    ownerName: event.pathParameters.ownerName,
    repoName: event.pathParameters.repoName,
    pullRequestNumber: event.pathParameters.pullRequestNumber
  })
  const { pullRequest, error } = await getPullRequest({ pullRequest: pullRequest_obj })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ pullRequest })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })