# FullGame

## Quick Launch

Use the launcher in the repository root:

- `LaunchGame.bat`

The launcher keeps the terminal open, prints the exit code, and points to `FullGame.log`.

## Build

```bat
cmake -S . -B build
cmake --build build --config Debug
```

## Crash Troubleshooting (Windows)

If the game window appears then closes, do this:

1. Run `LaunchGame.bat` again.
2. Open `FullGame.log` in the repository root.
3. Share the final 30 log lines.

Common causes:

- Vulkan runtime/driver missing or outdated.
- `glfw3` not found at configure time (`glfw3Config.cmake` missing from CMake search paths).
- Running executable from a different build config than expected.
