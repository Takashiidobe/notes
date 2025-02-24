---
title: Dependency Inversion
date created: Monday, February 24th 2025, 7:27:34 am
date modified: Monday, February 24th 2025, 8:10:16 am
---

# Dependency Inversion

Every piece of code has some kind of dependency. They can come from the OS (randomness, I/O, the network, time) or other libraries (an SDK, an API you call, etc).
They can also come from your own code, which can also be dependent on other pieces of code.

In a statically typed language, we need to handle different dependencies for app and test code.
This can be taken to an extreme in both ways.

## Singletons

The first way to do this is to have a set of Singletons in main/test, and when the app starts or test starts, you can either initialize your dependencies or lazily load them when needed.

This is straightforward, but you now need to look at the implementation of a given function to know which dependencies it has, so you cannot just look at a function and know what dependencies it requires to mock out in test.

This is fine if you plan to mock out every dependency in test, but if you want to just run one test file, you may have to initialize everything. Thus, this leads to complicated testing, since you dont know which singletons to initialize until you're writing the tests.

## Mock Test

Who says we have to do anything for our app code? Let it use what it wants, and when we test, provide mock implementations of those static instances

This leaves your app code the same, but makes your test code carry the burden. It has to mock the static instances of functions you rely on in app code.

This comes with the downside that you're not tracking your explicit dependencies, so test has to know where to mock and reading the app code becomes harder because your dependencies are not captured.

As well, this requires some sort of ability to manipulate the bytecode of a function, or overwrite static functions, which can be trickier in some languages than others, and makes reading the code more confusing (do you know how X function works depending on whether it's in test or not?)

## Dependency Injection

Dependency Injection states that all functions should take all of their dependencies in their function call. That way, dependencies are all tracked by the constructor, and with either compile-time or run-time reflection, mocks can be codegened, which alleviates their downside of having to write a lot of code. 

Of course, relying on codegen itself is a downside; you have to know about how the codegen works, and if done in runtime or compile time, they either increase your compile times or slow your app starts and can cause unpredictable pauses if done at runtime either on start or lazily.

The other con is that function arguments can become unwieldy, since most code has lots of dependencies -- you may have to state many such dependencies (maybe 100s for a large function) and this hampers readability considerably.

However, you gain the ability to set up mocks easily, and reading a function tells us about its dependencies, since they're listed at the top of the function. 

## Service Locators

Service locators allow you to provide a locator to each of your functions, which then locates dependencies for you. You can write one for your app code and one for your test code which conform to the same interface, so app and test code get different versions of the code.

This takes care of the problem of Dependency Injection having lots of function arguments, but you also lose the pro of Dependency Injection explicitly stating its dependencies.

You only know what you need when you test code, which is the same as when you mock test or use singletons.