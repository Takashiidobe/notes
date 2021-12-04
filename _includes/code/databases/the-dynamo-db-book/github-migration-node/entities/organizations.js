const { PaymentPlan, paymentPlanFromString } = require('./paymentPlans')

class Organization {

    constructor({ organizationName, ownerName, createdAt = new Date(), members = 1, paymentPlan = new PaymentPlan({}) }) {
        if (!organizationName) {
            throw new Error('Organization requires an organization name')
        }
        this.organizationName = organizationName
        this.ownerName = ownerName
        this.createdAt = createdAt
        this.members = parseInt(members)
        this.paymentPlan = paymentPlan
    }

    pk() {
        return { 'S': `ACCOUNT#${this.organizationName.toLowerCase()}` }
    }

    key() {
        return {
            'PK': this.pk(),
            'SK': { 'S': `ACCOUNT#${this.organizationName.toLowerCase()}` }
        }
    }

    gsi1pk() {
        return { 'S': `ACCOUNT#${this.organizationName.toLowerCase()}` }

    }

    gsi1sk() {
        return { 'S': `ACCOUNT#${this.organizationName.toLowerCase()}` }
    }

    gsi1() {
        return {
            'GSI1PK': this.gsi1pk(),
            'GSI1SK': this.gsi1sk()
        }
    }

    gsi3pk() {
        return { 'S': `ACCOUNT#${this.organizationName.toLowerCase()}` }

    }

    gsi3() {
        return {
            'GSI3PK': this.gsi3pk(),
            'GSI3SK': { 'S': `ACCOUNT#${this.organizationName.toLowerCase()}` }
        }
    }


    toItem() {
        return {
            ...this.key(),
            ...this.gsi1(),
            ...this.gsi3(),
            'Type': { 'S': 'Organization' },
            'OrganizationName': { 'S': this.organizationName },
            'OwnerName': { 'S': this.ownerName },
            'Members': { 'N': this.members.toString() },
            'CreatedAt': { 'S': this.createdAt.toISOString() },
            'PaymentPlan': { 'S': this.paymentPlan.toString() }
        }
    }

}

const organizationFromItem = (item) => {
    // It's possible we could retrieve a User by accident due to similar key structure.
    // This will prevent us from returning a User as an Organization
    if (item.Type.S !== 'Organization') {
        throw new Error('Not an organization.')
    }
    return new Organization({
        organizationName: item.OrganizationName.S,
        ownerName: item.OwnerName.S,
        members: item.Members.S,
        createdAt: new Date(item.CreatedAt.S),
        paymentPlan: item.PaymentPlan ? paymentPlanFromString(item.PaymentPlan.S) : {}
    })
}

module.exports = {
    Organization,
    organizationFromItem
}