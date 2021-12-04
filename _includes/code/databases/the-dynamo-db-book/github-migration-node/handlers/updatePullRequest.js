const { makeHandler } = require('./utils')
const { updatePullRequest } = require('../data')
const { PullRequest, PR_STATUSES } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        title: { type: 'string' },
        content: { type: 'string' },
        status: {
          type: 'string',
          enum: PR_STATUSES
        }
      },
      required: [ 'title', 'content', 'status']
    },
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
    pullRequestNumber: event.pathParameters.pullRequestNumber,
    title: event.body.title,
    content: event.body.content,
    status: event.body.status
  })
  const { pullRequest, error } = await updatePullRequest({ pullRequest: pullRequest_obj })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ pullRequest })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })