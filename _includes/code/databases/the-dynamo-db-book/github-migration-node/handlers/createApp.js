const { makeHandler } = require('./utils')
const { createApp } = require('../data')
const { GitHubApp } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        ownerName: { type: 'string' },
        appName: { type: 'string' },
        description: { type: 'string' },
      },
      required: [ 'ownerName', 'appName', ]
    }
  },
  required: [ 'body' ]
}

const handler = async event => {
  const app = new GitHubApp({
    appOwner: event.body.ownerName,
    appName: event.body.appName,
    description: event.body.description,
  })
  const { error } = await createApp(app)
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ app })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })