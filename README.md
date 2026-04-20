# FullGame

## Quick Launch

To make the game easy to find, use the launcher in the repository root:

- `LaunchGame.bat`

The launcher now keeps the terminal open and prints the game's exit code so startup failures are visible.

## Build

```bat
cmake -S . -B build
cmake --build build --config Debug
```

## Startup Troubleshooting (Windows)

If a window appears and immediately closes, verify:

1. Vulkan runtime/driver is installed and up to date.
2. GLFW is available to CMake (`glfw3Config.cmake` discoverable).
3. Build and run configuration match (`Debug` executable exists).
