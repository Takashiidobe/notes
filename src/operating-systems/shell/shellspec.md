---
title: shellspec
---

# ShellSpec

## Installation

`brew tap shellspec/shellspec` `brew install shellspec`

run `shellspec --init` inside of a project directory to start a
shellspec project.

this creates files like so:

    tree ${project}
    ${project}
    ├── lib
    │   └── hello.sh
    └── spec
        ├── hello_spec.sh
        └── spec_helper.sh

Implement your functionality inside of `lib/` and test it in the `spec/`
directory. suffix each file with `_spec.sh` and make sure to include the
lib file in the project to allow it to be tested. An example might look
like:

```sh
Describe "hello.sh"
  Include lib/hello.sh
  It "puts greeting, but not implemented"
    When call hello world
    The output should eq "Hello world!"
  End
End
```
