const { makeHandler } = require('./utils')
const { getIssue } = require('../data')
const { Issue } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
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
    issueNumber: event.pathParameters.issueNumber
  })
  const { issue, error } = await getIssue({ issue: issue_obj })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ issue })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })