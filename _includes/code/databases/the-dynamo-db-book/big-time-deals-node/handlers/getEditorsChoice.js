const { makeHandler } = require('./utils')
const { getEditorsChoice } = require('../data')

const handler = async event => {
  const { page, error } = await getEditorsChoice()
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ ...page })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler })