const { makeHandler } = require('./utils')
const { updatePaymentPlanForOrganization } = require('../data')
const { Organization, PaymentPlan, PLAN_TYPES } = require('../entities')

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
        organizationName: { type: 'string' }
      },
      required: ['organizationName']
    }
  },
  required: [ 'body' ]
}

const handler = async event => {
  const paymentPlan = new PaymentPlan({
    planType: event.body.planType
  })
  const organization_obj = new Organization({
    organizationName: event.pathParameters.organizationName,
    paymentPlan
  })
  const { organization, error } = await updatePaymentPlanForOrganization(organization_obj)
  const statusCode = error ? 500 : 200
  const body = error ? JSON.stringify({ error }) : JSON.stringify({ organization })
  return {
    statusCode,
    body
  }
}

module.exports.handler = makeHandler({ handler, inputSchema })