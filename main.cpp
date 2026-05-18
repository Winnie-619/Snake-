#include "SnakeGame.h"
#include <ftxui/component/screen_interactive.hpp>
#include <chrono>
#include <thread>
#include <random>

SnakeGame::SnakeGame(int w, int h) : w_(w), h_(h)
{
	nowDir = RIGHT;
	level = NORMAL;
	body.push_back({w / 2, h / 2});
	SpawnFood();
}

void SnakeGame::SpawnFood()
{
	static std::mt19937 rd(std::random_device{}());
	std::uniform_int_distribution<int> rx(0, w_ - 1);
	std::uniform_int_distribution<int> ry(0, h_ - 1);
	food = {rx(rd), ry(rd)};
}

bool SnakeGame::IsHitWall(Position p)
{
	return p.x < 0 || p.x >= w_ || p.y < 0 || p.y >= h_;
}

bool SnakeGame::IsHitSelf(Position p)
{
	for (auto& b : body)
		if (b.x == p.x && b.y == p.y)
			return true;
	return false;
}

void SnakeGame::MoveSnake()
{
	Position head = body.front();
	switch (nowDir)
	{
		case UP:    head.y--; break;
		case DOWN:  head.y++; break;
		case LEFT:  head.x--; break;
		case RIGHT: head.x++; break;
	}
	
	if (IsHitWall(head) || IsHitSelf(head))
	{
		gameOver = true;
		return;
	}
	
	body.insert(body.begin(), head);
	if (head.x == food.x && head.y == food.y)
	{
		growFlag = true;
		score += 10;
		SpawnFood();
	}
	
	if (!growFlag)
		body.pop_back();
	else
		growFlag = false;
}

void SnakeGame::Update()
{
	if (gameOver || isPause) return;
	MoveSnake();
}

void SnakeGame::SetDir(Direction d)
{
	if ((d == UP && nowDir == DOWN)  ||
		(d == DOWN && nowDir == UP)  ||
		(d == LEFT && nowDir == RIGHT) ||
		(d == RIGHT && nowDir == LEFT))
		return;
	nowDir = d;
}

void SnakeGame::SwitchLevel()
{
	if (gameOver || !isPause) return;
	switch (level)
	{
		case EASY: level = NORMAL; break;
		case NORMAL: level = HARD; break;
		case HARD: level = EASY; break;
	}
}

void SnakeGame::TogglePause()
{
	if (gameOver) return;
	isPause = !isPause;
}

void SnakeGame::RestartGame()
{
	score = 0;
	gameOver = false;
	isPause = true;
	nowDir = RIGHT;
	body.clear();
	body.push_back({w_ / 2, h_ / 2});
	SpawnFood();
}

bool SnakeGame::IsOver() const
{
	return gameOver;
}

bool SnakeGame::IsPaused() const
{
	return isPause;
}

int SnakeGame::GetSpeed() const
{
	switch (level)
	{
		case EASY: return 220;
		case NORMAL: return 150;
		case HARD: return 80;
	}
	return 150;
}

ftxui::Element SnakeGame::Render()
{
	using namespace ftxui;
	Elements map;
	for (int y = 0; y < h_; y++)
	{
		Elements line;
		for (int x = 0; x < w_; x++)
		{
			// 苹果食物图标
			if (x == food.x && y == food.y)
			{
				line.push_back(text("🍎") | color(Color::Red));
			}
			else
			{
				bool isHead = false;
				bool isBody = false;
				// 判断蛇头
				if (!body.empty() && body.front().x == x && body.front().y == y)
				{
					isHead = true;
				}
				else
				{
					// 判断蛇身
					for (size_t i = 1; i < body.size(); i++)
					{
						if (body[i].x == x && body[i].y == y)
						{
							isBody = true;
							break;
						}
					}
				}
				
				if(isHead)
				{
					line.push_back(text("🐍") | color(Color::Green));
				}
				else if(isBody)
				{
					line.push_back(text("▬") | color(Color::GreenLight));
				}
				else
				{
					line.push_back(text("  "));
				}
			}
		}
		map.push_back(hbox(line));
	}
	
	Element gameView = vbox(map) | border;
	std::string levelStr[] = {"简单", "普通", "困难"};
	
	Elements infoBox;
	infoBox.push_back(text("分数：" + std::to_string(score)) | bold);
	infoBox.push_back(text("难度：" + std::string(levelStr[level])));
	infoBox.push_back(text("空格=开始/暂停"));
	infoBox.push_back(text("L=切换难度  R=重新开局"));
	
	// 开局提示
	if (isPause && !gameOver)
	{
		gameView = vbox({
			gameView,
			separator(),
			text("    按下空格键开始游戏    ") | bold | color(Color::Yellow)
		}) | center;
	}
	
	// 游戏结束提示
	if (gameOver)
	{
		gameView = vbox({
			gameView,
			separator(),
			text("        游戏结束！        ") | bold | color(Color::Red),
			text("最终得分：" + std::to_string(score)) | color(Color::Red),
			text("    按 R 键重新游玩    ") | color(Color::Green)
		}) | center;
	}
	
	return hbox({gameView, separator(), vbox(infoBox)});
}

int main()
{
	using namespace ftxui;
	SnakeGame game(22, 16);
	auto screen = ScreenInteractive::TerminalOutput();
	
	Component gameUI = Renderer([&] { return game.Render(); });
	
	gameUI |= CatchEvent([&](Event e)
						 {
		if (e == Event::ArrowUp)    game.SetDir(UP);
		if (e == Event::ArrowDown)  game.SetDir(DOWN);
		if (e == Event::ArrowLeft)  game.SetDir(LEFT);
		if (e == Event::ArrowRight) game.SetDir(RIGHT);
		if (e == Event::Character(' ')) game.TogglePause();
		if (e == Event::Character('l') || e == Event::Character('L')) game.SwitchLevel();
		if (e == Event::Character('r') || e == Event::Character('R')) game.RestartGame();
		if (e == Event::Escape)     screen.ExitLoopClosure()();
		return false;
	});
	
	std::thread runThread([&]()
						  {
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(game.GetSpeed()));
			game.Update();
			screen.PostEvent(Event::Custom);
		}
	});
	runThread.detach();
	
	screen.Loop(gameUI);
	return 0;
}
