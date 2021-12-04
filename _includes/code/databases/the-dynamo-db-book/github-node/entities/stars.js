class Star {

    constructor({ ownerName, repoName, username, starredAt = new Date() }) {
        if (!ownerName) {
            throw new Error('Star requires an owner name')
        }
        this.ownerName = ownerName
        
        if (!repoName) {
            throw new Error('Star requires a repo name')
        }
        this.repoName = repoName

        this.username = username
        this.starredAt = starredAt
    }

    key() {
        return {
            'PK': { 'S': `REPO#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}` },
            'SK': { 'S': `STAR#${this.username.toLowerCase()}` }
        }
    }

    toItem() {
        return {
            ...this.key(),
            'Type': { 'S': 'Star' },
            'OwnerName': { 'S': this.ownerName },
            'RepoName': { 'S': this.repoName },
            'Username': { 'S': this.username },
            'StarredAt': { 'S': this.starredAt.toISOString() }
        }
    }

}

const starFromItem = (item) => {
    return new Star({
        ownerName: item.OwnerName.S,
        repoName: item.RepoName.S,
        username: item.Username.S,
        starredAt: new Date(item.StarredAt.S)
    })
}

module.exports = {
    Star,
    starFromItem
}