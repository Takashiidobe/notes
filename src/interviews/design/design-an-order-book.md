# Design an Order Book

- An Order book keeps a map of stocks with bids and ask spreads for each instrument. If there comes in a trade that is buy/sell over the bid/ask, take it.

- Otherwise, try dumping some of the stock to not hold onto it too long.
