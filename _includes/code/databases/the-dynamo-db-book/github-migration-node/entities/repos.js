class Repo {
    constructor({ ownerName, repoName, description, forkOwner, issueAndPullRequestCount = 0, starCount = 0, forkCount = 0, createdAt = new Date(), updatedAt = new Date(), codeOfConduct = new CodeOfConduct({}) }) {
        if (!ownerName) {
            throw new Error('Repo requires owner name.')
        }
        this.ownerName = ownerName

        if (!repoName) {
            throw new Error('Repo requires repo name.')
        }
        this.repoName = repoName

        this.description = description
        this.forkOwner = forkOwner
        this.issueAndPullRequestCount = parseInt(issueAndPullRequestCount)
        this.starCount = parseInt(starCount)
        this.forkCount = parseInt(forkCount)
        this.createdAt = createdAt
        this.updatedAt = updatedAt
        this.codeOfConduct = codeOfConduct
    }

    pk() {
        return { 'S': `REPO#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}` }
    }

    sk() {
        return { 'S': `REPO#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}` }
    }

    key() {
        return {
            'PK': this.pk(),
            'SK': this.sk()
        }
    }

    gsi1pk() {
        return { 'S': `REPO#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}` }
    }

    gsi1sk() {
        return { 'S': `REPO#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}` }
    }

    gsi1() {
        return {
            'GSI1PK': this.gsi1pk(),
            'GSI1SK': this.gsi1sk()
        }
    }

    gsi2pk() {
        if (!this.forkOwner) {
            return { 'S': `REPO#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}` }
        }
        return { 'S': `REPO#${this.forkOwner.toLowerCase()}#${this.repoName.toLowerCase()}` }
    }

    gsi2sk() {
        if (!this.forkOwner) {
            return { 'S': `#REPO#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}` }
        }
        return { 'S': `FORK#${this.ownerName.toLowerCase()}` }
    }

    gsi2() {
        return {
            'GSI2PK': this.gsi2pk(),
            'GSI2SK': this.gsi2sk()
        }
    }

    gsi3() {
        return {
            'GSI3PK': { 'S': `ACCOUNT#${this.ownerName.toLowerCase()}` },
            'GSI3SK': { 'S': `#${this.updatedAt.toISOString()}` },
        }
    }

    gsi4pk() {
        return { 'S': `REPO#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}` }
    }

    gsi4sk() {
        return { 'S': `#REPO#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}` }
    }

    gsi4() {
        return {
            'GSI4PK': this.gsi4pk(),
            'GSI4SK': this.gsi4sk()
        }
    }

    gsi5pk() {
        return { 'S': `REPO#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}` }
    }

    gsi5sk() {
        return { 'S': `#REPO#${this.ownerName.toLowerCase()}#${this.repoName.toLowerCase()}` }
    }

    gsi5() {
        return {
            'GSI5PK': this.gsi5pk(),
            'GSI5SK': this.gsi5sk()
        }
    }

    toItem() {
        const item = {
            ...this.key(),
            ...this.gsi1(),
            ...this.gsi2(),
            ...this.gsi3(),
            ...this.gsi4(),
            ...this.gsi5(),
            'Type': { 'S': 'Repo' },
            'OwnerName': { 'S': this.ownerName },
            'RepoName': { 'S': this.repoName },
            'IssueAndPullRequestCount': { 'N': this.issueAndPullRequestCount.toString() },
            'StarCount': { 'N': this.starCount.toString() },
            'ForkCount': { 'N': this.forkCount.toString() },
            'CreatedAt': { 'S': this.createdAt.toISOString() },
            'UpdatedAt': { 'S': this.updatedAt.toISOString() },
            'CodeOfConduct': { 'S': this.codeOfConduct.toString() }
        }
        if (this.description) {
            item.Description = { 'S': this.description }
        }
        if (this.forkOwner) {
            item.ForkOwner = { 'S': this.forkOwner }
        }
        return item
    }
}

const repoFromItem = (attributes) => { 
    return new Repo({
        ownerName: attributes.OwnerName.S,
        repoName: attributes.RepoName.S,
        description: attributes.Description ? attributes.Description.S : undefined,
        forkOwner: attributes.ForkOwner ? attributes.ForkOwner.S : undefined,
        issueAndPullRequestCount: attributes.IssueAndPullRequestCount.N,
        starCount: attributes.StarCount.N,
        forkCount: attributes.ForkCount.N,
        createdAt: new Date(attributes.CreatedAt.S),
        updatedAt: new Date(attributes.UpdatedAt.S),
        codeOfConduct: attributes.CodeOfConduct ? codeOfConductFromString(attributes.CodeOfConduct.S) : {}
    })
}

class CodeOfConduct {

    constructor({ name, URL }) {
        this.name = name
        this.URL = URL
    }

    toString() {
        return JSON.stringify(this)
    }
}

const codeOfConductFromString = (string) => {
    const parsed = JSON.parse(string)
    return new CodeOfConduct({
        name: parsed.name,
        URL: parsed.URL
    })
}

module.exports = {
    Repo,
    repoFromItem,
    CodeOfConduct
}