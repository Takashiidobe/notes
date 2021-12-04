const { makeHandler } = require('./utils')
const { addReactionToPullRequest } = require('../data')
const { PullRequestReaction, REACTION_TYPES, getReactionName } = require('../entities')

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
        pullRequestNumber: { type: 'integer' }
      },
      required: ['ownerName', 'repoName', 'pullRequestNumber' ]
    }
  },
  required: [ 'body' ]
}

const handler = async event => {
  const reaction = getReactionName(event.body.reaction)
  const pullRequestReaction = new PullRequestReaction({
    ownerName: event.pathParameters.ownerName,
    repoName: event.pathParameters.repoName,
    id: event.pathParameters.pullRequestNumber,
    reactingUsername: event.body.username,
  })
  const { error } = await addReactionToPullRequest({ pullRequestReaction, reaction })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ message: 'OK' })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })