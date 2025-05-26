#include "backend_s.hpp"

namespace s21 {

// Функция для загрузки максимального количества очков
int LoadHighScore() {
  ifstream file("brick_game/snake/highscore.txt");
  int highScore = 0;
  if (file) {
    file >> highScore;
  }
  return highScore;
}
// Функция для сохранения максимального количества очков
void SaveHighScore(int highScore) {
  ofstream file("brick_game/snake/highscore.txt");
  if (file) {
    file << highScore;
  }
}

Snake::Snake()
    : x(BOARD_X / 2), y(BOARD_Y / 2), nTail(4), dir(Direction::RIGHT) {
  // Инициализация хвоста змейки
  for (int i = 0; i < nTail; i++) {
    tail.push_back({x - i - 1, y});
  }
}

void Snake::Input(int key) {
  switch (key) {
    case KEY_LEFT:
      if (dir != Direction::RIGHT) dir = Direction::LEFT;
      break;
    case KEY_RIGHT:
      if (dir != Direction::LEFT) dir = Direction::RIGHT;
      break;
    case KEY_UP:
      if (dir != Direction::DOWN) dir = Direction::UP;
      break;
    case KEY_DOWN:
      if (dir != Direction::UP) dir = Direction::DOWN;
      break;
  }
}

void Snake::Move() {
  // Добавляем новую голову
  tail.insert(tail.begin(), {x, y});

  // Удаляем последний элемент хвоста, если змейка не съела еду
  if (tail.size() > static_cast<size_t>(nTail)) {
    tail.pop_back();
  }

  // Двигаем голову
  switch (dir) {
    case Direction::LEFT:
      x--;
      break;
    case Direction::RIGHT:
      x++;
      break;
    case Direction::UP:
      y--;
      break;
    case Direction::DOWN:
      y++;
      break;
    case Direction::STOP:
      break;
  }
}

bool Snake::CheckBoundaryCollision() const {
  return x < 0 || x >= BOARD_X - 1 || y < 0 || y >= BOARD_Y - 1;
}

bool Snake::CheckCollision() const {
  for (const auto& [tailX, tailY] : tail) {
    if (tailX == x && tailY == y) return true;
  }
  return false;
}

int Snake::GetX() const { return x; }

int Snake::GetY() const { return y; }

const vector<pair<int, int>>& Snake::GetTail() const { return tail; }

int Snake::GetNTail() const { return nTail; }

void Snake::GrowTail() { nTail++; }

Food::Food()
    : x((PADDING) + rand() % (BOARD_X - 3)),
      y((PADDING) + rand() % (BOARD_Y - 3)) {}

void Food::Generate(const Snake& snake) {
  do {
    x = PADDING + rand() % (BOARD_X - 3);
    y = PADDING + rand() % (BOARD_Y - 3);
  } while (std::any_of(snake.GetTail().begin(), snake.GetTail().end(),
                       [this](const auto& segment) {
                         return segment.first == x && segment.second == y;
                       }));
}

std::pair<int, int> Food::GetPosition() const {
  return {x, y};  // Возвращаем позицию еды
}

int Food::GetX() const { return x; }

int Food::GetY() const { return y; }

GameController::GameController(int initialDelay)
    : gameState(GameState::MENU), score(0), level(1), delay(initialDelay) {
  highScore = LoadHighScore();
}

int ChooseGame() {
  int a = -9;
  while (a != KEY_LEFT && a != KEY_RIGHT && a != 'q') {
    DrawChoose();
    a = getch();
  }
  clear();
  return a;
}

void GameController::HandleInput(int key) {
  switch (gameState) {
    case GameState::MENU:
      if (key == 10 || key == 'e') gameState = GameState::RUNNING;
      break;

    case GameState::RUNNING:
      snake.Input(key);
      switch (key) {
        case 32:
          gameState = GameState::PAUSED;
          break;
        case 'q':
          gameState = GameState::GAME_OVER;
          break;
        case '+':
          delay = max(50, delay - 10);
          break;  // Ускорение змейки
      }
      break;

    case GameState::PAUSED:
      if (key == 32) gameState = GameState::RUNNING;
      break;

    case GameState::GAME_OVER:
      if (key == 10) {
        s21::GameController game(200);
        game.Run();
        gameState = GameState::RUNNING;
      }
    case GameState::WIN:
      if (key == 'q') {
        SaveHighScore(highScore);
        endwin();
        exit(0);
      }
      break;
  }
}

void GameController::Update() {
  if (gameState == GameState::RUNNING) {
    snake.Move();

    if (snake.CheckBoundaryCollision()) {
      gameState = GameState::GAME_OVER;
      return;
    }

    if (snake.GetX() == food.GetX() && snake.GetY() == food.GetY()) {
      score++;
      snake.GrowTail();
      food.Generate(snake);

      // Увеличение уровня каждые 5 очков
      if (score % 5 == 0 && level < maxLevel) {
        level++;
        delay = max(50, delay - 20);  // Увеличение скорости
      }
    }

    if (snake.CheckCollision()) {
      gameState = GameState::GAME_OVER;
    }

    // Проверка на победу
    if (snake.GetNTail() >= 200) {
      gameState = GameState::WIN;
    }

    // Обновление максимального количества очков
    if (score > highScore) {
      highScore = score;
    }
  }
}

void GameController::Draw() const {
  clear();
  switch (gameState) {
    case GameState::MENU:
      renderer.DrawMenu();
      break;

    case GameState::RUNNING:
      renderer.DrawBorder();
      renderer.DrawSnake(snake);
      renderer.DrawFood(food);
      renderer.DrawScore(score, highScore, level, delay);
      break;

    case GameState::PAUSED:
      renderer.DrawBorder();
      renderer.DrawScore(score, highScore, level, delay);
      renderer.DrawPause();
      break;

    case GameState::GAME_OVER:
      renderer.DrawBorder();
      renderer.DrawScore(score, highScore, level, delay);
      renderer.DrawGameOver();
      break;

    case GameState::WIN:
      renderer.DrawWin(score, highScore);
      break;
  }
  refresh();
}

void GameController::Run() {
  srand(static_cast<unsigned>(time(0)));
  timeout(delay);
  while (true) {
    int key = getch();
    HandleInput(key);
    Update();
    Draw();
    napms(delay);
  }
}

}  // namespace s21
