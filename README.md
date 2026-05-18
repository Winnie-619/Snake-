# 🐍 CoolSnake TUI
A terminal-based Snake game written in C++20, powered by FTXUI.

![Game Demo GIF](你的游戏演示GIF地址)

## Features
- Classic snake movement with automatic forward progression
- Direction control with arrow keys (prevents 180° reverse movement)
- Eat apple food to grow longer and gain score
- Wall & self-body collision detection (game over on hit)
- 3 difficulty levels (Easy / Normal / Hard) with adjustable speed
- Real-time score display, final score shown on game over
- Pause/resume functionality
- Unicode & emoji graphics (snake head, snake body, apple food)

## Controls
| Key          | Action                          |
|--------------|---------------------------------|
| ← → ↑ ↓      | Move snake direction            |
| Space        | Start / Pause / Resume game     |
| L / l        | Switch difficulty level         |
| R / r        | Restart new game                |
| Esc          | Quit game                       |

## Scoring
| Action              | Points (fixed) |
|---------------------|----------------|
| Eat one apple       | 10 points      |

Difficulty affects movement speed:
- Easy: 220ms
- Normal: 150ms
- Hard: 80ms

## Build
### Requirements
| Tool               | Minimum Version                          |
|--------------------|------------------------------------------|
| CMake              | 3.20                                     |
| C++ compiler       | C++20 (GCC 8+, Clang 7+, MSVC 2019 16.8+)|

FTXUI is fetched automatically via CMake FetchContent — no manual dependency installation needed.

### Compile & Run
```bash
# macOS / Linux
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/CoolSnake

# Windows (Developer Command Prompt / PowerShell)
cmake -B build
cmake --build build --config Release
.\build\Release\CoolSnake.exe

# Debug build with Address Sanitizer (GCC/Clang)
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_ASAN=ON
cmake --build build
