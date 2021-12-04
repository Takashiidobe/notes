const { makeHandler } = require('./utils')
const { getFrontPageAndLatestDeals } = require('../data')

const handler = async event => {
  const { page, deals, error } = await getFrontPageAndLatestDeals()
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ ...page, deals })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler })