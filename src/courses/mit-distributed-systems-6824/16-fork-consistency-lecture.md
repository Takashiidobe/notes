---
title: "Secure Untrusted Data Repository (SUNDR)"
---

# Secure Untrusted Data Repository (SUNDR)

6.824 2022 Lecture 18: Secure Untrusted Data Repository (SUNDR) (2004)

Why are we reading this paper?
  We routinely trust storage services, e.g Google mail, AFS, Dropbox.
  Even if organization is honest overall, can bad things happen?
    Maybe the server s/w or h/w is buggy, even exploitable.
    Maybe an attacker guessed server admin password, modified s/w.
    Maybe an employee of the cloud provider is corrupt or sloppy.
  Can we obtain trustworthy storage from non-trustworthy servers?
    This is a hard problem!
  SUNDR contains some good ideas.
  Similar ideas show up in git and blockchains.
    Keybase (acquired by zoom) is directly influenced by SUNDR
  Some of you have seen SUNDR in 6.858
    It's interesting both as a distributed system (consistency, logging)
    and for security.

Setting:
  A bunch of programmers collaborating on a project.
  They want to store their source files somewhere shared.
  They need to see each other's modifications.
  They could store their source in github, Google Drive, &c
  But they do not want to have to trust any storage service!

We don't know in advance what exactly could go wrong.
  So we'll assume the worst:
    that the server is fully controlled by a malicious adversary.
  It is intentionally trying to trick the users.
  It will not, if it doesn't want to, follow any rules or protocol.
  "Byzantine faults".
  But we do assume the adversary cannot break cryptography,
    and only has control over the server, not my client computer.

Potential goals:
  Confidentiality.
    Adversary cannot read file contents.
  Integrity.
    Adversary cannot trick clients into getting wrong file contents.
  Availability.
    Adversary can't prevent clients from accessing their files.

This paper's focus: integrity.

