# EDNS

EDNS Client Subnet allows a recursive DNS resolver to specify the subnet for the host or client when amking a DNS query -- it is used to speed up the delivery of data from CDNs, by allowing better use of DNS-based load balancing to select a service address near the client.

EDNS can be used to resolve a hostname to a CDN that is close to the IP's subnet, and then serve requests that way.
