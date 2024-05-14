# Pac plus

[![codecov](https://codecov.io/gh/chienaeae/pac-plus/graph/badge.svg?token=YP2ELJQQJD)](https://codecov.io/gh/chienaeae/pac-plus)


## Development

### Initial

```bash
git submodule update --init --recursive

./vcpkg/bootstrap-vcpkg.sh

./vcpkg/vcpkg install

```

### Git Hooks

It is suggested to install git hook for style linting before code committing. This project is configured with [pre-commit](https://pre-commit.com).

Installation steps:

```bash
pre-commit install --install-hooks -t commit-msg -t pre-commit

```

### Debug

```bash
cmake --preset=debug .

cmake --build debug

./debug/main

```

### Release

```bash
cmake --preset=release .

cmake --build release

./release/main

```
