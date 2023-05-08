# Youtube on Bare Metal

Let's design Youtube, but on bare metal.

We'll take some numbers from System Design Interview by Alex Xu and Sahn Lam here:

- Assume the product has 5 million daily active users (DAU).
- Users watch 5 videos per day.
- 10% of users upload 1 video per day.
- Assume the average video size is 300 MB.

Let's take these numbers as solid enough and make some extra assumptions:

1. We want to keep every video ever uploaded, so 20 years worth.
2. Users will want the same video in many different formats. If I `youtube-dl` a video, there are about 30 total formats -- 15 audio-only (for playing audio in the background, like for youtube music, or for music videos with a static thumbnail) and 5 video only formats and 10 video + audio formats.

- Assuming that the average video is 300MB and we want to store it in these 30 formats, let's ballpark and say this will cost us about 5x the normal video cost, so each video will take 1.5GB to store on our servers in these 30 formats.
- Each video will cost 1.5GB of storage uncompressed.

- This means 1.5GB * 500K users uploading a video a day, which is 750TB of data.

```
>>> 1.5GB * 500000 -> TB

  1.5 GB × 500000 ➞ TB

   = 750 TB
```

- Going back 20 years, we'll need about 5EB of data.

```
>>> 750TB * 365 * 20 -> EB

  750TB × 365 × 20 ➞ EB

   = 5.475 EB
```

Perfect.

Now let's see how much bandwidth we need to send over the wire:

Using the estimations of users watching 5 videos a day:

```
>>> 5e6 * 5 * 1.5GB -> PB

  5000000 × 5 × 1.5 GB ➞ PB

   = 37.5 PB
```

We have 37.5PB of bandwidth to transfer over the wire.

The authors note CDN costs, $0.02 a GB, so our daily bill is $750k if we choose to serve our daily bill through CDNs.

```
>>> 5e6 * 5 * 1.5GB * 0.02$ -> GB * USD

  5000000 × 5 × 1.5 GB × 0.02 USD ➞ GB × USD

   = 750000 GB·USD
```

Let's beat that with bare metal.

## Storing 750TB/a day on bare metal

To do so, let's make a simplifying assumption: SSDs are going to sit in for CDNs.

I'm going to use the SSD I have on my laptop: The SN750 from Western Digital. Nowadays, this costs about $75/TB.

To store 750TB:

```
>>> 750TB * 75$/TB

  750 TB × (75 USD / TB)

   = 56250 USD
```

Let's assume RAID5, so we'll store about 1/4 more data, so lets round it off at 75k per day to store the data on SSDs.

```
>>> 750TB * 10$/TB

  750 TB × (10 USD / TB)

   = 7500 USD
```

Let's assume RAID0, so we'll store about 1/4 more data, so lets round it off at 10k per day to store the data on SSDs.

Since we have to replicate the same data to up to 20 different locations (to create a CDN network), let's take the HDD storage and multiply it by 20 for the worst case, and on average case lets say a video is replicated to 5 different CDNs.

On average case:

```
>>> 750TB * 10$/TB * 5

  750 TB × (10 USD / TB) × 5

   = 37500 USD
```

On worst case:

```
>>> 750TB * 10$/TB * 20

  750 TB × (10 USD / TB) × 20

   = 150000 USD
```

Still coming out on top.

## Serving 37.5PB/day over the internet

Let's assume for 10Gbps internet, the monthly cost will be about $600 in a datacenter. This can vary widely, but let's take this as best case. For our reads, we want to serve about 37.5PB/day, or about 1.125EB per month.

At best case, let's saturate that line we need about 350 of these 10Gbps lines.

```
>>> 1.125EB / 10Gbps -> months

  1.125 EB / 10 Gbit/s ➞ month

   = 342.238 month
```

And the cost per day to serve this while saturating all lines is about $7000.
This is pretty unrealistic: let's assume 10% usage at all times, for a cost of $70000 per day of bandwidth.
So we have about a 10-fold improvement in cost.

```
>>> 350 * 600$ / 30

  350 × (600 USD / 30)

   = 7000 USD
```

## Saving all of this to disk

Let's take the assumption that we're going to save all of this to disk.

```
>>> 750TB * 30 * 365 * 20 -> EB

  750 TB × 30 × 365 × 20 ➞ EB

   = 164.25 EB
```

And it costs us $10/TB:

To store the entirety of this data will cost $1.6B.

```
>>> 750TB * 30 * 365 * 20 * 10$/TB -> USD

  750 TB × 30 × 365 × 20 × (10 USD / TB) ➞ USD

   = 1,642,500,000 USD
```

Let's try to store this on AWS on EBS, where storage is $0.08/month.

One month of storage, storing all of this data:

$1.8M/month.

```
>>> 750TB * 30 * 0.08$/GB/month

  750 TB × 30 × ((0.08 USD / GB) / month)

   = 1,800,000 USD/month
```

There's 26,648,650 months of storing 750TB per day per month over 20 years:

```
>>> 750TB * 30 * 0.08$/GB/month * 26648650 months

  750 TB × 30 × ((0.08 USD / GB) / month) × 26648650 month

   = 47,967,570,000,000 USD
```

so this would cost about $48T. That's a lot more than $1.6B.

## Calculating Bandwidth

Let's see how fast we must be able to accept new videos from users + how fast we must serve from our data center:

So we'd saturate about 7 10Gbps network connections:

```
>>> 750TB / 86400 seconds -> Gbps

  750 TB / 86400 s ➞ Gbit/s

   = 69.4444 Gbit/s
```

And we have a write bandwidth of 8.6GB. Assuming a write speed of 1GB/s (which is fairly slow nowadays), we could have about 8.5 SSDs accepting writes at all times.

```
>>> 750TB / 86400 seconds -> GB/second

  750 TB / 86400 s ➞ GB / s

   = 8.68056 GB/s
```

To see how much read bandwidth we need:

And about 340 10Gbps network connections at any time.

```
>>> 37.5 PB / 86400 seconds -> Gbps

  37.5 PB / 86400 s ➞ Gbit/s

   = 3472.22 Gbit/s
```

With a 4GB/s read, we'd need about 110 SSDs to be read from at all times:

```
>>> 37.5 PB / 86400 seconds -> GB/second

  37.5 PB / 86400 s ➞ GB / s

   = 434.028 GB/s
```
