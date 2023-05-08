# Port vs Socket

A connection is identified by the following:

(Protocol, Client IP, Client Port, Remote IP, Remote Port).

A socket requires knowledge of the protocol it's using, and the IP and Port to connect to.

## How do Ports work?

Ports is a virtual identifier defining a service endpoint.

When opening a socket to a remote server, the client chooses a random port to fulfill the request. Thus, it can have up to 65k connections to as many servers.
