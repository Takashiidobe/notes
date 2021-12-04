const { makeHandler } = require('./utils')
const { getCommentsForPullRequest } = require('../data')
const { PullRequestComment } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    pathParameters: {
      type: 'object',
      properties: {
        ownerName: { type: 'string' },
        repoName: { type: 'string' },
        pullRequestNumber: { type: 'integer' }
      },
      required: [ 'ownerName', 'repoName', 'pullRequestNumber' ]
    }
  },
  required: [ 'pathParameters' ]
}

const handler = async event => {
  const pullRequestComment = new PullRequestComment({
    ownerName: event.pathParameters.ownerName,
    repoName: event.pathParameters.repoName,
    targetNumber: event.pathParameters.pullRequestNumber
  })
  const { pullRequestComments, error } = await getCommentsForPullRequest({ pullRequestComment })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ pullRequestComments })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })