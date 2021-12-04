const { makeHandler } = require('./utils')
const { addIssueToRepo } = require('../data')
const { Issue } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        creatorUsername: { type: 'string' },
        title: { type: 'string' },
        content: { type: 'string' },
      },
      required: [ 'creatorUsername', 'title', 'content' ]
    },
    pathParameters: {
      type: 'object',
      properties: {
        ownerName: { type: 'string' },
        repoName: { type: 'string' }
      },
      required: ['ownerName', 'repoName']
    }
  },
  required: [ 'body' ]
}

const handler = async event => {
  const issue_obj = new Issue({
    ownerName: event.pathParameters.ownerName,
    repoName: event.pathParameters.repoName,
    creatorUsername: event.body.creatorUsername,
    title: event.body.title,
    content: event.body.content,
  })
  const { issue, error } = await addIssueToRepo({ issue: issue_obj })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ issue })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })