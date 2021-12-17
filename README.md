# Notes

This is repository that compiles markdown notes in an html website.

Example here: <https://notes.takashiidobe.com/>

## Dependencies

- GNU Make
- Pandoc
- Node
- miniserve (for development)
- netlify (for deployment)

On mac these can be installed like so:

```sh
brew install make pandoc node miniserve
npm install -g netlify
```

## Building

To build the whole site, run `make`.

## Deployment

To deploy the site to netlify, run `make deploy`.
