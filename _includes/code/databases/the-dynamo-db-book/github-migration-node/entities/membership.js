const ROLES = [
    'Owner',
    'Admin',
    'Member'
]

class Membership {

    constructor({ organizationName, username, role, memberSince = new Date() }) {
        if (!organizationName) {
            throw new Error('Membership requires an organization name')
        }
        this.organizationName = organizationName
        if (!username) {
            throw new Error('Membership requires a username')
        }
        this.username = username
        if (!ROLES.includes(role)) {
            throw new Error(`Invalid role: ${role}`)
        }
        this.role = role
        this.memberSince = memberSince
    }

    key() {
        return {
            'PK': { 'S': `ACCOUNT#${this.organizationName.toLowerCase()}` },
            'SK': { 'S': `MEMBERSHIP#${this.username.toLowerCase()}` }
        }
    }

    toItem() {
        return {
            ...this.key(),
            'Type': { 'S': 'Membership' },
            'OrganizationName': { 'S': this.organizationName },
            'Username': { 'S': this.username },
            'Role': { 'S': this.role },
            'MemberSince': { 'S': this.memberSince.toISOString() }
        }
    }

}

const membershipFromItem = (item) => {
    return new Membership({
        organizationName: item.OrganizationName.S,
        username: item.Username.S,
        role: item.Role.S,
        memberSince: new Date(item.MemberSince.S)
    })
}

module.exports = {
    Membership,
    membershipFromItem,
    ROLES
}