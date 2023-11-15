---
title: sockets-introduction
---

# Sockets: Introduction

Prev: [file-locking](file-locking.md) Next: [sockets-unix-domain](sockets-unix-domain.md)

Sockets are a method of IPC that allow data to be exchanged between applications, either on the same host or on different hosts connected by a network.

## Overview

In a client-server scenario, applications communicate with sockets like so:

- An application creates a socket. Both sides require a socket.
- The server binds its socket to a well-known address (name) so that clients can locate it.

A socket is created with the `socket` system call, which returns a file descriptor used to refer to the socket.
```c
fd = socket(domain, type, protocol);
```

### Communication domains

Sockets exist in communication domains, which determines:

- the way to identify the socket (the format)
- the range of communication (between the same host or between applications on different hosts)

Most systems have the following domains:

- `AF_UNIX`, for communication between applications on the same host.
- `AF_INET`, communication between applications running on hosts connected on IPv4.
- `AF_INET6`, communication between applications running on hosts connected on IPv6.

Summarized thusly:


| Domain   | Communication performed | Communication between applications     | Address format                           | Address structure                         |
|----------|-------------------------|----------------------------------------|------------------------------------------|-------------------------------------------|
| AF_UNIX  | within kernel           | on same host                           | pathname                                 | sockaddr_un                               |
| AF_INET  | via IPv4                | on hosts connected via an IPv4 network | 32-bit IPv4 address + 16-bit port number | sockaddr_in                               |
| AF_INET6 | via IPv6                | on hosts connected                     | via an IPv6 network                      | 128-bit IPv6 address + 16-bit port number | sockaddr_in6 |

Each implementation also provides stream and datagram sockets, with the following characteristics:

| Property                      | Stream | Datagram |
|-------------------------------|--------|----------|
| Reliable delivery?            | Y      | N        |
| Message boundaries preserved? | N      | Y        |
| Connection-oriented?          | Y      | N        |

### Socket System Calls

- `socket` creates a new socket.
- `bind` binds a socket to an address, so clients can locate the socket.
- `listen` to allow a stream socket to accept incoming connections from other sockets.
- `accept` accepts a connection from a peer application on a listening socket stream.
- `connect` establishes a connection with another socket.

```c
#include <sys/socket.h>
int socket(int domain, int type, int protocol); // Returns file descriptor on success, or –1 on error
```

```c
#include <sys/socket.h>
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen); // Returns 0 on success, or –1 on error
```

```c
struct sockaddr {
    sa_family_t sa_family; /* Address family (AF_* constant) */
    char sa_data[14]; /* Socket address (size varies according to socket domain) */
};
```

- Stream sockets are either active or passive. A socket created with `socket` is active, and can be used in a `connect` call to establish a connection to a passive socket.
- A passive socket is one that has been marked to allow incoming connections by calling `listen`.

## Stream Sockets

1. The `socket` system call creates a socket, which is like a telephone (it allows for bidirectional communication).
2. One application calls `bind` to bind the socket, `listen` to mark that it is ready for connections.
3. The other application establishes the connection with `connect` and the address of the other party.
4. The application that called `listen` accepts the connection using `accept`. Accept blocks until the opposing party is ready with `connect`.
5. Data can be send using `send` and `recv`, and sockets can be closed with `close`.

```c
#include <sys/socket.h>
int listen(int sockfd, int backlog); // Returns 0 on success, or –1 on error
```

Accept is used to accept an incoming connection. If there are no pending connections, the call blocks until one arrives.

```c
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); // Returns file descriptor on success, or –1 on error
```

Connect connects the active socket to the listening socket on `addr` and `addrlen`.

```c
#include <sys/socket.h>
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen); // Returns 0 on success, or –1 on error
```

To shutdown a socket, `close` or `shutdown` can be used.

## Datagram Sockets

Datagram sockets have a different flow.

1. The socket system call is like setting up a mailbox, in a location where the postal service delivers and picks up letters to said mailbox.
2. In order to allow another application to send it messages, an application uses `bind`, which allows messages to be sent to it.
3. To send a message, an application calls `sendto`, with the bound socket.
4. To receive a message, an application calls `recvfrom`, which blocks until a message is received. This also allows for replies, since sockets are labeled with their sending address.
5. Unneeded sockets are cleaned up with `close`.

### Exchanging Datagrams: `recvfrom` and `sendto`

```c
#include <sys/socket.h>
ssize_t recvfrom(int sockfd, void *buffer, size_t length, int flags,
struct sockaddr *src_addr, socklen_t *addrlen); // Returns number of bytes received, 0 on EOF, or –1 on error
ssize_t sendto(int sockfd, const void *buffer, size_t length, int flags,
const struct sockaddr *dest_addr, socklen_t addrlen); // Returns number of bytes sent, or –1 on error
```

`recvfrom` and `sendto` work like `recv` and `send`.

### Using `connect` with datagram sockets

Using `connect` on datagram sockets has the kernel give an address to a socket. This allows usage of `read` and `write`, but also makes calling easier by not requiring the address to be passed in every time.

Prev: [file-locking](file-locking.md) Next: [sockets-unix-domain](sockets-unix-domain.md)
