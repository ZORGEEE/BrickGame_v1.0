#include "brick_game/snake/backend_s.hpp"
#include "brick_game/tetris/backend.h"
#include "gui/cli/frontend.h"

int main() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  int key = (s21::ChooseGame());
  if (key == KEY_LEFT) {
    game_start(0);
  } else if (key == KEY_RIGHT) {
    s21::GameController game(200);  // Начальная задержка 200 мс
    game.Run();
  }
  endwin();
  return 0;
}