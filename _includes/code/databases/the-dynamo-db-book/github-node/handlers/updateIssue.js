const { makeHandler } = require('./utils')
const { updateIssue } = require('../data')
const { Issue, ISSUE_STATUSES } = require('../entities')

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
          enum: ISSUE_STATUSES
        }
      },
      required: [ 'title', 'content', 'status']
    },
    pathParameters: {
      type: 'object',
      properties: {
        ownerName: { type: 'string' },
        repoName: { type: 'string' },
        issueNumber: { type: 'number' }
      },
      required: [ 'ownerName', 'repoName', 'issueNumber' ]
    }
  },
  required: [ 'pathParameters' ]
}

const handler = async event => {
  const issue_obj = new Issue({
    ownerName: event.pathParameters.ownerName,
    repoName: event.pathParameters.repoName,
    issueNumber: event.pathParameters.issueNumber,
    title: event.body.title,
    content: event.body.content,
    status: event.body.status
  })
  const { issue, error } = await updateIssue({ issue: issue_obj })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ issue })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })