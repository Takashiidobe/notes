const { makeHandler } = require('./utils')
const { updatePaymentPlanForUser } = require('../data')
const { User, PaymentPlan, PLAN_TYPES } = require('../entities')

const inputSchema = {
  type: 'object',
  properties: {
    body: {
      type: 'object',
      properties: {
        planType: { 
          type: 'string',
          enum: PLAN_TYPES
        }
      },
      required: [ 'planType' ]
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
  const paymentPlan = new PaymentPlan({
    planType: event.body.planType
  })
  const user_obj = new User({
    username: event.pathParameters.username,
    paymentPlan
  })
  const { user, error } = await updatePaymentPlanForUser(user_obj)
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ user })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })