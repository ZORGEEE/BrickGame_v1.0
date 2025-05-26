#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include <ncurses.h>

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <utility>
#include <vector>

#include "../tetris/defines.h"

using namespace std;

namespace s21 {
// constexpr int width = 10;     // Ширина поля
// constexpr int height = 20;    // Высота поля
constexpr int maxLevel = 10;  // Максимальный уровень

enum class Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum class GameState { MENU, RUNNING, PAUSED, GAME_OVER, WIN };

int LoadHighScore();
void SaveHighScore(int highScore);
int ChooseGame();
void DrawChoose();

class Snake {
 private:
  int x, y;
  vector<pair<int, int>> tail;

  int nTail;

 public:
  Direction dir;
  Snake();

  void Input(int key);
  void Move();
  bool CheckCollision() const;
  bool CheckBoundaryCollision() const;

  int GetX() const;
  int GetY() const;
  const vector<pair<int, int>>& GetTail() const;
  int GetNTail() const;
  void GrowTail();
};

class Food {
 private:
  int x, y;

 public:
  Food();

  void Generate(const Snake& snake);

  std::pair<int, int> GetPosition() const;
  int GetX() const;
  int GetY() const;
};

class Renderer {
 public:
  void DrawBorder() const;
  void DrawSnake(const Snake& snake) const;
  void DrawFood(const Food& food) const;
  void DrawScore(int score, int highScore, int level, int delay) const;
  void DrawMenu() const;
  void DrawPause() const;
  void DrawGameOver() const;
  void DrawWin(int score, int highScore) const;
};

class GameController {
 private:
  Renderer renderer;

 public:
  Snake snake;
  Food food;
  GameState gameState;
  int score;
  int highScore;
  int level;
  int delay;
  GameController(int initialDelay = 200);

  void HandleInput(int key);
  void Update();
  void Draw() const;
  void Run();
};

}  // namespace s21

#endif