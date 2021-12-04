const { makeHandler } = require('./utils')
const { addCommentToPullRequest } = require('../data')
const { PullRequestComment } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        username: { type: 'string' },
        content: { type: 'string' },
      },
      required: [ 'username', 'content' ]
    },
    pathParameters: {
      type: 'object',
      properties: {
        ownerName: { type: 'string' },
        repoName: { type: 'string' },
        pullRequestNumber: { type: 'integer' }
      },
      required: ['ownerName', 'repoName', 'pullRequestNumber' ]
    }
  },
  required: [ 'body' ]
}

const handler = async event => {
  const pullRequestComment = new PullRequestComment({
    ownerName: event.pathParameters.ownerName,
    repoName: event.pathParameters.repoName,
    targetNumber: event.pathParameters.pullRequestNumber,
    content: event.body.content,
    commentorUsername: event.body.username,
  })
  const { error } = await addCommentToPullRequest(pullRequestComment)
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ pullRequestComment })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })