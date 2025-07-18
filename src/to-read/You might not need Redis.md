---
title: "You might not need Redis"
source: "https://www.viblo.se/posts/no-need-redis/"
author:
published:
created: 2025-07-06
description: "Redis is arguably the most well regarded tech of all. But many times you do    not need Redis. Here are 3 examples from my last 3 jobs."
tags:
  - "clippings"
---
[Redis](https://redis.io/) is arguably the most well regarded tech of all. My impression is that not even PostgreSQL has the same kind of positive aura around it. And of all tech available Redis is at the top of things you "need" to have in your tech stack. Maybe this will change with their latest [licencing change](https://redis.com/blog/redis-adopts-dual-source-available-licensing/), but that remains to be seen.

It's not difficult to see why, Redis is after all a very well architected and impressive piece of technology and this post is not arguing against any technical merits of Redis. What I will argue is that despite no technical flaw in Redis itself you still might not need it!

## My Experience

In the last 3 places I worked (10+ years) I have seen the same pattern. A problem comes up, Redis is seen as a great fit and here we go.

However, when looking closer at the actual use case it turns out that Redis didn't improve things, or did not fix the underlying problem. It just added complexity for complexity's sake.

## First time, at Tantan

First time Redis was proposed was at [Tantan](https://tantanapp.com/), the second largest dating app in China and a sort of Chinese Tinder. At the time we had 50-100 very powerful database servers running PostgreSQL.

To not make this post too long I will simplify the architecture a bit: Each server stored a subset of the users 'swipes', sharded by the UserId so that a specific user only had data on one server. To add new swipes, the code would locate the server belonging to the user, and then run an insert SQL statement. If you are curious I have held a couple of talk of Tantan's DB architecture, see [here](https://www.viblo.se/talks/) for a more in depth overview.

The need arose to keep track of a little piece of additional data, namely the count of swipes. Basically a single integer value for each user, with two important properties: The value would be updated very often since 'swipe' where the most common action of a user, and the value would often be read, to always show the correct value.

Our first thought (mine as well), where to put this data in Redis. A small amount of data, frequently updated and often requested felt like a perfect match for Redis. A single beefy Redis (many cores, lots of RAM type of machine) should be able to handle the load, so we would only need a couple (for redundancy). We bought (no cloud!) and installed the machines and started to configure Redis. While doing this a question rose in my mind - 'Why can't we just store this data on the shards in PostgreSQL, next to the swipes?'. The data itself would be microscopic in comparison and the additional load would also be microscopic in comparison to what these servers were already doing. After discussions in the team, they agreed! It would just add complexity to our relatively simple stack to add Redis!

Guess what, after deployment the added load couldn't barely be seen on the db servers. Success!

This is one of my favorite architecture moments. Something I think back to whenever someone proposes adding new tech, but the reasoning behind is not thought through all the way.

## Second time, at Bannerflow

After I left Tantan I joined a ad tech company called [Bannerflow](https://www.bannerflow.com/). There we built a "CMP", a web-platform for our enterprise users to create and publish ads online.

At Bannerflow, one team were building a new set of microservices to configure and publish ads to social networks like Facebook. While there are certainly complexities in regard to how format the ads to fit the various social network's API contracts, get access etc., this was not a high load scenario like at Tantan.

The team decided to add a Redis instance, for some cache of sorts. Note that this was for a system with a load not even 0.1% of Tantan's.

Unfortunately, I will not be able to explain why Redis was (thought to be) needed in this post, because I don't know the reasoning either. After the initial developer left, no-one in the team could explain it to me when we discussed it! Looking at the code, or the number of calls or any other metric I could not see any reason, and we could agree that given a bit of spare time the best would be to remove it. (Now, running a managed Redis in Azure is not a lot of work, so I could not justify rearchitect it just for simplicity, but the long term plan was clear)

I have to take this on me for not staying close enough to the team while they were designing and building the new feature, and despite skilled developers we had a (in this case) useless Redis sneaked in there. Lesson learned!

## Third time, at MAJORITY

And finally, as of 2024 I now work at the fintech company [MAJORITY](https://www.majority.com/). And surprise, surprise, they had just introduced Redis in the months before I joined!

The first usage was to cache the result of an external API call to lookup geolocation of users, so that the service in question could process location requests quicker, and also run cheaper. What I think is interesting here is that it is very reasonable to want to cache this data, no objection here.

What is less clear is what Redis added. By chance this specific service did two things for the lookup, one DB call (to a Azure SQL Database), and one Redis call. This made it very easy to compare and evaluate.

The service in question had its own DB, sharing a DB cluster with other services. This specific DB had so low amount of load that it did not even show up when looking at the cluster load in Azure. Moving the Redis usage over to the DB would result in ~2x that load, which is a big *relative* increase, but in *absolute* numbers a very minor increased load on the DB when the original load was more or less 0!

Of course, when a new tech is introduced into a tech stack, more and more parts will start using it. Same here. Soon the need arose to have locks shared between several instances of the same microservice. Since Redis was already in use, it was natural to use it for this as well.

But, looking closer it was easy to see that these locks could just as well use the locking mechanism inside the main DB (Azure SQL). Some mentioned performance and to not put more load on the DB, but just as before it was not a high performance use case, actually not anywhere near even 1 lock per second.

Just like in Bannerflow, the implementation were already done by the time I really understood it. And same as in Bannerflow, we decided to try and move away from Redis.

## Ending

Each of the three cases were unique, with different tech stacks, different domains and different load. But somehow they were still unified by the desire to use Redis!

If you nod in agreement, or are at least open for more on the same topic, there's this quite well known talk by Dan McKinley I recommend to check out: [Choose Boring Technology](https://boringtechnology.club/) By pure coincidence it's also about Redis...

*Victor 2024-03-12*