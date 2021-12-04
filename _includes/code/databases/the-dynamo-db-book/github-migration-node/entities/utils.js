const crypto = require('crypto')
const KSUID = require('ksuid')

const generateKSUID = timestamp => {
    const payload = crypto.randomBytes(16)
    return KSUID.fromParts(timestamp.getTime(), payload).string
}

const zeroPadNumber = (number) => {
    return ("0000000" + number).slice(-7)
}

const zeroPadDifference = (number) => {
    const difference = 9999999 - number
    return ("0000000" + difference).slice(-7)
}

const ISSUE_STATUSES = [
    'Open',
    'Closed'
]

const PR_STATUSES = [
    'Open',
    'Closed',
    'Merged'
]

const REACTION_TYPES = {
    '+1': '+1',
    '-1': '-1',
    'smile': 'Smile',
    'celebration': 'Celebration',
    'disappointed': 'Disappointed',
    'heart': 'Heart',
    'rocket': 'Rocket',
    'eyes': 'Eyes',
}


module.exports = {
    generateKSUID,
    zeroPadNumber,
    zeroPadDifference,
    ISSUE_STATUSES,
    PR_STATUSES,
    REACTION_TYPES
}