Integrity is real concern for source repository services!
  What if someone modifies the source in a huge project like Linux?
    Millions of lines of code!
    It might be a long time before anyone noticed.
  Paper mentions Debian server compromised in 2003.
  SourceForge compromised in 2011.
    [ http://sourceforge.net/blog/sourceforge-attack-full-report ]
  Canonical (Ubuntu) compromised in 2019.
    [ https://hub.packtpub.com/canonical-the-company-behind-the-ubuntu-linux-distribution-was-hacked-ubuntu-source-code-unaffected/ ]

Integrity is not just about preventing illegitimate modifications,
  but also about ensuring legitimate modifications all appear and in
  the right order.

An integrity example:
  Users A, B, and C are developing a simple O/S
  They store their source "in the cloud"
  We don't want the cloud storage service to be able to modify the source.
  We don't want the service to hide or re-order updates either!
    This turns out to be the real problem.
  User A adds password protection to login.c.
  User B adds remote login to net.c.
  User C creates a release tar file.
  We want C's release to have *both* A's and B's updates.
    and not *just* B's net.c.
    Since that would allow password-less remote access.
  So we want to prevent the service from revealing A's update
    but concealing B's update.

The point of this example: it's not enough to prevent the server from
  changing the data, we need to prevent it from hiding legitimate
  updates as well!
 
Naive design: users sign file contents.
  Use existing network file system (say, Dropbox) as a starting point.
    Not expecting any security guarantees from it.
  Each file contains data, Sig(SK_writer, data).
  When user writes to file, client signs with user's key.
  When user reads file, client checks signature.
    Signature check will fail if the data isn't exactly the same as when signed.
  We assume clients know public keys of all users.

What could a malicious server do in this naive design?
  Cannot send arbitrary source code to user C.
  Can send one file's data instead of another file's data.
    Possible fix: include filename in the signature.
  Can send old contents of files.
  Can send new content for some files, and old for others.
  Can claim that a file doesn't exist.
  Not good for our O/S development scenario:
    Adversary could cause C to deploy net.c without login.c change.

We need a more sophisticated security design.
  Consistent versions of files: net.c change requires login.c change.
  Latest version of files: should not be missing any changes.
  Integrity of directory contents: should not be missing any files.
  Permissions: users might not have permissions to modify every file.

Big idea in SUNDR:
  Every update to any file includes signature over current
    state visible to updating user.
  Thus B's update to net.c includes reference to A's updated login.c
  If C sees updated net.c, will also know of new login.c

Strawman design: section 3.1 from the paper.
  File system state is determined by a log of operations by users.
  Server is responsible for storing this log.
  Clients interpret the log.

Strawman details
  Log entries: fetch or modify, user, sig.
    Signature covers the entire log up to that point.
  Client step:
    Download log (other clients now wait).
    Check the log:
      Correct signatures in each entry, covering log prefix.
        (really only need to check each user's last entry)
      This client's last log entry is present.
    Construct FS state based on logged operations.
    Append client's operation and sign new log.
    Upload log (other clients can now proceed).
  Inefficient but simple to reason about.
  Example log:
    X: mod(???), sig
    A: mod(login.c), sig
    B: mod(net.c), sig
    C: fetch(login.c), sig
    C: fetch(net.c), sig

Crucial that signature covers all previous operations in the log.
  Prevents adversary from revealing the net.c change but hiding login.c change.
  If adversary omits login.c change from log, B's signature does not verify.

Could an adversary sign a fake log entry?
  It would need to know the private key of an authorized user.
  How do clients know the public keys of authorized users?
  1. All clients must be told public key of root directory owner.
  2. File system stores the public key of each file/directory owner.
  Clever: file system integrity ensures integrity of public keys.

What would happen if C did not log its fetch?
  I.e. append a "fetch" log entry even when just reading a file.
  Malicious server could give C a stale view of the log.
  When C fetches login.c, server gives log before mod(login.c).
  When C fetches net.c, server gives log with mod(login.c) and mod(net.c).
  Effectively, server pretends C had a race with A + B.
  Outcome: C uses login.c from first fetch and uses net.c from second fetch
    Oops; that is what we were trying to prevent.

When a client fetches the log, it checks that its most recent
  fetch or mod is in the log, and rejects the log if not.
  
How does logging the fetch help?
  Server can still show C the log before mod(login.c).
  But then C logs its fetch based on that log prefix,
    and remembers that fetch as its last log entry.
  Now the server cannot show mod(login.c) or mod(net.c) to C,
    since they have signatures over a log that does not
    contain C's fetch, and C is expecting to see its fetch.
  "Forking" attack.

So: the server can fork C by hiding modifications to login.c and net.c,
  but the server can then no longer show C any subsequent operations
    by A or B, since their signatures won't include C's fetch.
  The server can, however, continue to serve C's requests.
    C can't realize it's been forked just by talking to server.
  But the server has to hide all future A/B operations from C,
    since their log entry signatures won't include C's fetch.
    Similarly, server must hide C's operations from A/B.
  "fork consistency": server can fork clients, but once it
    forks, can never show operations from one fork to clients
    in the other fork.

Fork consistency is pretty good for a file system.
  Leaves strong trace of attack: impossible to cover up a fork.
  Users can detect if they can communicate outside of SUNDR.
    e.g. e-mail asking "what do you think of my last commit?"

Automated fork detection with separate trusted "timestamp box".
  Designated user is responsible for updating some file every 5 seconds.
  If client sees these updates, it's in the same "fork" as the timestamp box.
  If there is a fork, timestamp box's updates can show up in only one fork.
    Clients in the other fork won't see timestamp box's updates!

Strawman is not practical:
  Log keeps growing.
  Interpreting log gets slow.

Idea: tree of blocks reflecting current state, instead of log.
  Figure 2.
  Server stores smallish blocks, for fast retrieval/update,
    in the usual case that you're operating on just one file.
  i-handle points to table of i-number->inode mappings.
  inode contains type (file vs directory) and list of block references.
  Directory contains list of name->i-number mappings.

The blocks are immutable!
  References (keys) are cryptographic hashes of content.
  When a client asks server for a block, it sends the key,
    and client can check that returned data hashes to that key.
  So the server cannot modify the data, assuming client knows the right key.
  But neither can clients modify any blocks!

How to update?
  When client C writes a file,
    it constructs a new tree reflecting its modification.
  But new tree can share almost all blocks with old tree,
    only needs new blocks on path from modified content
    up to i-handle.
  A new i-handle for each modification.

How to maintain fork consistency with i-handles?
  A malicious server could give out old i-handle, concealing recent updates.
  We can't prevent the server from forking users, but (as with the
    straw man) we want to prevent it from merging forks and
    thus concealing its misdeeds.
  We want each new i-handle to somehow encode what came before it,
    and we want to be able to record fetches as well as modifications.

Idea: a signed "version structure" (VS) for each user.
  Figure 3.
  Stored in server.
  Contains:
    i-handle after user's last operation.
    Version vector (VV):
      For each user, how many operations that user has performed.
    Public-key signature by user.
  The point: the VV operation counts allow clients to detect
    omitted old operations, and detect attempts by server to
    merge forks.

How client U1 executes an operation (both reads and writes):
  Get all users' VSs from server.
  Validate.
  Get needed i-tables &c from block server.
  Store new i-table, i-handle with mods (if any).
  New VS:
    New i-handle.
    Increment U1's version #.
  Put VS back to server

How do version vectors evolve in correct operation?
  U1: 1,0           2,2
  U2:      1,1  1,2     2,3

How should U2 validate a set of fetched VSs?
  Check that U2's VS is up to date (so U2 must remember its own last VS).
  Check that version vectors of diff users can be totally ordered.
    e.g. 2,2 <= 2,3

What would version vectors look like if server hid an update from U2?
  U1: 1,0       [2,1]
  U2:      1,1        1,2

Do the version vectors give us fork consistency?
  can the server show future U1 VSs to U2?
    e.g. 3,1
    no: 3,1 and 1,2 cannot be ordered!
  can the server show future U2 VSs to U1?
    e.g. 1,3
    no: 1,3 and 2,1 cannot be ordered

For our A/B/C login.c net.c example, a correct execution:
  A: 1,1,1 2,1,1                something else, then modify login.c
  B:             2,2,1          modify net.c
  C:                   2,2,2    read login.c and net.c

If the server hides A's update to login.c, but reveals B's net.c,
  it will send C these vv's:
  A: 1,1,1
  B: 2,2,1
  C will compute its new VV z: 1,2,2
  But A/B/z cannot be totally ordered
    not this way:
      A 1,1,1
      B 2,2,1
      z 1,2,2
    not this way:
      A 1,1,1
      z 1,2,2
      B 2,2,1
  so C will know something is wrong.

Nice: version structures allow us to use an efficient tree
  data structure, eliminate the need for an ever-growing log,
  but can still enforce fork consistency.

Summary.
  Hard problem: integrity despite compromised servers.
  Client signatures prevent outright forgery.
  Hiding and forking are the main attacks still possible.
  Fork consistency prevents server from hiding a fork once created.
    Forking still possible, but will eventually become obvious to clients.
  No plan for recovery after a detected fork.
