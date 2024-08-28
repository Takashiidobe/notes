# Running a Github Actions worker:

To create your own github actions worker, follow these instructions:

1. Go to the repository, organization, or enterprise where you want to add the runner.
2. Navigate to Settings > Actions > Runners.
3. Click Add runner to start the setup process.

# Create a directory for your runner

```sh
mkdir actions-runner && cd actions-runner
```

# Download the latest runner package

```sh
curl -o actions-runner-linux-x64-2.319.0.tar.gz -L https://github.com/actions/runner/releases/download/v2.319.0/actions-runner-linux-x64-2.319.0.tar.gz
```

# Extract the installer

```sh
tar xzf ./actions-runner-linux-x64-2.319.0.tar.gz
```

# Configure the runner

```sh
./config.sh --url https://github.com/your-repo-owner/your-repo-name --token YOUR_PERSONAL_ACCESS_TOKEN
```

# Run the runner

```sh
./run.sh
```

Then, your runner will pick up jobs it can.
