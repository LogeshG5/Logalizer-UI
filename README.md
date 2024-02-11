# Logalizer-UI

User interface for [Logalizer](https://github.com/LogeshG5/Logalizer).

Logalizer helps to visualize logs. You could generate sequence diagram with Logalizer and PlantUML.

## Usage

Place `logalizer` binary in the same path as `logalizer-ui`.

Place all your configurations under config directory in the same path as `logalizer-ui`.

## Build

1. [Install vcpkg](https://vcpkg.io/en/getting-started.html)

2. Build

```bash
cmake --preset ninja-multi-vcpkg
cmake --build --preset ninja-multi-vcpkg-release
```

3. Run Tests

```bash
ctest --preset ninja-multi-vcpkg-release --verbose
```
