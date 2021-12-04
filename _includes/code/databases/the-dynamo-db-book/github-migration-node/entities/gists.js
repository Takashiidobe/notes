const { generateKSUID, zeroPadNumber, REACTION_TYPES } = require('./utils')

class Gist {
    constructor({ ownerName, gistId, gistTitle, createdAt = new Date(), updatedAt = new Date() }) {
        if (!ownerName) {
            throw new Error('Gist requires owner name.')
        }
        this.ownerName = ownerName

        if (gistId) {
            this.gistId = gistId 
        } else {
            this.gistId = generateKSUID(createdAt)
        }

        this.gistTitle = gistTitle
        this.createdAt = createdAt
        this.updatedAt = updatedAt
    }

    key() {
        return {
            'PK': { 'S': `ACCOUNT#${this.ownerName.toLowerCase()}` },
            'SK': { 'S': `#GIST#${this.gistId}` }
        }
    }

    toItem() {
        return {
            ...this.key(),
            'Type': { 'S': 'Gist' },
            'OwnerName': { 'S': this.ownerName },
            'GistId': { 'S': this.gistId },
            'GistTitle': { 'S': this.gistTitle },
            'CreatedAt': { 'S': this.createdAt.toISOString() },
            'UpdatedAt': { 'S': this.updatedAt.toISOString() },
        }
    }
}

const gistFromItem = (attributes) => { 
    return new Gist({
        ownerName: attributes.OwnerName.S,
        gistId: attributes.GistId.S,
        gistTitle: attributes.GistTitle.S,
        createdAt: new Date(attributes.CreatedAt.S),
        updatedAt: new Date(attributes.UpdatedAt.S),
    })
}


module.exports = {
    Gist,
    gistFromItem
}