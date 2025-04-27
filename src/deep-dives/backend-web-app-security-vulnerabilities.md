# Backend WebApp Security Pitfalls

## Constant Time Comparisons

Comparing secrets without using true constant time comparisons can leak
information through timing differences.

Imagine you have a verify function:

```python
def verify(inp):
    if len(inp) != len(secret):
        return False
    for a, b in zip(inp, secret):
        if a != b:
            return False
    return True
```

If the length is not correct, you'll always get the same result through
timing knowledge -- therefore, you can use the verify function to get
the correct length of the secret, by generating different length inputs.

Secondly, you can use the second part of the function, the byte by byte
comparison, to figure out how many bytes you have correctly guessed,
starting from the beginning of the string. Since there are only 256 bits
in every byte, you can first find the length of the string (assume that
the secret's length is 16 bytes). In general, to get the secret at 50%
chance, you'd need this many guesses, which is far too much:

$$
(2^8)^{16}
$$

$$
(2^8)^{16} = 2^{128} = 3.4028237e+38
$$

$$
\frac{2^{128}}{2} = 2^{127} = 1.7014118e+38
$$

Even if we could do a billion checks a second, this is still more than a
billion years to check everything.

However, if you can first guess the length (assume this is a constant
time operation, since we can use the first part of the function) and
then we can use the second part of the function to verify that we've
placed the correct bit, so, we only need on average to guess 1/2 the
space to get the first byte correct, and then we guess the next byte
independently of the previous one (since we would simply set the first
value to the correct byte).

So, the equation becomes the following:

$$
\text{Total Guesses} = \sum_{i=1}^{n} (\text{Guesses for Byte } i)
$$

Where we have a secret of length 16, so we fix n to 16 and we set the
state space of guesses to $2^8$ for a byte.

$$
\text{Worst-Case Guesses} = \sum_{i=1}^{16} (2^8) = 16 \times 256 = 4096
$$

To get the 50% guess chance, we can divide that by 2.

$$
\text{Average-Case Guesses} = \sum_{i=1}^{16} (2^7) = 16 \times 128 = 2048
$$

Since we said we could do a billion operations a second this is solvable
in a microsecond or so, down from a billion years.

## Predictable Identifiers: Insecure Direct Object References

Using sequence or predictable IDs in API urls should always be checked.
As long as authorization checks are in-place, technically this is fine,
however, it leaks information about your implementation that you might
not want users to know.

Take for example a safe case -- you're building a website that tracks
the books you've read, and each book is given a primary key in the url
(reader.com/book/{1..n}) that can be used to uniquely identify it. This
is fine, as long as users cannot create new books that are not
incrementally increasing.

However, if a user can create a book with an arbitrary ID, they can do a denial
of service attack on the endpoint. They would create an id for every
possible id (assuming a 4-byte unsigned integer, this would be 4.3B),
and then break the API's ability to create new books.

This also has problems for reads -- you can hypothetically degrade
performance by creating blocks of unused books, so the rdbms has to jump
around in memory to find books that should be sequentially ordered
in-memory, and thus fast to pull from in-memory cache.

You can also use this during an authorization breach -- say you know a
particular user's id that you want to compromise, and you know their
resource you'd like (say their employee information). If you get access
to the whole database, you can dump it and read it later, so without
encryption at rest, there's no protection. However, if you can break a
smaller part, say just read employee information, and you know all the
unique ids, it's a simple issue of making sequential API requests. If
you have UUIDs, assuming they're 16 bytes each, to get one employee's
information, you'd have to guess 128 bits **per employee**, which would
be basically impossible. Even if the service had everybody in the world
($2 ^ 33$ employees), you'd still have to make a $2 ^ 95$ guesses to
even get a single hit, which is basically impossible to do.

## Insufficient Input validation

Failing to properly validate or sanitize input before sending it to an
interpreted program. The most common ones are giving up control to your
SQL database by allowing unprepared queries, crashing your service with
a buffer overflow, getting control of files you shouldn't, like
`/etc/passwd`, or even just taking control of the server itself.

Imagine a REST endpoint that takes a search parameter, e.g.
`/search?q={term}`, where `{term}` is user submitted. The user knows
this is a direct SQL query, so they submit `foo OR 1 = 1`, to make the
where clause always return true, returning the entire contents of the
database table. You could also look inside the database or query another
table as well.

Always use parameterized queries, escape input and validate correctness
of inputs.

## Insecure Serialization and Deserialization

Accepting or processing serialized data from untrusted sources without
restrictions.

Deserialization of untrusted data can allow for remote code execution,
replay attacks, or injection. Take for example, a python API that takes
a cookie as a pickle and then deserializes it. This allows the user to
craft a cookie that would execute system commands, leading the user to
take control of the server.

Someone could also zip bomb a service -- creating a small payload that
explodes when deserialized, if the given format is compressed in input,
and uncompressed for use. One example is 42.zip, which is 42KB in size.
It contains 4 layers of nested zip files in sets of 16, with each
containing (2^32 bytes of data) (4GB), so the entire payload is 4.5PB in
size.

Similar things can be done to XML parsers, like the billion laughs
attack, where you define nested entities that balloon up into gigabytes
of data. You define some data that nests extra data.

```xml
<?xml version="1.0"?>
<!DOCTYPE lolz [
 <!ENTITY lol "lol">
 <!ELEMENT lolz (#PCDATA)>
 <!ENTITY lol1 "&lol;&lol;&lol;&lol;&lol;&lol;&lol;&lol;&lol;&lol;">
 <!ENTITY lol2 "&lol1;&lol1;&lol1;&lol1;&lol1;&lol1;&lol1;&lol1;&lol1;&lol1;">
 <!ENTITY lol3 "&lol2;&lol2;&lol2;&lol2;&lol2;&lol2;&lol2;&lol2;&lol2;&lol2;">
 <!ENTITY lol4 "&lol3;&lol3;&lol3;&lol3;&lol3;&lol3;&lol3;&lol3;&lol3;&lol3;">
 <!ENTITY lol5 "&lol4;&lol4;&lol4;&lol4;&lol4;&lol4;&lol4;&lol4;&lol4;&lol4;">
 <!ENTITY lol6 "&lol5;&lol5;&lol5;&lol5;&lol5;&lol5;&lol5;&lol5;&lol5;&lol5;">
 <!ENTITY lol7 "&lol6;&lol6;&lol6;&lol6;&lol6;&lol6;&lol6;&lol6;&lol6;&lol6;">
 <!ENTITY lol8 "&lol7;&lol7;&lol7;&lol7;&lol7;&lol7;&lol7;&lol7;&lol7;&lol7;">
 <!ENTITY lol9 "&lol8;&lol8;&lol8;&lol8;&lol8;&lol8;&lol8;&lol8;&lol8;&lol8;">
]>
<lolz>&lol9;</lolz>
```

The same attack has been done to YAML parsers, since it supports macro
expansions as well.

```yaml
a: &a ["lol","lol","lol","lol","lol","lol","lol","lol","lol"]
b: &b [*a,*a,*a,*a,*a,*a,*a,*a,*a]
c: &c [*b,*b,*b,*b,*b,*b,*b,*b,*b]
d: &d [*c,*c,*c,*c,*c,*c,*c,*c,*c]
e: &e [*d,*d,*d,*d,*d,*d,*d,*d,*d]
f: &f [*e,*e,*e,*e,*e,*e,*e,*e,*e]
g: &g [*f,*f,*f,*f,*f,*f,*f,*f,*f]
h: &h [*g,*g,*g,*g,*g,*g,*g,*g,*g]
i: &i [*h,*h,*h,*h,*h,*h,*h,*h,*h]
```

Don't use serialization or deserialization that can allow for executing
commands. You can easily fork bomb to take down a node or exfiltrate
data.

You can also fork bomb with bash:

```bash
:(){ :|:& };:
```

## Excessive Data Exposure & Verbose Errors

Sending more data than necessary or including sensitive details in API
responses allow attackers to glean information about the API it's
targeting. For example, if you have debug logs that show the database
schema, table name, or any other relevant metadata, an attacker can use
that and keep it for when another exploit occurs.

You should always sanitize logs, never allow for debug logs to make it
to the user, and keep to minimal exposure, returning fields required by
the client.

## Architectural Flaws

### Overexposed or Internal APIs

Internal or overexposed APIs should only be reachable from a VPN or
internal network that only servers internally should be able to see.
Maintain a list of APIs and make sure to retire unused APIs (with
metrics) and revise security concerns from time to time. Use API
gateways to enforce isolation between services.

### Improper Trust Boundaries

Assume you have service A and B. A User can call service A, and service
A can call service B for data. A compromise of service A allows users to
also compromise B. Services should have a service mesh or mTLS so
unauthenticated users cannot call arbitrary services. Use roles/scopes
so services can only call what they need to know.

### Improper API Versioning

Not retiring legacy endpoints, because attackers can abuse them when
vulnerabilities occur, increasing attack surface, but also because a
compromise in a less secure endpoint can be an entrance into compromise
a secure endpoint.

### Weak Authorization Models

Authentication (Identity) and Authorization (what they can do). If you
have weak authentication, other people can spoof a user they shouldn't.
If they spoof a user, and there are weak authorization checks, they can
get access to other parts of the app. JWTs are particularly bad, because
a library may allow for an unsigned token, or a token with alg:none, and
let attackers forge their identity.

### Rate Limiting

If you don't limit how often clients can all APIs, without rate limits
and quotas, attackers can brute force credentials, enumerate IDs, and
cause denial of service by flooding requests. If you have a `/login`
endpoint that allows many POST attempts per minute, you can try to guess
anybody's password or also hog the database for yourself, denying
service from other (legitimate) users.

## Deployment & Infrastructure Misconfigurations

Exposing data storage resource to public access, or allowing overly
broad access policies. Another issue is giving cloud service roles too
many permissions.

Say you allow for public or misconfigured S3 buckets -- if you allow
writes from anybody, that's an issue, but allowing anybody to read from
a bucket can allow them to keep downloading from a bucket and charging
you all your money.

Regularly scan for public buckets, with AWS Trusted Advisor.

## Poor Key/Secret Management

If you hold your keys in version control, anybody can see your secrets.
If you don't rotate secrets, you risk an old credential being leaked and
an attacker being able to see all your data in the future.

Secrets should be encrypted at rest, keys should be rotated, and code
should be audited for secrets. Use a vault like KMS or Hashicorp Vault
for managing secrets.

## TLS Misconfiguration

Using HTTP, old TLS version, or weak ciphers.
Without secure TLS, attackers can MITM traffic. Credentials, and cookies
can be hijacked. TLS 1.2 even has some vulnerabilities, since it
supports insecure cipher suites. Test your TLS configuration with tools
to ensure strong security.

## Insufficient Logging & Monitoring

If you don't log security related events or logs for anomalies, you
won't know when an attacker has stolen all your information. Log all
authentication attempts, failures, and critical system errors. Use
centralized log management and set alerts.
