---
title: "design-netflix"
---
# Design Netflix

To design netflix's read side, we don't want the client to have to authenticate before picking up the next chunk of their video. To handle this, we can use 
[Signed Cookies](https://docs.aws.amazon.com/AmazonCloudFront/latest/DeveloperGuide/private-content-signed-cookies.html), which allow a user to access files from S3 that follow a regex in the resource policy (so they can access all the files that correspond to the same movie), the date/time the user can access the content, the date/time when the user cannot access content, and the IP address that users can access the content.

This way, we can fetch one signed cookie from the backend and use it to access the CDN for some n amount of times.