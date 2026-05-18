cmake_minimum_required(VERSION 3.20)
project(CoolSnake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(ftxui)

add_executable(CoolSnake
    src/main.cpp
    include/SnakeGame.h
)

target_link_libraries(CoolSnake
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)
