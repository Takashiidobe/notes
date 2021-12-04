const { makeHandler } = require('./utils')
const { addStarToRepo } = require('../data')
const { Star } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        username: { type: 'string' },
      },
      required: [ 'username' ]
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
  const star = new Star({
    ownerName: event.pathParameters.ownerName,
    repoName: event.pathParameters.repoName,
    username: event.body.username,
  })
  const { error } = await addStarToRepo(star)
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ star })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })