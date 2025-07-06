---
title: "Unsoundness and accidental features in the #[target_feature] attribute"
source: "https://predr.ag/blog/unsoundness-and-accidental-features-in-target-feature/"
author:
  - "[[Predrag Gruevski]]"
published: 2025-07-04
created: 2025-07-06
description: "Making Rust better for everyone while working on `cargo-semver-checks`"
tags:
  - "clippings"
---
*Researching the SemVer hazards of the `#[target_feature]` attribute led to finding unexpected unsoundness, discovering an "accidental feature" in Rust, [finding bugs](https://github.com/rust-lang/rust/issues/142655) [in rustdoc](https://github.com/rust-lang/rust/issues/142952), the creation of [an RFC that evolves the Rust language](https://github.com/rust-lang/rfcs/pull/3820), and the addition of a dozen new SemVer lints. My work on `cargo-semver-checks` benefits the Rust ecosystem in more ways than just preventing breakage!*

Rust 1.86 shipped an interesting new feature: the ability to apply [the `#[target_feature]` attribute](https://doc.rust-lang.org/reference/attributes/codegen.html#the-target_feature-attribute) to *safe* functions, not just `unsafe` ones!

The [release notes for this new functionality](https://blog.rust-lang.org/2025/04/03/Rust-1.86.0/#allow-safe-functions-to-be-marked-with-the-target-feature-attribute) piqued my curiosity. I had never heard of `#[target_feature]` before! Of course, I then did my usual thing: I read the docs, I poked at it in the playground, and I tried to come up with all the edge cases for (mis)using this functionality.

Eventually, I wrote a piece of code I *knew* was broken. I was *sure* `rustc` would reject it.

Except... it didn't 🤯

```
Compiling example v0.0.1 (/example)
   Finished \`dev\` profile [unoptimized + debuginfo] target(s) in 0.1s
```

It took more than three months of work (!) to wrap up everything I discovered down that particular rabbit hole. The Rust ecosystem is much better off as a result, and predominantly *not* just because `cargo-semver-checks` has new lints about the `#[target_feature]` attribute.

Let's talk about why.

- [What does `#[target_feature]` do, and when is it used?](https://predr.ag/blog/unsoundness-and-accidental-features-in-target-feature/#what-does-target-feature-do-and-when-is-it-used)
- [SemVer implications of `#[target_feature]`](https://predr.ag/blog/unsoundness-and-accidental-features-in-target-feature/#semver-implications-of-target-feature)
	- [Safe functions and methods](https://predr.ag/blog/unsoundness-and-accidental-features-in-target-feature/#safe-functions-and-methods)
	- [Unsafe functions and methods](https://predr.ag/blog/unsoundness-and-accidental-features-in-target-feature/#unsafe-functions-and-methods)
	- [Trait functions and their implementations](https://predr.ag/blog/unsoundness-and-accidental-features-in-target-feature/#trait-functions-and-their-implementations)
- [Unsoundness, or an "accidental feature?"](https://predr.ag/blog/unsoundness-and-accidental-features-in-target-feature/#unsoundness-or-an-accidental-feature)
	- [Why is this surprising? Why is it a problem?](https://predr.ag/blog/unsoundness-and-accidental-features-in-target-feature/#why-is-this-surprising-why-is-it-a-problem)
	- [We can't roll it back, so we're fixing it forward](https://predr.ag/blog/unsoundness-and-accidental-features-in-target-feature/#we-can-t-roll-it-back-so-we-re-fixing-it-forward)
- [A dozen new SemVer lints, and two rustdoc bugfixes](https://predr.ag/blog/unsoundness-and-accidental-features-in-target-feature/#a-dozen-new-semver-lints-and-two-rustdoc-bugfixes)
- [Supporting `cargo-semver-checks` means supporting work like this](https://predr.ag/blog/unsoundness-and-accidental-features-in-target-feature/#supporting-cargo-semver-checks-means-supporting-work-like-this)

## What does #\[target\_feature\] do, and when is it used?

*If you're already familiar with `#[target_feature]`, [feel free to skip ahead](https://predr.ag/blog/unsoundness-and-accidental-features-in-target-feature/#semver-implications-of-target-feature).*

`#[target_feature]` is a way to [allow a function to rely on platform-specific architecture features](https://doc.rust-lang.org/reference/attributes/codegen.html#the-target_feature-attribute). This is most useful in high-performance applications (cryptography, video encoding, etc.) where it's common to offer different implementations of a function specialized for the capabilities of the hardware where the program happens to be running.

For example, applying `#[target_feature(enable = "avx")]` on a function allows it to use the x64 architecture's [Advanced Vector Extensions](https://en.wikipedia.org/wiki/Advanced_Vector_Extensions), which add 16 vector registers able to hold up to 256 bits of data and a variety of [SIMD operations](https://en.wikipedia.org/wiki/Single_instruction,_multiple_data) over such vectors.

When encountering such a function during code generation, the compiler will feel free to emit instructions that make use of those new vector registers, even if the rest of the program might not be allowed to make use of them.

## SemVer implications of #\[target\_feature\]

*If you just want to see the unsoundness, [feel free to skip ahead](https://predr.ag/blog/unsoundness-and-accidental-features-in-target-feature/#unsoundness-or-an-accidental-feature).*

If you're wondering where you can find the documentation for the SemVer hazards of `#[target_feature]` — you're looking at it. This blog post is the definitive (and AFAIK, the only!) guide to the breakage hazards posed by `#[target_feature]`.

I'm writing this part for three reasons:

- To document my findings, because discovering all this was *very* time-consuming. I want all the details and nuance written down, so I don't have to re-discover them later.
- To allow users running into lints and breakage to understand *why* their change is accidentally breaking in a strange and non-obvious way.
- To convince you, dear reader, that the *vast majority* of the effort involved in building `cargo-semver-checks` is not writing the lints. Quite the opposite: by the time we *start* writing lints, the work is already 99% complete!

Broadly speaking, the SemVer rules are mostly identical between top-level functions and methods / associated functions. But functions in traits have their own, more complex rules.

We'll stick to considering single [target triple](https://doc.rust-lang.org/stable/rustc/platform-support.html) breakage cases here, because referencing a feature name on an inappropriate target triple is an *immediate* compilation error — `cargo check` fails even if you never use the item in question.

Let's dig in!

### Safe functions and methods

Consider the following safe function:

```rust
#[target_feature(enable = "avx")]
pub fn example() {
    // ...
}
```

This function is only callable when the feature is *syntactically* present:

```rust
// This item only exists when
// the \`avx\` feature is present.
#[cfg(target_feature = "avx")]
fn this_works() {
    example();
}

// Here we conditionally call \`example\`
// if the \`avx\` feature is found at runtime.
// This does not work!
fn this_is_a_compile_error() {
    if is_x86_feature_detected!("avx") {
        example();
        // error[E0133]: call to function \`example\` with
        //   \`#[target_feature]\` is unsafe and
        //   requires unsafe block
    }
}
```

Therefore, *any* new target feature addition is a major breaking change: it breaks calls to the affected function that weren't gated on a `#[cfg]` for that newly added feature.

### Unsafe functions and methods

Let's start with the following function:

```rust
#[target_feature(enable = "avx")]
pub unsafe fn example() {
    // ...
}
```

Adding an additional feature to the list of enabled features is *generally* a major breaking change:

```rust
// Calling this function now also requires \`avx2\`.
// That imposes a new safety precondition on callers,
// which is a major breaking change.
#[target_feature(enable = "avx,avx2")]
pub unsafe fn example() {
    // ...
}
```

There are two exceptions. One is when the additional feature was [already implied](https://doc.rust-lang.org/reference/attributes/codegen.html#available-features) by an existing feature:

```rust
// \`sse4.2\` is now also listed as required.
// But it was already *implicitly* required:
// the existing \`avx\` feature implied \`sse4.2\`.
//
// This applies recursively: \`sse4.2\` implies \`sse4.1\`,
// which implies \`ssse3\` etc.
// Adding any of those features is *not* breaking!
#[target_feature(enable = "avx,sse4.2")]
pub unsafe fn example() {
    // ...
}
```

The second exception is when the added feature is already globally enabled on that target triple. For example, requiring the `sse2` feature on any `unsafe` function is not a major breaking change on `x86_64-unknown-linux-gnu` because `sse2` is always enabled there.

This is a good example of how a code change can be SemVer-breaking only on *some* target triples. There are other ways too!

`cargo-semver-checks` by default checks the target triple corresponding to your Rust toolchain. It can be instructed to check a different target triple using `--target <BUILD_TARGET>`. If your crate has any target-specific code, it's a good idea to invoke `cargo-semver-checks` for each target triple your crate supports.

### Trait functions and their implementations

Today, only `unsafe` trait functions that include a default implementation are allowed to include `#[target_feature]`.

So neither of the following is valid Rust today (~1.88 or earlier):

```rust
pub trait NonWorkingExample {
    #[target_feature(enable = "avx")]
    fn not_unsafe() {}
    // error: \`#[target_feature(..)]\` cannot be applied
    //        to safe trait method

    #[target_feature(enable = "avx")]
    unsafe fn no_default_implementation();
    // error: attribute should be applied to a function definition
}
```

As a start, the same rule from regular `unsafe` functions applies here as well: it's a breaking change for a trait function to require a new feature that was not previously implied and which is not globally enabled by default.

But traits [which are not sealed](https://predr.ag/blog/definitive-guide-to-sealed-traits-in-rust/) can also be implemented in downstream crates. Consider the following case, then:

```rust
// In crate \`upstream\`:
pub trait MyTrait {
    /// SAFETY: No obligations other than
    ///         the \`#[target_feature]\` attribute.
    #[target_feature(enable = "avx")]
    unsafe fn example() {
        // ...
    }
}

// In crate \`downstream\`:
pub struct MyType;

impl upstream::MyTrait for MyType {
    /// SAFETY: Same as upstream, just the
    ///         \`#[target_feature]\` obligation.
    #[target_feature(enable = "avx")]
    unsafe fn example() {
        // ...
    }
}
```

What happens if `upstream::MyTrait::example` removed its `#[target_feature]` attribute? Say the function remains `unsafe`, because [making the trait function safe is a major breaking change](https://github.com/obi1kenobi/cargo-semver-checks/blob/f2799bfe9d94dabe14a50ae1cad58842b0c0ddd1/src/lints/trait_method_unsafe_removed.ron). We get:

```rust
// In crate \`upstream\`:
pub trait MyTrait {
    /// SAFETY: Always safe to call.
    unsafe fn example() {
        // ...
    }
}
```

Now imagine a hypothetical crate `end_user` which depends on `upstream`, but may or may not be used together with `downstream`. Say `end_user` depends on the updated version of `upstream` and does the following:

```rust
// In crate \`end_user\`:
pub fn do_thing<T: upstream::MyTrait>(value: T) {
    // SAFETY: Per the \`upstream::MyTrait\` docs,
    //         \`example()\` is always safe to call.
    unsafe {
        value.example();
    }
}
```

`do_thing()` is generic over `upstream::MyTrait` implementations.`downstream::MyType` is one such implementation, so calling `do_thing()` with a `downstream::MyType` value is allowed.

But calling `downstream::MyType::example` *still carries* a safety obligation: we never removed its `#[target_feature(enable = "avx")]` requirement! Calling `end_user::do_thing()` with `downstream::MyType` would therefore be *unsound* — it causes [undefined behavior (UB)](https://predr.ag/blog/falsehoods-programmers-believe-about-undefined-behavior/).

Okay, so *removing* a feature from `#[target_feature]` is a major breaking change when the trait isn't sealed, because it can cause UB in implementations of that trait. That's easy enough, [we can lint](https://github.com/obi1kenobi/cargo-semver-checks/blob/f2799bfe9d94dabe14a50ae1cad58842b0c0ddd1/src/lints/trait_method_target_feature_removed.ron) [for that](https://github.com/obi1kenobi/cargo-semver-checks/blob/f2799bfe9d94dabe14a50ae1cad58842b0c0ddd1/src/lints/pub_api_sealed_trait_method_target_feature_removed.ron).

## Unsoundness, or an "accidental feature?"

Hang on though. Surely this must be a compile error, right?

When you remove `#[target_feature]` from a function, you are widening the API: calls that were previously banned are now allowed. Saying "my `impl` of this trait can actually be used without this feature" is okay — the `impl` is broader than the trait. This general concept is called "refinement" and [there's an open RFC to add a flavor of it to Rust](https://rust-lang.github.io/rfcs/3245-refined-impls.html).

But if you remove `#[target_feature]` from a *trait* function, then you leave the trait broader than the `impl`! Downstream implementations no longer satisfy the full API defined by the trait.

Implementations that don't satisfy the trait's full API are normally rejected by Rust. Here's one example:

```rust
pub trait BroadTrait {
    fn example() -> i64;
}

pub struct Narrow;

impl BroadTrait for Narrow {
    // Actually, we don't feel like
    // returning the \`i64\` the trait promised.
    // We're narrower than the trait.
    fn example() {}
    // error: method \`example\` has an incompatible type for trait
}
```

Okay. Then we'd expect removing `#[target_feature]` from the trait to cause a compile error on the mismatched `impl`, right?

Try it for yourself: [playground](https://play.rust-lang.org/?version=stable&mode=debug&edition=2024&gist=24e13f09afeee2ac8932706ece38bc43)

```rust
pub trait NoFeatures {
    // SAFETY: Always safe to call.
    unsafe fn example(&self) -> i64 {
        0
    }
}

pub struct NeedsAvx;

impl NoFeatures for NeedsAvx {
    // SAFETY: May only be called
    //         on \`avx\`-capable hardware.
    #[target_feature(enable = "avx")]
    unsafe fn example(&self) -> i64 {
        1
    }
}

fn main() {
    if is_x86_feature_detected!("avx") {
        // SAFETY: \`avx\` hardware is present.
        unsafe {
            // This prints \`1\`, showing that
            // we did not use the default impl.
            println!("{}", NeedsAvx.example());
        }
    }
}
```

Invoking `cargo run` here produces:

```
Compiling example v0.0.1 (/example)
   Finished \`dev\` profile [unoptimized + debuginfo] target(s) in 0.83s
    Running \`target/debug/example\`
1
```

No compile error! 😵 Okay, well then consider this other code:

```rust
pub fn takes_generic<T: NoFeatures>(value: T) -> i64 {
    // SAFETY: The trait said this is always safe to call.
    unsafe {
        value.example()
    }
}

pub fn undefined_behavior() -> i64 {
    let value = NeedsAvx;

    // Recall that the \`NeedsAvx\` implementation
    // of \`NoFeatures::example()\` demands the \`avx\` feature.
    //
    // This code is unsound!
    // We caused UB *without* an \`unsafe\` block!
    takes_generic(value);
}
```

Oops, we caused undefined behavior 💥 ([playground link](https://play.rust-lang.org/?version=stable&mode=debug&edition=2024&gist=31828ca9d3df4c894ba65ec2f74c0f32))

Based on the reaction when I [reported this issue](https://github.com/rust-lang/rust/issues/139368), I wasn't the only one surprised to see this! Lots of GitHub issue labels gave weight to that issue at various points:`I-unsound`, `I-prioritize`, `T-lang`, `T-compiler`, `I-lang-nominated`, `I-lang-radar` etc.The issue discussion is nearly 100 items long, involving many people across various Rust project teams and spanning many months of work.

Since that discussion is extremely technical, let me attempt to provide a more approachable explanation.

### Why is this surprising? Why is it a problem?

Avoiding undefined behavior is the responsibility of the programmer when `unsafe` is used. If `unsafe` code can be misused by safe code to exhibit undefined behavior, such code is **unsound**.

But *which* use of `unsafe` is unsound?

Our example code used [safety comments](https://std-dev-guide.rust-lang.org/policy/safety-comments.html), adhering to the best practices of writing unsafe Rust. We should be able to look at each use of `unsafe`, together with its safety comment, to determine what went wrong.

```rust
pub trait NoFeatures {
    // SAFETY: Always safe to call.
    unsafe fn example(&self) -> i64 {
        0
    }
}
```

Not much to see here, this seems fine!

Moving on:

```rust
pub fn takes_generic<T: NoFeatures>(value: T) -> i64 {
    // SAFETY: The trait said this is always safe to call.
    unsafe {
        value.example()
    }
}
```

This safety comment accurately references the safety requirement documented in the trait. That seems fine!

In particular, we cannot demand that `takes_generic()` know anything about possible implementations of the `NoFeatures` trait: such implementations may exist in unrelated downstream crates, in entirely separate crates from both `takes_generic()` and its invocations. In other words, the function's generic nature means it *cannot know anything* about the specific flavor of `NoFeatures` it is being called with.

That leaves only one `unsafe` use left — this one:

```rust
impl NoFeatures for NeedsAvx {
    // SAFETY: May only be called
    //         on \`avx\`-capable hardware.
    #[target_feature(enable = "avx")]
    unsafe fn example(&self) -> i64 {
        1
    }
}
```

With today's design of Rust, we *have to* conclude that the problem lies here. There's nowhere else left to place the blame — we're out of `unsafe` uses!

While Rust teams work very hard to foresee and prevent issues like this, it's impossible to think of everything ahead of time. My work on `cargo-semver-checks` helped discover this issue — and led to the following paragraph being added to the Rust 1.89 documentation:

> Note that unlike normal `unsafe fn`, an `unsafe fn` in a trait implementation does not get to just pick an arbitrary safety contract! It *has* to use the safety contract defined by the trait (or one with weaker preconditions).

As surprising as this edge case is, it's certainly not the first time something like this has come up. The *usual fix* is to:

- Ban the problematic pattern going forward — in this case, prevent trait implementations from adding target features that are not part of the trait's own definition.
- Audit existing Rust code to examine the impact of the change, opening issues and PRs as needed to minimize impact to real-world code.

This case was no different — [that was the initial plan](https://github.com/rust-lang/rust/issues/139368#issuecomment-2790408412)!

But there was a problem.

### We can't roll it back, so we're fixing it forward

> Not even the compiler itself builds when `target_feature` in trait impls is forbidden. There's \[also\] a use in aho-corasick \[...\] That looks all entirely sound, and the safety comment indicates that the author was fully aware of all the pitfalls here.

It's unclear whether `#[target_feature]` was *always* intended to support this use case, or whether this feature is "accidental."

We know one thing for sure, though: there are valid use cases out there. The Rust project is (correctly so!) extremely reluctant to break existing, working code.

Fortunately, the addition of `unsafe` *attributes* in Rust edition 2024 gives us a way out: [a new language RFC](https://github.com/veluca93/rfcs/blob/tft/text/3820-target-feature-traits.md) proposes changing `#[target_feature]` to sometimes require `unsafe` — across an edition so breakage is avoided, of course.

The RFC's idea is to clearly distinguish between cases that impose *new* safety requirements from cases that merely reuse (or even relax) safety requirements already spelled out in the trait definition. The latter case remains served by `#[target_feature(enable = "x")]` as before. Meanwhile, the former is proposed to use a new `unsafe` attribute, `#[unsafe(target_feature(force = "x"))]`:

> It comes with the following soundness requirement: a function with the signature of the function the attribute is applied to must *only be callable if the force-enabled features are guaranteed to be present* (this can be done, for example, if the function takes arguments that carry appropriate safety invariants).

With the new attribute, our previous example would instead have to be:

```rust
impl NoFeatures for NeedsAvx {
    // New \`unsafe\` here!
    // ------------------
    // ||
    // || It makes the \`NeedsAvx\` struct
    // || become responsible for enforcing
    // || that it can only be constructed
    // || if \`avx\` functionality is present.
    // || This eliminates the prior unsoundness!
    // ||
    // \/
    #[unsafe(target_feature(force = "avx"))]
    unsafe fn example(&self) -> i64 {
        // The \`unsafe\` in \`unsafe fn\` now
        // only carries the safety requirements
        // in the trait definition — as we'd expect.
        1
    }
}
```

This solves the problem quite neatly indeed! 🎉

## A dozen new SemVer lints, and two rustdoc bugfixes

Today's includes 12 new lints aimed at making `#[target_feature]` easier to use in a SemVer-safe manner.

The new lints catch the breaking addition of new target features in both safe and unsafe functions, in both free functions and methods / associated functions. They also cover breaking changes in trait functions — including both target feature addition *and* removal cases.

The `#[target_feature]` removal case in traits is a particularly nasty kind of breakage: instead of a compilation error, it silently causes *undefined behavior* in downstream code 😱

```rust
// In crate \`upstream\`:
pub trait MyTrait {
    // Say the following line is removed:
    #[target_feature(enable = "avx")]
    unsafe fn example() {
        // ...
    }
}

// In crate \`downstream\`:
pub struct MyStruct;

impl upstream::MyTrait for MyStruct {
    // As we described in this post,
    // \`#[target_feature]\` here is allowed
    // *even if* it's removed from the trait.
    //
    // But if the trait removes it,
    // a caller using \`MyTrait\` via
    // a generic parameter or \`dyn Trait\`
    // might call \`MyStruct\`'s implementation
    // *without* satisfying the feature requirement
    // -- unexpected undefined behavior!
    #[target_feature(enable = "avx")]
    unsafe fn example() {
        // ...
    }
}
```

While "caused compilation errors for downstream users" breakage is bad enough, "caused undefined behavior" is certainly worse! Maintainers who upgrade to the new `cargo-semver-checks` version will thankfully be protected from such fallout.

Shout outs to [Will Glynn](https://github.com/willglynn) and [aDotInTheVoid](https://github.com/aDotInTheVoid) for making target feature information available to `cargo-semver-checks`, to [Jubilee](https://github.com/workingjubilee) for answering a million of my questions that helped shape the lints, and to [Kornel](https://github.com/kornelski) for [finding a bug](https://github.com/obi1kenobi/cargo-semver-checks/issues/1344) in the lints in by running a pre-release version of `cargo-semver-checks`. Software engineering truly is a team sport!

While testing the new lints, I discovered something unexpected in rustdoc. Say we have a function like:

```rust
#[target_feature(enable = "avx")]
pub fn example() {
    // ...
}
```

This function is *safe* — there's no `unsafe` in sight. But rustdoc would incorrectly list the function as `unsafe`!

I originally [reported this issue](https://github.com/rust-lang/rust/issues/142655) for rustdoc's JSON output. While triaging that issue, the rustdoc team subsequently determined that [the HTML output that powers `docs.rs` is affected too](https://github.com/rust-lang/rust/issues/142952).

The HTML output is now fixed, while the [rustdoc JSON issue](https://github.com/rust-lang/rust/issues/142655) is marked as having an available mentor and is a good area for contributors to jump in. A fix there is hopefully not far behind!

## Supporting cargo-semver-checks means supporting work like this

To recap: working on SemVer lints for `#[target_feature]` made Rust *better for everyone* — even for users who *have never used* `cargo-semver-checks`.

I [discovered and reported an issue](https://github.com/rust-lang/rust/issues/139368) with the design of `#[target_feature]` that could lead to violations of memory safety and undefined behavior. It led to [an RFC bringing refinements to its design](https://github.com/veluca93/rfcs/blob/tft/text/3820-target-feature-traits.md) that make the feature both safer and more powerful.

Along the way, the rustdoc team and I discovered two bugs in `rustdoc` ([one in the HTML output](https://github.com/rust-lang/rust/issues/142952), the [other in the JSON output format](https://github.com/rust-lang/rust/issues/142655)) that caused safe functions that use `#[target_feature]` to incorrectly be listed as `unsafe`. Fixing these bugs improved the experience of browsing the `docs.rs` pages of crates that use `#[target_feature]`.

Building `cargo-semver-checks` requires taking an *intensely* close look at Rust features. The act of putting Rust features under a microscope like this means we're also likely to find many bugs, both big and small. I make it a point to report these bugs in a manner that makes it easier to fix them: with a high-quality explanation of what went wrong, and with a reproducer that can be readily converted into a regression test.

If you [support my work on `cargo-semver-checks`](https://github.com/sponsors/obi1kenobi), you are not only supporting the effort to eradicate SemVer breakage — you make all the rest of this possible too.

When "things just *work* " in Rust, remember that this is extraordinary — not automatic. That feeling is the product of countless volunteers contributing their expertise and spare time, building atop each other's work for *years*. I'm honored to be a part of that ecosystem, and I'm delighted I can help make it an even better place.

*If you liked this essay, consider [subscribing to my blog](https://predr.ag/subscribe/) or following me on [Mastodon](https://hachyderm.io/@predrag), [Bluesky](https://bsky.app/profile/predraggruevski.bsky.social), or [Twitter/X](https://twitter.com/PredragGruevski). You can also fund my writing and work on `cargo-semver-checks` via [GitHub Sponsors](https://github.com/sponsors/obi1kenobi), for which I'd be most grateful ❤*

*Discuss on [r/rust](https://www.reddit.com/r/rust/comments/1lsdaeh/unsoundness_and_accidental_features_in_the_target/).*