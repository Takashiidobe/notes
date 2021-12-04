# Profiling

- You can profile by running `flamegraph`.
  `flamegraph $path-to-binary` and then looking at the flamegraph with `open flamegraph.svg`.

- You can check the time a binary takes to execute with `hyperfine`.
  `hyperfine $path-to-binary`.
