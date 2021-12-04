const { notifyBrandWatchers, notifyCategoryWatchers } = require('../data')
const { dealFromItem } = require('../entities')

exports.handler = async event => {
  const records = event.Records.filter((record) => {
    return record.eventName === 'INSERT' && record.dynamodb.NewImage.Type.S === 'Deal'
  }).map((record) => { return dealFromItem(record.dynamodb.NewImage) })

  const brandPromises = records.map((deal) => notifyBrandWatchers({ deal }))
  const categoryPromises = records.map((deal) => notifyCategoryWatchers({ deal }))

  try {
    const results = await Promise.all([ ...brandPromises, ...categoryPromises ])
    const count = results.reduce((acc, cur) => { return acc + cur}, 0)
    console.log(`Sent messages to ${count} watchers across ${records.length} deals`)
  } catch(error) {
    console.log('Error sending messages to watchers.')
    console.log(error)
  }
}