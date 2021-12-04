const PLAN_TYPES = [
    'Pro',
    'Enterprise',
    'Mega'
]

class PaymentPlan {

    constructor({ planType, planStartDate = new Date() }) {
        if (planType && !PLAN_TYPES.includes(planType)) {
            throw new Error(`Invalid plan type: ${planType}`)
        }
        this.planType = planType
        this.planStartDate = planStartDate
    }

    toString() {
        return JSON.stringify(this)
    }
}

const paymentPlanFromString = (string) => {
    const parsed = JSON.parse(string)
    return new PaymentPlan({
        planType: parsed.planType,
        planStartDate: new Date(parsed.planStartDate)
    })
}

module.exports = {
    PaymentPlan,
    paymentPlanFromString,
    PLAN_TYPES
}