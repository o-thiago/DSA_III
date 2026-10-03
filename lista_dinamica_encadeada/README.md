# C flake template

Minimal CMake starter with a reproducible Clang toolchain. `C_STANDARD` in
`flake.nix` is the single language-version toggle (default: `23`).

## Run

```sh
nix develop
cmake -S . -B build && cmake --build build && ./build/c_app
```
