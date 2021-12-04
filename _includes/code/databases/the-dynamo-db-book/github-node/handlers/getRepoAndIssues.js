const { makeHandler } = require('./utils')
const { getRepoAndIssues } = require('../data')
const { Repo } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    pathParameters: {
      type: 'object',
      properties: {
        ownerName: { type: 'string' },
        repoName: { type: 'string' }
      },
      required: ['ownerName', 'repoName']
    }
  },
  required: [ 'pathParameters' ]
}

const handler = async event => {
  const repo_obj = new Repo({
    ownerName: event.pathParameters.ownerName,
    repoName: event.pathParameters.repoName
  })
  const status = event.queryStringParameters && event.queryStringParameters.status ? event.queryStringParameters.status : 'Open'
  const { repo, issues, error } = await getRepoAndIssues({ repo: repo_obj, status })
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ repo, issues })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })