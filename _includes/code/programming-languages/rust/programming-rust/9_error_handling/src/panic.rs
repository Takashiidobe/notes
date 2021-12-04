// You want to panic in a test, so calling unwrap or expect is a good way to do that.

// You can also use unwrap when you're certain that a method won't fail:

use std::net::IpAddr;
fn return_localhost() -> std::net::IpAddr {
    "127.0.0.1".parse().unwrap();
}

// panics are generally used when you cannot handle some output of a function.
// otherwise, use a result or option
