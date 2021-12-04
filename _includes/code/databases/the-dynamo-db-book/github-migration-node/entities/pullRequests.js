const { zeroPadNumber, zeroPadDifference, PR_STATUSES, REACTION_TYPES } = require('./utils')

class PullRequest {
    constructor({ ownerName, repoName, creatorUsername, title, content, status = 'Open', pullRequestNumber, createdAt = new Date(), updatedAt = new Date(), reactions = {} }) {
        if (!ownerName) {
            throw new Error('Pull request requires owner name.')
        }
        this.ownerName = ownerName

        if (!repoName) {
            throw new Error('Pull request requires repo name.')
        }
        this.repoName = repoName

        this.creatorUsername = creatorUsername
        this.title = title
        this.content = content
        if (status && !PR_STATUSES.includes(status)) {
            throw new Error(`Invalid status: ${status}`)
        }
        this.status = status

        this.pullRequestNumber = parseInt(pullRequestNumber)
        this.createdAt = createdAt
        this.updatedAt = updatedAt
        this.reactions = reactions
    }

    zeroPaddedPullRequestNumber() {
        return zeroPadNumber(this.pullRequestNumber)
    }

    zeroPaddedPullRequestNumberDifference() {
        return zeroPadDifference(this.pullRequestNumber)
    }

    key() {
        return {
            'PK': { 'S': `PR#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}#${this.zeroPaddedPullRequestNumber()}` },
            'SK': { 'S': `PR#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}#${this.zeroPaddedPullRequestNumber()}` },
        }
    }

    gsi1() {
        return {
            'GSI1PK': { 'S': `REPO#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}` },
            'GSI1SK': { 'S': `PR#${this.zeroPaddedPullRequestNumber()}` },
        }
    }
    gsi5pk() {
        return { 'S': `REPO#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}` }
    }

    gsi5sk() {
        if (this.status === 'Open') {
            return { 'S': `PR#OPEN#${this.zeroPaddedPullRequestNumberDifference()}`}
        }
        return { 'S': `#PR#CLOSED#${this.zeroPaddedPullRequestNumber()}`}
    }

    gsi5() {
        return {
            'GSI5PK': this.gsi5pk(),
            'GSI5SK': this.gsi5sk()
        }
    }

    toItem() {
        return {
            ...this.key(),
            ...this.gsi1(),
            ...this.gsi5(),
            'Type': { 'S': 'PullRequest' },
            'OwnerName': { 'S': this.ownerName },
            'RepoName': { 'S': this.repoName },
            'PullRequestNumber': { 'S': this.pullRequestNumber.toString() },
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

const pullRequestFromItem = (attributes) => { 
    return new PullRequest({
        ownerName: attributes.OwnerName.S,
        repoName: attributes.RepoName.S,
        pullRequestNumber: attributes.PullRequestNumber.S,
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
    PullRequest,
    pullRequestFromItem
}