class GitHubApp {
    constructor({ appOwner , appName, description, createdAt = new Date(), updatedAt = new Date() }) {
        if (!appOwner) {
            throw new Error('Repo requires app owner.')
        }
        this.appOwner = appOwner 

        this.appName = appName
        this.description = description
        this.createdAt = createdAt
        this.updatedAt = updatedAt
    }

    pk() {
        return { 'S': `APP#${this.appOwner.toLowerCase()}#${this.appName.toLowerCase()}` }
    }

    key() {
        return {
            'PK': this.pk(),
            'SK': { 'S': `APP#${this.appOwner.toLowerCase()}#${this.appName.toLowerCase()}` }
        }
    }

    gsi1() {
        return {
            'GSI1PK': { 'S': `ACCOUNT#${this.appOwner.toLowerCase()}` },
            'GSI1SK': { 'S': `APP#${this.appName.toLowerCase()}` }
        }
    }

    toItem() {
        const item = {
            ...this.key(),
            ...this.gsi1(),
            'Type': { 'S': 'GitHubApp' },
            'AppOwner': { 'S': this.appOwner },
            'AppName': { 'S': this.appName },
            'CreatedAt': { 'S': this.createdAt.toISOString() },
            'UpdatedAt': { 'S': this.updatedAt.toISOString() },
        }
        if (this.description) {
            item.Description = { 'S': this.description }
        }
        return item
    }
}

const gitHubAppFromItem = (attributes) => { 
    return new GitHubApp({
        appOwner: attributes.AppOwner.S,
        appName: attributes.AppName.S,
        description: attributes.Description ? attributes.Description.S : undefined,
        createdAt: new Date(attributes.CreatedAt.S),
        updatedAt: new Date(attributes.UpdatedAt.S)
    })
}

class GitHubAppInstallation {
    constructor({ appOwner, appName, repoOwner, repoName, installedAt = new Date(), updatedAt = new Date() }) {
        if (!appOwner) {
            throw new Error('GitHub App Installation requires app owner.')
        }
        this.appOwner = appOwner

        if (!appName) {
            throw new Error('GitHub App Installation requires app name.')
        }
        this.appName = appName

        this.repoOwner = repoOwner
        this.repoName = repoName

        this.installedAt = installedAt 
        this.updatedAt = updatedAt
    }

    key() {
        return {
            'PK': { 'S': `APP#${this.appOwner.toLowerCase()}#${this.appName.toLowerCase()}` },
            'SK': { 'S': `REPO#${this.repoOwner.toLowerCase()}#${this.repoName.toLowerCase()}` },
        }
    }

    gsi1() {
        return {
            'GSI1PK': { 'S': `REPO#${this.repoOwner.toLowerCase()}#${this.repoName.toLowerCase()}` },
            'GSI1SK': { 'S': `REPOAPP#${this.appOwner.toLowerCase()}#${this.appName.toLowerCase()}` },
        }
    }

    toItem() {
        return {
            ...this.key(),
            ...this.gsi1(),
            'Type': { 'S': 'GitHubAppInstallation' },
            'AppOwner': { 'S': this.appOwner },
            'AppName': { 'S': this.appName },
            'RepoOwner': { 'S': this.repoOwner },
            'RepoName': { 'S': this.repoName },
            'InstalledAt': { 'S': this.installedAt.toISOString() },
            'UpdatedAt': { 'S': this.updatedAt.toISOString() },
        }
    }
}

const gitHubAppInstallationFromItem = (attributes) => { 
    return new GitHubAppInstallation({
        appOwner: attributes.AppOwner.S,
        appName: attributes.AppName.S,
        repoOwner: attributes.RepoOwner.S,
        repoName: attributes.RepoName.S,
        installedAt: new Date(attributes.InstalledAt.S),
        updatedAt: new Date(attributes.UpdatedAt.S),
    })
}


module.exports = {
    GitHubApp,
    gitHubAppFromItem,
    GitHubAppInstallation,
    gitHubAppInstallationFromItem
}