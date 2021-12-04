const { makeHandler } = require('./utils')
const { addCommentToIssue } = require('../data')
const { IssueComment } = require('../entities')

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
        issueNumber: { type: 'integer' }
      },
      required: ['ownerName', 'repoName', 'issueNumber' ]
    }
  },
  required: [ 'body' ]
}

const handler = async event => {
  const issueComment = new IssueComment({
    ownerName: event.pathParameters.ownerName,
    repoName: event.pathParameters.repoName,
    targetNumber: event.pathParameters.issueNumber,
    content: event.body.content,
    commentorUsername: event.body.username,
  })
  const { error } = await addCommentToIssue(issueComment)
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ issueComment })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })