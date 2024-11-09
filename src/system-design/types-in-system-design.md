---
title: types-in-system-design
---
# Types in System Design

You can use types to model what states something can be in.

For example, in build an interview system, where there are 5 rounds, and
can be more, you might do this in OOP land, to create a candidate with a
state where the candidate is either failed, in progress, or passed.

In typescript that could be shown as such:

```ts
type interviewStates = "inProgress" | "passed" | "failed";
```

You can only transition from progress to passed or failed. You can also
encapsulate the interview number to make sure that you have had at least
5 interviews.

```ts
type interviewStates = "inProgress" | "passed" | "failed";

class Candiate {
  constructor(
    public status: interviewStates = "inProgress",
    public passedInterviews: number = 0
  ) {}

  conductInterview(passed: bool) {
    if (passed) {
      this.passedInterviews++;
    }
    this.status = "failed";
  }

  passInterview() {
    if (this.passedInterviews < 5) {
      throw new Error(;
    }
    this.status = "passed";
  }
}
```
