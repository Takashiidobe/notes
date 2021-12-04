const { zeroPadNumber, zeroPadDifference, ISSUE_STATUSES, REACTION_TYPES } = require('./utils')

class Issue {
    constructor({ ownerName, repoName, creatorUsername, title, content, status = 'Open', issueNumber, createdAt = new Date(), updatedAt = new Date(), reactions = {} }) {
        if (!ownerName) {
            throw new Error('Issue requires owner name.')
        }
        this.ownerName = ownerName

        if (!repoName) {
            throw new Error('Issue requires repo name.')
        }
        this.repoName = repoName

        this.creatorUsername = creatorUsername
        this.title = title
        this.content = content
        if (status && !ISSUE_STATUSES.includes(status)) {
            throw new Error(`Invalid status: ${status}`)
        }
        this.status = status

        this.issueNumber = parseInt(issueNumber)
        this.createdAt = createdAt
        this.updatedAt = updatedAt
        this.reactions = reactions
    }

    zeroPaddedIssueNumber() {
        return zeroPadNumber(this.issueNumber)
    }

    zeroPaddedIssueNumberDifference() {
        return zeroPadDifference(this.issueNumber)
    }

    key() {
        return {
            'PK': { 'S': `REPO#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}` },
            'SK': { 'S': `ISSUE#${this.zeroPaddedIssueNumber()}` }
        }
    }

    gsi4pk() {
        return { 'S': `REPO#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}` }
    }

    gsi4sk() {
        if (this.status === 'Open') {
            return { 'S': `ISSUE#OPEN#${this.zeroPaddedIssueNumberDifference()}`}
        }
        return { 'S': `#ISSUE#CLOSED#${this.zeroPaddedIssueNumber()}`}
    }

    gsi4() {
        return {
            'GSI4PK': this.gsi4pk(),
            'GSI4SK': this.gsi4sk()
        }
    }

    toItem() {
        return {
            ...this.key(),
            ...this.gsi4(),
            'Type': { 'S': 'Issue' },
            'OwnerName': { 'S': this.ownerName },
            'RepoName': { 'S': this.repoName },
            'IssueNumber': { 'S': this.issueNumber.toString() },
            'CreatorUsername': { 'S': this.creatorUsername },
            'Title': { 'S': this.title },
            'Content': { 'S': this.content },
            'Status': { 'S': this.status },
            'CreatedAt': { 'S': this.createdAt.toISOString() },
            'UpdatedAt': { 'S': this.updatedAt.toISOString() },
            'Reactions': { 'M': this.formatReactions() }
        }
    }

    formatReactions() {
        const reactions = {}
        Object.values(REACTION_TYPES).forEach((reaction) => {
            const count = this.reactions[reaction] || 0
            reactions[reaction] = { 'N': count.toString() }
        })
        return reactions
    }
}

const parseReactions = reactions => {
    const parsed = {}
    for (let [name, count] of Object.entries(reactions)) {
        parsed[name] = parseInt(count.N)
    }
    return parsed
}

const issueFromItem = (attributes) => { 
    return new Issue({
        ownerName: attributes.OwnerName.S,
        repoName: attributes.RepoName.S,
        issueNumber: attributes.IssueNumber.S,
        creatorUsername: attributes.CreatorUsername.S,
        title: attributes.Title.S,
        content: attributes.Content.S,
        status: attributes.Status.S,
        createdAt: new Date(attributes.CreatedAt.S),
        updatedAt: new Date(attributes.UpdatedAt.S),
        reactions: parseReactions(attributes.Reactions.M)
    })
}

module.exports = {
    Issue,
    issueFromItem
}