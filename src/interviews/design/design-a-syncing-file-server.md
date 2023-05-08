# Design a syncing file server (Dropbox)

- Dropbox is a design with a folder on your desktop/mobile computer,
  which syncs every so often. Syncing must be cheap, because there's a
  mobile version as well.
- Given that this is a mobile solution, network speeds can fluctuate,
  and networks can be unreliable.

- For now, assume that users can have multiple clients, but they cannot
  group edit (they can send each other files, but this is negligible).

## Back of the Envelope

- 500M total users
- 100M DAU
- syncs 100 times a day on average
- Every user has 10GB of space synced to the cloud.
- average sync is 100kb of data.

- (10B write operations a day). (100k rps)
- 10 GB of writes per second.

(S3 standard costs 1c per GB/month).
(S3 Glacier costs about 1/2c for millisecond access)

Data transfer in to S3 is free, but it costs about 10c/gb out (painful)

Also it costs $4 per 10M CRUD requests.

At 300B requests per month, the requests would cost about $120k/month.

Assuming we have to save all data, this is 1.5 EB of data (1500
petabytes).

It costs about $30M a month to store all this data on S3. (it
would be about $6M if you used glacier instant access)

Technically S3 takes care of this, but if we were to roll
our own, we'd have 3 copies of the data (ideally), so this would be 4.5
EB of data.

## Questions

- How much money would we have to charge our 500M users a month? At $5 a
  month, we would get 2.5B a month, which easily covers our bill at 99%
  margin. Since 1000 engineers cost about 2M a month, is this ok?

- What happens if two clients edit the same file concurrently?

  - Git diff? CRDTs? Should we lock a file from syncing?

- How do we save bandwidth?

  Rsync is a good way - use crc32 and MD4 hashes to calculate blocks
  that have changed, and only send them afterwards.

  For diffing the linux kernel (24MB) in the rsync paper, it only took 2
  minutes on a 50 MHz computer, compared to 4 minutes on diff. Diff
  generated a file of ~2.1MB, whereas rsync produced a 1MB file with a
  block size of 500.

  Since this is parallelizable, and mobile phones have a clock speed 20x
  that of the paper in 1996, we can assume that an rsync like algorithm
  would be able to calculate the diff in a few seconds for a 25MB file,
  and send it within a few seconds (assuming 100KB/s upload, which is
  slow).

  We could also compress the data (rsync didn't in the figures above for us).
  Assuming a 1MB text file, it's reasonable with brotli/lz4/zstd to
  compress to 5x, so only needing to transfer 200kb. You can tune this
  as well, (zstd allows you to choose between 25 compression
  levels).

  This also allows us to checkpoint our uploads, since we can compress
  and send files in chunks, which is a better user experience for those
  on bad internet.

- What are the constraints we need? Every action must be causally
  ordered (using a vector clock). Every action, once acknowledged cannot
  be done out of order (file corruption reasons, like appending to a
  file then deleting it will cause corruption/a bad state if done in
  reverse).

## Architecture

- If we use S3, we only need 3 things.
- Stateless clients that handle the uploads/downloads
- S3 to handle all of our state (and handle deduplication)
- Some metadata server which holds pointers to the file in S3.
- We may need some queues for messages to send from S3 to the metadata
  server for completed file syncs (DAG Processing).

