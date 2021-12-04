const { makeHandler } = require('./utils')
const { addReactionToComment } = require('../data')
const { CommentReaction, IssueComment, PullRequestComment, REACTION_TYPES, getReactionName } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        username: { type: 'string' },
        reaction: { 
          type: 'string',
          enum: REACTION_TYPES,
        },
        targetType: { type: 'string' },
        targetNumber: { type: 'string' },
      },
      required: [ 'username', 'reaction', 'targetType', 'targetNumber' ]
    },
    pathParameters: {
      type: 'object',
      properties: {
        ownerName: { type: 'string' },
        repoName: { type: 'string' },
        commentId: { type: 'string' }
      },
      required: ['ownerName', 'repoName', 'commentId' ]
    }
  },
  required: [ 'body' ]
}

const targetClassMap = {
  'issue': IssueComment,
  'pullRequest': PullRequestComment
}

const handler = async event => {
  const reaction = getReactionName(event.body.reaction)
  const commentReaction = new CommentReaction({
    ownerName: event.pathParameters.ownerName,
    repoName: event.pathParameters.repoName,
    id: event.pathParameters.commentId,
    reactingUsername: event.body.username,
  })
  const targetClass = targetClassMap[event.body.targetType]
  const comment = new targetClass({
    commentId: event.pathParameters.commentId,
    ownerName: event.pathParameters.ownerName,
    repoName: event.pathParameters.repoName,
    targetNumber: event.body.targetNumber,
  })

  const { error } = await addReactionToComment({ commentReaction, comment, reaction })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ message: 'OK' })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })