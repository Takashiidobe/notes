const { makeHandler } = require('./utils')
const { createGist } = require('../data')
const { Gist } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        title: { type: 'string' }
      },
      required: [ 'title' ]
    },
    pathParameters: {
      type: 'object',
      properties: {
        username: { type: 'string' }
      },
      required: ['username']
    }
  },
  required: [ 'body' ]
}

const handler = async event => {
  const gist = new Gist({
    ownerName: event.pathParameters.username,
    gistTitle: event.body.title
  })
  const { error } = await createGist(gist)
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ gist })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })