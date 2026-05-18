# Snake Game
Terminal snake game developed with C++ and FTXUI library.

![demo](gif地址)

## Features
Complete classic snake game function, support difficulty switching, pause game and restart game, with simple and clear game interface.

## Controls
| Key | Function |
| ---- | ---- |
| Arrow keys | Control movement direction |
| Space | Start and pause game |
| L | Switch difficulty |
| R | Restart game |
| Esc | Exit game |

## Scoring
You can get 10 points every time you eat food, and the score will be displayed in real time during the game.

## Build
### Requirements
| Tool | Version |
| ---- | ---- |
| CMake | 3.20 and above |
| C++ Compiler | C++20 standard |

### Compile & Run
cmake -B build && cmake --build build && ./build/snake
