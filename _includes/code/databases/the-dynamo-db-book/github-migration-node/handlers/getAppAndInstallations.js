const { makeHandler } = require('./utils')
const { getAppAndInstallations } = require('../data')
const { GitHubApp } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    pathParameters: {
      type: 'object',
      properties: {
        appOwner: { type: 'string' },
        appName: { type: 'string' }
      },
      required: [ 'appOwner', 'appName' ]
    }
  },
  required: [ 'pathParameters' ]
}

const handler = async event => {
  const app_obj = new GitHubApp({
    appOwner: event.pathParameters.appOwner,
    appName: event.pathParameters.appName
  })
  const { app, installations, error } = await getAppAndInstallations({ app: app_obj })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ app, installations })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })