const { makeHandler } = require('./utils')
const { updateCodeOfConductForRepo } = require('../data')
const { CodeOfConduct, Repo } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        name: { type: 'string' },
        URL: { type: 'string' }
      },
      required: [ 'name', 'URL' ]
    },
    pathParameters: {
      type: 'object',
      properties: {
        ownerName: { type: 'string' },
        repoName: { type: 'string' },
      },
      required: ['ownerName', 'repoName']
    }
  },
  required: [ 'body' ]
}

const handler = async event => {
  const codeOfConduct = new CodeOfConduct({
    name: event.body.name,
    URL: event.body.URL
  })
  const repo_obj = new Repo({
    ownerName: event.pathParameters.ownerName,
    repoName: event.pathParameters.repoName,
    codeOfConduct
  })
  const { repo, error } = await updateCodeOfConductForRepo(repo_obj)
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ repo })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })