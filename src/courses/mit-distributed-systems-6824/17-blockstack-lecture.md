---
title: "Blockstack"
---

# Blockstack

6.824 2022 Lecture 20: Blockstack (2016)

topic today: decentralized apps
  apps built in a way that moves control over data into users's hands
    and out of centrally-controlled web sites
  many people are exploring this general vision
    early P2P apps, keybase, solid, smart contracts, etc
  speculative, not clear what will happen
  this lecture draws on later developments by Blockstack
    now a company, with a fuller design for decentralized apps
    it has users and apps written for it
    
old: a typical (centralized) web site
  [user browsers, net, site's web servers w/ app code, site's DB]
  users' data hidden behind proprietary app code
  e.g. blog posts, gmail, piazza, reddit comments, photo sharing,
    calendar, medical records, &c
  this arrangement has been very successful
    it's easy to program
    e.g. ebay s/w can see all users' bids, even though users can't
  why is this not ideal?
    users have to use this web site's UI if they want to use their data
    web site sets (and changes!) the rules for who gets access
    web site may snoop, sell information to advertisers
    web site's employees may snoop for personal reasons
    disappointing since it's often the user's own data!
  a design view of the problem:
    the big interface division is between users and app+data
    app+data integration is convenient for web site owner
    but HTML as an interface is UI-oriented.
      and is usually not good about giving users control and access to data

new: decentralized apps
  [user apps, general-purpose cloud storage service]
  run apps on users' computers, ipads, browser javascript, &c
    data in cloud storage providers
    users pay providers -- users own their data
    users control access
    users can share data with each other
    users can use whatever apps they want with their own data
  this architecture separates app code from user data
    the key interface is between user+app and data
    so there's a clearer notion of a user's data, owned/controlled by user
    much as you own the data on your laptop, or in your Athena account

requirements for the storage system
  we care about its design a lot, since storage is now a primary API
  in the cloud, so can be accessed from any device
  storage design can't be app-specific
    general-purpose, like a file system or k/v store or DB
  paid for and controlled by user who owns the data
  we want sharing between users for multi-user apps
  permissions
    user vs user
    app vs app: i don't want a game to look at my e-mail!
  need a way to find other user's data, name users for access ctl
  not impossible: Amazon S3 has some of this flavor

how might a decentralized application work?
  app: a to-do list shared by two users
    [UI x2, check-box list, "add" button]
  users U1 and U2 run apps on their computers
    maybe as JavaScript in browsers, or iPad app
    the apps read other user's public data, write own user's data
  both contribute list items
  both can mark an item as finished
  each user has a file with to-do items
    and a file with "done" marks
    each stored by their storage provider
  each user's UI code periodically scans the other user's to-do files
  the app doesn't have any associated server, it just uses the storage system

what's the point?
  easier for users to switch apps
    data not hidden inside web sites
    data not tied to apps
  easier to have apps that look at multiple kinds of data
    calendar/email/todo, or backup, or file browser
  privacy vs snooping (assuming end-to-end encryption)

why might this vision be difficult to realize?
  sharing requires standards for structuring stored data
    both file formats, and larger arrangements
    no longer private business of web sites
    history speaks on both sides (JPEG, Microsoft Word)
  probably bad for performance
  per-user FS-like storage much less flexible than SQL DB
    e.g. server-side execution of complex SQL
  sometimes you may need a trusted/central server
    e.g. to generate reddit front page, indexes, vote counts
    e.g. to look at all users' auction bids w/o revealing
  cryptographic privacy/authentication makes everything else harder
    groups, revocation
  not clear there are killer advantages to drive adoption

now for Blockstack
  they started out just with decentralized naming
  later papers -- and company -- pursuing decentralized apps
  
why is naming a concern?
  Blockstack wants to allow sharing among potentially all humans
  need a way for humans to unambiguously specify who to share with &c
  no existing system does what they need
  name -> location of user's data, so multiple users can interact
  name -> public key, for end-to-end data security
    so I can check I've really retrieved your authentic data
    so I can encrypt private data so only my co-workers can decrypt it
    since storage system is not trusted
  this is a public key infrastructure (PKI)
  PKI critical to many global security ideas e.g. secure e-mail
    exists for web sites -- https certificates
    but no good global PKI for human users
  so Blockstack started with a PKI -- a naming scheme for users

Blockstack claims naming is hard, summarized by "Zooko's triangle":
  1. unique / global -- each name has the same meaning to everyone
  2. human-readable
  3. decentralized -- we don't need anyone's permission to create/use names
  claim: all three would be valuable
  claim: any two is easy; all three is hard
    without central entity, how to decide who gets "rtm"?

example for each pair of properties?
  unique + human-readable : e-mail addresses
  unique + decentralized : randomly chosen public keys
  human-readable + decentralized : my contact list

summary of how Blockstack gets all three of Zooko's properties?
  Bitcoin produces an ordered chain of blocks
    and everyone agrees on the order, even in the face of malice
  Blockstack embeds name-claiming records in
    meta-data of valid bitcoin transactions
  [diagram: blocks, naming operations embedded]
  if my record claiming "rtm" is first in Bitcoin chain, I own it
    blockstack peers watch the bitcoin chain
    they all enforce rules
    e.g. what if i claim "rtm", then someone else claims "rtm"
    first-come-first-served policy
  unique (== globally the same)?
  human-readable?
  decentralized?

now that I control "rtm", we'll see that Blockstack will
  let me point it at my blog posts, open source contributions,
  photo collection, to-do list, public keys, &c.
and then others can find my stuff once they know I'm "rtm".

is this kind of name space good for decentralized apps?
  good: I can tell you someone's name, and you can use it (global, unique).
  good: we can probably remember the names (human readable).
  good: no-one can block access by censoring the name system (decentralized).
  bad: human-readable names won't be very meaningful if globally unique
       I probably can't be "rtm" -- someone else likely to have taken it.
       Hard for you to guess that I'm "rtm229".
       You might think "rtm@mit.edu" is sure to be me.
       but blockstack is FCFS, it doesn't check!
  bad: how can I find your Blockstack name?
  bad: how can I verify that a Blockstack name is really you?

alternate naming approaches:
  Keybase adds re-inforcement via linking to other naming systems
    (e.g. e-mail or github name), agreement with existing friends
  could use public keys directly, no human-readable names
    people exchange their keys out-of-band, e.g. on paper
    each person keeps separate "contact list" with names they understand
    naturally decentralized
    no need for uniqueness mechanism, so no need for Bitcoin
  could have central entity that reliably verifies human identity
    maybe tied to passports, drivers licences, social security #s, &c

what are the pieces in Blockstack decentralized app design?
  (much of this is from their later company white-papers)
  [bitcoin chain, BNS servers, Atlas, Gaia, S3, client apps]
  Bitcoin's block-chain
    with embedded Blockstack name operations
  Blockstack servers (BNS)
    read Bitcoin chain
    interpret Blockstack naming records to update DB
    serve naming RPCs from clients
    name -> zone hash, public key
  Atlas servers -- store "zone files"
    a name record in bitcoin maps to a zone file in Atlas
    zone file indicates where my Gaia data is stored
    keyed by content-hash, so items are immutable
    Atlas keeps the full DB in every server
  Gaia servers
    separate storage area for each user
    key -> value
    gateway to Amazon S3, Dropbox, &c
      Gaia makes them all look the same, acts as gateway/translator
    user's profile contains user's public key, per-app public keys
    user can have lots of other files, containing app data
    apps sign data in Gaia
      owner can update as well, as long as correctly signed
    for private data, apps can encrypt

BNS server details
  BNS servers have to ignore invalid Blockstack records
  BNS servers enforce bitcoin payments to burn address
    why require payment to register a name?
    prevent people from registering every single useful name
    free stuff tends to be abused
  you need to use a BNS server you trust
    maybe run it yourself
    can check, if you need to, by looking at the block-chain

how does user U1's app fetch user U2's data?
  ask BNS server to look up "U2"
    yields content-hash of U2's zone file, and U2's pub key
    (U1 has to trust its BNS server)
  ask Atlas to look up hash, get zone file
    don't have to trust Atlas, since U1 has the hash
  zone file has a link to a Gaia storage locker
  ask Gaia for U2's profile file
    verify with U2's public key
    extract U2's per-app public keys from profile
  ask Gaia for the file of interest
    verify with public key from U2's profile
  U1 has to trust that Gaia returned the latest version

Private key handling
  my apps run on my own computers
  my apps need a private key to write to gaia
  but I can't trust random apps with my real private key!
    e.g. a game written by an untrusted vendor
  so per-app private keys, per-app data
  Blockstack Browser manages; trusted
  private key never leaves my device(s)!
    protected at rest by a pass-phrase

It's hard to keep private keys secure!
  users often not very careful with private keys
  what if I lose my phone?
  what if I forget my key pass-phrase?
  what if I suspect loss and want to change my key?
  maybe print my private key on a sheet of paper somewhere secure?
  maybe "mother's maiden name" for key recovery?
    but then that's likely to be the weakest security link
    and it means the recovery agent needs to know my private key
    (blockstack doesn't do this)
  a vexing general problem!

Will programmers be eager to switch to this kind of architecture?
  I have programmed it a bit, seems signif harder than apache/mysql
  hard to have data that's specific to the app, vs each user
    indices, vote counts, front-page rankings for Reddit or Hacker News
  hard to both look at other users' secrets, and keep the secrets
    e.g. for eBay
  access control is more painful than with apache/mysql
    since you need to encrypt
    e.g. 6.824 group, controlled by registrar, may change, revoke &c
  so it's not clear programmers will be eager to switch.

Will users be excited by trust/privacy/decentralization arguments?
  maybe it will improve privacy of user data
    perhaps better than trusting facebook, google, &c
    to keep data private from employees, advertisers, friends, hackers
  but you still have to trust a cloud storage provider,
    and it will probably be google or amazon aws
  client app is written by facebook, or whoever!
    so, unless you audit the code, it does whatever facebook wants anyway
    so the trust advantage is perhaps not huge
  must trust storage provider to not lose data
    and to yield most recent version
    given that, maybe willing to trust Google to run my email s/w too

Will users be interested in more control over their data?
  to be able to switch photo organizers &c?
  do users want to use same data in multiple applications?
  will apps use standard storage schemes to enable switching?

Will users be willing to pay for their own storage?
  hard to beat free ad-supported services

NAME CREATION

how does one register a Blockstack name?
  (https://docs.blockstack.org/core/wire-format.html)
  the user does it (by running Blockstack software)
  user must own some bitcoin
  two bitcoin transactions: preorder, registration
  preorder transaction
    registration fee to "burn" address
    hash(name)
  registration transaction
    name (not hashed)
    owner public key
    hash(zonefile)

why *two* transactions?
  front-running

why the registration fee? after all there's no real cost.

what if a client tries to register a name that's already taken?

what if two clients try to register same name at same time?

is it possible for an attacker to change a name->key binding?
  after all, anyone can submit any bitcoin transaction they like

is it possible for Blockstack to change a name->key binding?

CONCLUSION

what do I take away from Blockstack?
  separating cloud data from applications sounds good in principle
    but developers will hate it (e.g. no SQL).
    not clear users will care.
    not clear whether users will want to pay for storage.
  surprising that we can have decentralized human-readable name allocation
  the whole thing rests on a PKI -- any progress here would be great
    to securely name human beings, map to public keys
  end-to-end encryption for privacy sound like a good idea
    private key management is a pain, and fragile
    encryption makes sharing and access control awkward
  you still have to trust vendor software; not clear it's a
    huge win that it's running on your laptop rather than
    vendor's server.

all that said, it would be fantastic if Blockstack or something
  like it were to be successful.

--- references ---

https://dataspace.princeton.edu/handle/88435/dsp019306t191k
https://econinfosec.org/archive/weis2015/papers/WEIS_2015_kalodner.pdf
