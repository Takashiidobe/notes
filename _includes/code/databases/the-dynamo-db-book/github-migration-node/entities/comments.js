const { generateKSUID, zeroPadNumber, REACTION_TYPES } = require('./utils')

class Comment {
    constructor({ ownerName, repoName, targetNumber, commentId, commentorUsername, content, createdAt = new Date(), updatedAt = new Date(), reactions = {} }) {
        if (commentId) {
            this.commentId = commentId 
        } else {
            this.commentId = generateKSUID(createdAt)
        }
        if (!ownerName) {
            throw new Error('Comment requires owner name.')
        }
        this.ownerName = ownerName

        if (!repoName) {
            throw new Error('Comment requires repo name.')
        }
        this.repoName = repoName

        if (!targetNumber) {
            throw new Error('Comment requires target number.')
        }
        this.targetNumber = targetNumber

        this.commentorUsername = commentorUsername

        this.content = content
        this.createdAt = createdAt
        this.updatedAt = updatedAt
        this.reactions = reactions
    }

    zeroPaddedTargetNumber() {
        return zeroPadNumber(this.targetNumber)
    }

    pk() {
        return { 'S': `${this.type().toUpperCase()}#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}#${this.zeroPaddedTargetNumber()}` }
    }

    sk() {
        return { 'S': `${this.type().toUpperCase()}#${this.commentId}` }
    }

    key() {
        return {
            'PK': this.pk(),
            'SK': this.sk()
        }
    }

    toItem() {
        return {
            ...this.key(),
            'Type': { 'S': this.type() },
            'OwnerName': { 'S': this.ownerName },
            'RepoName': { 'S': this.repoName },
            [`${this.targetType()}Number`]: { 'S': this.targetNumber.toString() },
            'CommentId': { 'S': this.commentId },
            'CommentorUsername': { 'S': this.commentorUsername },
            'Content': { 'S': this.content },
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


class IssueComment extends Comment {

    targetType() {
        return 'Issue'
    }

    type() {
        return 'IssueComment'
    }

}

class PullRequestComment extends Comment {

    targetType() {
        return 'PullRequest'
    }

    type() {
        return 'PRComment'
    }

}

const parseReactions = reactions => {
    const parsed = {}
    for (let [name, count] of Object.entries(reactions)) {
        parsed[name] = parseInt(count.N)
    }
    return parsed
}

const issueCommentFromItem = (attributes) => { 
    return new IssueComment({
        ownerName: attributes.OwnerName.S,
        repoName: attributes.RepoName.S,
        targetNumber: attributes.IssueNumber.S,
        commentId: attributes.CommentId.S,
        commentorUsername: attributes.CommentorUsername.S,
        content: attributes.Content.S,
        createdAt: new Date(attributes.CreatedAt.S),
        updatedAt: new Date(attributes.UpdatedAt.S),
        reactions: parseReactions(attributes.Reactions.M)
    })
}

const pullRequestCommentFromItem = (attributes) => { 
    return new PullRequestComment({
        ownerName: attributes.OwnerName.S,
        repoName: attributes.RepoName.S,
        targetNumber: attributes.PullRequestNumber.S,
        commentId: attributes.CommentId.S,
        commentorUsername: attributes.CommentorUsername.S,
        content: attributes.Content.S,
        createdAt: new Date(attributes.CreatedAt.S),
        updatedAt: new Date(attributes.UpdatedAt.S),
        reactions: parseReactions(attributes.Reactions.M)
    })
}

module.exports = {
    IssueComment,
    PullRequestComment,
    issueCommentFromItem,
    pullRequestCommentFromItem
}