---
title: "AWS Lambda"
---
# Lambda

AWS Lambda is an event-driven, serverless computing platform. Functions can respond in ~10ms if they don't hit a cold start penalty, but 100ms - 1s cold starts are common, with an average of about 300ms.

AWS Lambda runs off of AWS Firecracker, which uses KVM. Lightweight VMs are launched in about 125ms, which are jailed with cgroups and seccomp, with a simple virtualized device model.
