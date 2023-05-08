# Design Make

Let's design make. Each dependency has some dependency list that is
passed in, to compile a target binary.

```python

{
  "bin": ["foo.o", "bar.o", # "qux.h"]
  "foo.o": [# "foo.h", # "foo.c", # "qux.h"]
  "bar.o": [# "bar.h", # "bar.c"]
  "foo.h" : [] # compile
  "foo.c" : [] # compile
  "bar.h" : [] # compile
  "bar.c" : ["qux.h"] # compile this
  "qux.h" : [] # compile this
}

Builder(dependency map)

KickOffBuild(binary) # call compile on all dependencies until we compile binary
compile() # will add to a queue and compile asynchronously
OnCompileComplete(source_file) # this is called with source file when compile returns()
```

## Followups

- What happens if a certain dependency calls "compile" multiple times?
Isn't this inefficient?
- How might we parallelize this?
