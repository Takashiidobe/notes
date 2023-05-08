# Design a feed of Top Companies

- You subscribe to a data stream of all companies that are traded, and live inputs are coming of which company is being traded with their volume. How do you maintain the data, so that you can relay the top 10 most traded companies by volume of shares efficiently?

- What happens if reads (asking for the top 10 companies by volume) are much less common than writes?

- What happens if reads are much more common?

- How does this approach fare with cache locality?
