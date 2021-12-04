const { makeHandler } = require('./utils')
const { addReactionToIssue } = require('../data')
const { IssueReaction, REACTION_TYPES, getReactionName } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        username: { type: 'string' },
        reaction: { 
          type: 'string',
          enum: REACTION_TYPES
        },
      },
      required: [ 'username', 'reaction' ]
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
  const reaction = getReactionName(event.body.reaction)
  const issueReaction = new IssueReaction({
    ownerName: event.pathParameters.ownerName,
    repoName: event.pathParameters.repoName,
    id: event.pathParameters.issueNumber,
    reactingUsername: event.body.username,
  })
  const { error } = await addReactionToIssue({ issueReaction, reaction })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ message: 'OK' })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })