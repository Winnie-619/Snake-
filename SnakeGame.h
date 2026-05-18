#pragma once
#include <vector>
#include <atomic>
#include <string>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

struct Position {
    int x;
    int y;
};

enum Direction { UP, DOWN, LEFT, RIGHT };
enum GameLevel { EASY, NORMAL, HARD };

class SnakeGame
{
public:
    SnakeGame(int w, int h);
    void Update();
    void SetDir(Direction d);
    void SwitchLevel();
    void TogglePause();
    void RestartGame();
    ftxui::Element Render();
    bool IsOver() const;
    bool IsPaused() const;
    int GetSpeed() const;

private:
    int w_, h_;
    std::vector<Position> body;
    Position food;
    Direction nowDir;
    GameLevel level;
    bool growFlag = false;
    std::atomic<bool> gameOver{false};
    std::atomic<bool> isPause{true};
    int score = 0;

    void MoveSnake();
    void SpawnFood();
    bool IsHitWall(Position p);
    bool IsHitSelf(Position p);
};