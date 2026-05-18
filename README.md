# 🐍 CoolSnake TUI

A terminal-based Snake game written in C++20, powered by [FTXUI]([https://github.com/ArthurSonzogni/FTXUI](https://s2.ezgif.com/tmp/ezgif-26a9f6fe9c76ddb0.gif)).

![Demonstration animation](https://s2.ezgif.com/tmp/ezgif-26a9f6fe9c76ddb0.gif)

## Features

- Classic snake automatic moving gameplay
- Prevent snake from reversing direction suddenly
- Eat apples to grow longer and gain scores
- Collision detection with walls and own body
- Three adjustable game difficulty levels
- Real-time score display and final score statistics
- Support game pause and resume
- Distinct visual icons for snake head, body and apple food

## Controls

| Key | Action |
| -------------- | ---------------- |
| ← → ↑ ↓ | Control snake moving direction |
| Space | Start game / Pause & Resume |
| L | Switch game difficulty |
| R | Restart the game |
| Esc | Exit game program |

## Scoring

 Behavior | Obtained Points |
| ------------- | ---------------- |
| Eat one apple | 10 |

Different difficulty corresponds to different moving speed: Easy 220ms, Normal 150ms, Hard 80ms.

## Build

### Requirements

| Tool | Minimum Version |
| ---------- | --------------- |
| CMake | 3.20 |
| C++ compiler | C++20 (GCC 8+, Clang 7+, MSVC 2019 16.8+) |

FTXUI is fetched automatically via CMake FetchContent — no manual dependency installation needed.

### Compile & Run

**macOS / Linux**

```bash
# 1. Configure (generate build system)
cmake -B build -DCMAKE_BUILD_TYPE=Release

# 2. Compile
cmake --build build

# 3. Run
./build/tetris
```

**Windows (Developer Command Prompt / PowerShell)**

```powershell
# 1. Configure
cmake -B build

# 2. Compile
cmake --build build --config Release

# 3. Run
.\build\Release\tetris.exe
```

> **Note:** On Windows, MSVC places the executable in a `Release` (or `Debug`) subdirectory by default. Use `--config Release` with `cmake --build` and run from the matching folder.

### Build Options

```bash
# Debug build with Address Sanitizer (GCC/Clang)
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_ASAN=ON
cmake --build build
```

## Project Structure

```
show/
CoolSnake/
├── CMakeLists.txt      # Build configuration
├── include/
│   └── SnakeGame.h     # Game core header file
├── src/
│   └── main.cpp        # Main program and game logic
└── README.md
```
