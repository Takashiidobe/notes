const { makeHandler } = require('./utils')
const { installApp } = require('../data')
const { GitHubAppInstallation } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        repoOwner: { type: 'string' },
        repoName: { type: 'string' },
      },
      required: [ 'repoOwner', 'repoName', ]
    },
    pathParameters: {
      type: 'object',
      properties: {
        appOwner: { type: 'string' },
        appName: { type: 'string' }
      },
      required: [ 'appOwner', 'appName', ]
    }
  },
  required: [ 'body' ]
}

const handler = async event => {
  const appInstallation = new GitHubAppInstallation({
    appOwner: event.pathParameters.appOwner,
    appName: event.pathParameters.appName,
    repoOwner: event.body.repoOwner,
    repoName: event.body.repoName,
  })
  const { error } = await installApp(appInstallation)
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ appInstallation })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })