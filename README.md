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
#### macOS / Linux
```bash
# 1. Configure (generate build system)
cmake -B build -DCMAKE_BUILD_TYPE=Release
# 2. Compile
cmake --build build
# 3. Run
./build/CoolSnake
Windows (Developer Command Prompt / PowerShell)
bash
运行
# 1. Configure
cmake -B build
# 2. Compile
cmake --build build --config Release
# 3. Run
.\build\Release\CoolSnake.exe
Note: On Windows, MSVC places the executable in a Release (or Debug) subdirectory by default. Use --config Release with cmake --build and run from the matching folder.
Build Options
bash
运行
# Debug build with Address Sanitizer (GCC/Clang)
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_ASAN=ON
cmake --build build
Project Structure
plaintext
CoolSnake/
├── CMakeLists.txt      # Build configuration
├── include/
│   └── SnakeGame.h     # Game logic header
├── src/
│   └── main.cpp        # Game logic + FTXUI rendering
└── README.md           # Project documentation
