const { makeHandler } = require('./utils')
const { getCommentsForIssue } = require('../data')
const { IssueComment } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    pathParameters: {
      type: 'object',
      properties: {
        ownerName: { type: 'string' },
        repoName: { type: 'string' },
        issueNumber: { type: 'integer' }
      },
      required: [ 'ownerName', 'repoName', 'issueNumber' ]
    }
  },
  required: [ 'pathParameters' ]
}

const handler = async event => {
  const issueComment = new IssueComment({
    ownerName: event.pathParameters.ownerName,
    repoName: event.pathParameters.repoName,
    targetNumber: event.pathParameters.issueNumber
  })
  const { issueComments, error } = await getCommentsForIssue({ issueComment })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ issueComments })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })