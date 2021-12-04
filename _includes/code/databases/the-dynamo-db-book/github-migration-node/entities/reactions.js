const { REACTION_TYPES } = require('./utils')

class Reaction {
    constructor({ ownerName, repoName, id, reactingUsername }) {
        if (!ownerName) {
            throw new Error('Reaction requires owner name.')
        }
        this.ownerName = ownerName

        if (!repoName) {
            throw new Error('Reaction requires repo name.')
        }
        this.repoName = repoName

        if (!id) {
            throw new Error('Reaction requires id.')
        }
        this.id = id

        this.reactingUsername = reactingUsername
    }

    identifier() {
        return `${this.type().toUpperCase()}#${this.id}`
    }

    key() {
        return {
            'PK': { 'S': `${this.type().toUpperCase()}REACTION#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}#${this.identifier()}#${this.reactingUsername}` },
            'SK': { 'S': `${this.type().toUpperCase()}REACTION#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}#${this.identifier()}#${this.reactingUsername}` },
        }
    }
}


class IssueReaction extends Reaction {

    type() {
        return 'Issue'
    }
}

class PullRequestReaction extends Reaction {

    type() {
        return 'PR'
    }
}

class CommentReaction extends Reaction {

    type() {
        return 'Comment'
    }
}

const getReactionName = reaction => {
    return REACTION_TYPES[reaction]
}

module.exports = {
    IssueReaction,
    PullRequestReaction,
    CommentReaction,
    getReactionName
}