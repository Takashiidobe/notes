const algolia = require("atomic-algolia");
const indexName = "notes";

const APPLICATION_ID = process.env.APPLICATION_ID;

const indexPath = "./docs/search.json"

algolia(indexName, indexPath, {}, (err, _) => {
  if (err) throw err;
  console.log("Success");
});
