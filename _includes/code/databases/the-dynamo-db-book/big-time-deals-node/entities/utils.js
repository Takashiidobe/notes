const crypto = require('crypto')
const KSUID = require('ksuid')

const generateKSUID = timestamp => {
    const payload = crypto.randomBytes(16)
    return KSUID.fromParts(timestamp.getTime(), payload).string
}

const truncateTimestamp = timestamp => {
    return new Date(
        timestamp.getFullYear(),
        timestamp.getMonth(),
        timestamp.getDate()
    )
}

CATEGORIES = {
    food: 'Food & Drink',
    bathroom: 'Bathroom',
    jewelry: 'Jewelry',
    sports: 'Sports',
    tech: 'Tech',
    auto: 'Auto',
    entertainment: 'Entertainment',
    travel: 'Travel'
}

const getCategoryName = name => {
    return CATEGORIES[name.toLowerCase()]
}


module.exports = {
    generateKSUID,
    truncateTimestamp,
    CATEGORIES,
    getCategoryName
}