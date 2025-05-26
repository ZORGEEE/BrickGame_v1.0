#include "../../brick_game/snake/backend_s.hpp"
#include "frontend.h"

extern "C" {
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void game_paused();
void game_over_info();
}

namespace s21 {
void Renderer::DrawBorder() const { print_rectangle(0, BOARD_Y, 0, BOARD_X); }

void Renderer::DrawSnake(const Snake& snake) const {
  MVPRINTW(snake.GetY() + 1, snake.GetX() + 1, "O");
  for (const auto& [tailX, tailY] : snake.GetTail()) {
    MVPRINTW(tailY + 1, tailX + 1, "o");
  }
}

void Renderer::DrawFood(const Food& food) const {
  MVPRINTW(food.GetY() + 1, food.GetX() + 1, "F");
}

void Renderer::DrawScore(int score, int highScore, int level, int delay) const {
  MVPRINTW(4, BOARD_X + 5, "SCORE");
  MVPRINTW(5, BOARD_X + 5, "%d", score);

  MVPRINTW(7, BOARD_X + 5, "LEVEL");
  MVPRINTW(8, BOARD_X + 5, "%d", level);

  MVPRINTW(13, BOARD_X + 5, "HIGH SCORE");
  MVPRINTW(14, BOARD_X + 5, "%d", highScore);

  MVPRINTW(10, BOARD_X + 5, "SPEED");
  MVPRINTW(11, BOARD_X + 5, "%d", 500 - delay);
}

void Renderer::DrawMenu() const {
  int row, col;
  getmaxyx(stdscr, row, col);
  MVPRINTW(2, col / 2 - 9, "WELCOME TO THE:");
  MVPRINTW(4, col / 2 - 11, "Brick Game Snake");
  MVPRINTW(row / 2 - 5, col / 2 - 16, "PRESS ENTER (or 'e') TO START");
  MVPRINTW(row / 2 - 3, col / 2 - 15, "IF U WANT TO QUIT PRESS 'q'");
  MVPRINTW(row / 2 + 2, col / 2 - 3, "RULES:");
  MVPRINTW(row / 2 + 4, col / 2 - 19, "TO MOVE LEFT - PRESS 'left arrow'");
  MVPRINTW(row / 2 + 6, col / 2 - 19, "TO MOVE RIGHT - PRESS 'right arrow'");
  MVPRINTW(row / 2 + 8, col / 2 - 19, "TO MOVE DOWN - PRESS 'down arrow'");
  MVPRINTW(row / 2 + 10, col / 2 - 19, "TO MOVE UP - PRESS 'up arrow'");
  MVPRINTW(row / 2 + 12, col / 2 - 14, "PAUSE - PRESS 'spase'");
}

void Renderer::DrawPause() const { game_paused(); }

void Renderer::DrawGameOver() const { game_over_info(); }

void Renderer::DrawWin(int score, int highScore) const {
  mvprintw(BOARD_Y / 2, BOARD_X / 2 - 5, "You Win!");
  mvprintw(BOARD_Y / 2 + 1, BOARD_X / 2 - 5, "Score: %d | High Score: %d",
           score, highScore);
  mvprintw(BOARD_Y / 2 + 2, BOARD_X / 2 - 5, "Press 'q' to quit");
}

void DrawChoose() {
  mvprintw(2, 9, "CHOOSE THE GAME!");
  mvprintw(4, 3, "* Pess <- to play the Tetris");
  mvprintw(5, 3, "* Pess -> to play the Snake");
  mvprintw(6, 3, "* Pess 'q' to exit");
}

}  // namespace s21