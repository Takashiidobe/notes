# You might not need redis

[Article](https://www.viblo.se/posts/no-need-redis/)

This article goes through stories where three different dev teams
thought of using redis, but it would've been better to avoid it. The
first story ends with them caching data in postgreSQL, instead of having
to spin up redis.

Some of the comments on the hackernews post are interesting, including
this one where the developer used elasticsearch and H3 to do what took
hundreds of redis servers.

> When I was in Uber back in 2015, my org was trying to convert zip-code-based geo partitioning with a hexagon-based scheme. Instead of partitioning a city into on average tens of zip codes, we may partition the city into potentially hundreds of thousands of hexagons and dynamically create areas. The first launch was in Phoenix, and the team who was responsible for the launch stayed up all night for days because they could barely scale our demand-pricing systems. And then the global launch of the feature was delayed first by days, then by weeks, and then by months.
> It turned out Uber engineers just loved Redis. Having a need to distribute your work? Throw that to Redis. I remember debating with some infra engineers why we couldn't throw in more redis/memcached nodes to scale our telemetry system, but I digressed. So, the price service we built was based on Redis. The service fanned out millions of requests per second to redis clusters to get information about individual hexagons of a given city, and then computed dynamic areas. We would need dozens of servers just to compute for a single city. I forgot the exact number, but let's say it was 40 servers per an average-sized city. Now multiply that by the 200+ cities we had. It was just prohibitively expensive, let alone that there couldn't other scalability bottlenecks for managing such scale.
> The solution was actually pretty simple. I took a look at the algorithms we used, and it was really just that we needed to compute multiple overlapping shapes. So, I wrote an algorithm that used work-stealing to compute the shapes in parallel per city on a single machine, and used Elasticsearch to retrieve hexagons by a number of attributes -- it was actually a perfect use case for a search engine because the retrieval requires boolean queries of multiple attributes. The rationale was pretty simple too: we needed to compute repetitively on the same set of data, so we should retrieve the data only once for multiple computations. The algorithm was of merely dozens of lines, and was implemented and deployed to production over the weekend by this amazing engineer Isaac, who happens to be the author of the library H3. As a result, we were able to compute dynamic areas for 40 cities, give or take, on a single machine, and the launch was unblocked.

Or another comment, where a user says that redis is slow compared to
using a regular synchronized hashmap. You're looking at sub-microsecond
latency vs. millisecond latency due to network roundtrips on the same
data center.

> I have gotten in arguments with people who over-deploy Redis. Redis is cool, I don't dislike it or anything, but a lot of the time when people use it, it actually slows things down.
> Using it, you're introducing network latency and serialization overhead. Sometimes that's worth it, especially if your database is falling over, but a lot of the time people use it and it just makes everything more complex and worse.
> If you need to share cached data across processes or nodes, sometimes you have to use it, but a lot of the stuff I work with is partitioned anyway. If your data is already partitioned, you know what works well a lot of the time? A boring, regular hashmap.
> Pretty much every language has some thread-safe hashmap in there, and a lot of them have pretty decent libraries to handle invalidation and expiration if you need those. In Java, for example, you have ConcurrentHashMap for simple stuff, and Guava Caches or Caffeine Caches for more advanced stuff.
> Even the slowest [1] local caching implementation will almost certainly be faster than anything that hits the network; in my own testing [2] Caffeine caches have sub-microsecond `put` times, and you don't pay any serialization or deserialization cost. I don't think you're likely to get much better than maybe sub-millisecond times with Redis, even in the same data center, not to mention if you're caching locally that's one less service that you have to babysit.
