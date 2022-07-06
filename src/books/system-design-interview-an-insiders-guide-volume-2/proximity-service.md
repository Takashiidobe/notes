---
title: "Proximity Service"
---

# Proximity Service

Next: [nearby-friends](nearby-friends.md)

This chapter goes into the design of a proximity service, which shows
nearby attractions, like hotels, theaters, and museums.

## Step 1: Understand the Problem and Establish Design Scope

### Q/A

1. Can the user specify the search radius?
A: Let's start off with a fixed search radius, and expand it if we don't
have enough attractions nearby.

2. What's the maximum radius? (is 20km ok?)
A: Yes

3. Can a User change the search radius?
A: Yes, to 0.5km, 1km, 2km, 5km, 20km.

4. How does business information get updated? Does this need to be
   supported in real-time?
A: Business owners can update information at any time. The SLA for
updates to propagate is 1 day, but faster is better.

5. Should we account for the fact that a user might be moving while
   using the app?
A: Let's assume that the user is stationary.

### Non-functional requirements

- Low latency
- Data privacy (follow GDPR and CCPA)
- High availability and scalability. Spikes are important.

### Back of the envelope estimation

- 100 million daily active users
- 200 million businesses
- 100k seconds in a day (86.5k in actuality)
- User makes 5 search queries per day
- QPS = 1e8 * 5 / 1e5 = 5k QPS
- Business makes 1 query a week:
- QPS = 2e8 / 7 / 1e5 ~= 200 QPS

## Step 2: High-Level Design

### API Design

#### Users

`GET /v1/search/nearby`

| Field     | Description                | Type |
|-----------|----------------------------|------|
| latitude  |                            | f64  |
| longitude |                            | f64  |
| radius    | Optional, 5k meter default | i32  |

Response:

```json
{
  "total": 10,
  "businesses": [{...}]
}
```

The business object can contain information about each business. We
should take care to keep initial loads light: we can make a `light`
business page, where only important information is sent in this payload, with a link to the businesses endpoint for more detailed information. Likewise, images should be a link to an S3 object or similar, instead of being passed in the payload as base64 or similar.

#### Business API

| Endpoint                    | Notes                                 |
|-----------------------------|---------------------------------------|
| GET /v1/business/{:id}      | Detailed information about a business |
| POST /v1/businesses/        | Add a business                        |
| PUT /v1/businesses/{:id}    | Update details of a business          |
| DELETE /v1/businesses/{:id} | Delete a business                     |
### Data model

- There are more reads than writes in this model, and we need geospatial
    data. Let's defer to an SQL database.

### Schema

#### Business Table

| Field       | Type                |
|-------------|---------------------|
| business_id | i64                 |
| address     | i64 FKEY address_id |
| city        | i64 FKEY city_id    |
| state       | i64 FKEY state_id   |
| country     | i64 FKEY country_id |
| latitude    | f64                 |
| longitude   | f64                 |

Since this requires finding nearest neighbors in a space, a geospatial
index table is used for the efficient processing of spatial operations.

### High Level Design

There's two distinct services, a Business service and the users query
service.

We can have  primary-replica replication for our system.

## Algorithms to fetch nearby businesses

In real life, you might use redis' geohash or PostGIS for postgres for
geospatial data. Nonetheless, some notes follow on algorithms:

### Two-dimensional search

This involves drawing the circle around the location and finding nearby
businesses:

This would look like:

```SQL
SELECT business_id, latitude, longitude,
FROM business
WHERE (latitude BETWEEN :lat - radius AND lat + radius AND longitude
BETWEEN :long - radius and :long + radius
```

This query is inefficient because it requires a scan on the whole table,
because we can't index two separate columns on each other (we could have
an index on latitude and longitude, but that wouldn't help for range
queries like we have here.

Indexes only work on data for one dimension instead of two.

There's two options for generating an index: either a tree or a hash.

Hash options include:

- Even Grid
- Geohash
- Cartesian Trees

Tree Indexes include:

- Quadtree (R/W balanced)
- Google's S2
- RTree (Read optimized)

### Option 2: Even Grid

- An even grid involves splitting the world into small cubes, which are
    then indexed into.

- Simple, but doesn't scale, because distribution of businesses is not
    even.

### Option 3: Geohash

- Geohash divides the world recursively into a grid, which then is
base32'd. The longer the geohash prefix, the greater the precision.

Unfortunately, two locations can be close but have no shared prefix, if
they are in different boundaries.

So, a query like the following would fail.

```SQL
SELECT * FROM geohash_index WHERE geohash like 'u000%'
```

The solution is to fetch all businesses and its neighbors, since
geohashes of neighbors can be calculated in constant time.

If there are not enough businesses, we can remove a character from the
prefix and widen the search space.

### Option 4: Quadtree

A quadtree involves a tree like structure where the world is subdivided
into smaller grids, where each leaf node might be a location.

This quadtree will be in-memory, and may take a few minutes to hydrate
since it has to hydrate data.

### Operational considerations

Since this quadtree is in-memory, we might have a few copies of it. We
also need to be able to update it with added businesses, but given that
a quadtree may need to split nodes when inserting, there can be a
bottleneck.

As well, we need to update, and may deal with stale data. This should be
fine as long as it is done promptly, and our users can tolerate data
without real-time requirements.

Locking the quadtree in a multithreaded program is complicated, but can
perform well (see the quadboost paper for a CAS-based non-locking
linearizable quadtree).

## Caching

Ask the interviewer if caching is necessary. In the Quadtree or Geohash
case, it may not be necessary, as our workload fits in-memory and only
costs the access of the quadtree or geohash (either (log N) or O(1)
time).

As well, caching comes with some problems: mobile phones give a range
for latitude and longitude, which makes it hard to cache for specific
coordinates. You'd have to cache a tree, which our Quadtree already
does.

As well, if we update the underlying data structure, we need to find a
way to do so in the cache, with can cause consistency problems.

Next: [nearby-friends](nearby-friends.md)
