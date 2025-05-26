#include "brick_game/tetris/backend.h"
#include "gui/cli/frontend.h"

int game_start(int u);
int welcome_page();
int reply();

int main() {
  initscr();
  curs_set(0);
  noecho();
  raw();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  clear();
  srand(time(NULL));
  game_start(0);
  endwin();
  return 0;
}

int welcome_page() {
  int flag = 2;
  int row, col;
  getmaxyx(stdscr, row, col);
  game_start_info(row, col);
  while (flag == 2) {
    int signal = get_signal(getch());
    if (signal == START)
      flag = 1;
    else if (signal == TERMINATE) {
      flag = 0;
    }
    napms(100);
  }
  return flag;
}

int game_start(int u) {
  if (u == 0 && welcome_page() == 0) {
  } else {
    int r = rand() % 7;
    r = rand() % 7;
    tetris_t figure = FIGURE.type[r];
    Field field = init_field();
    while (field.game_is_on == 1) {
      int seconds = field.speed;
      do {
        seconds -= 10;
        napms(10);
        updateCurrentState(field, figure);
        int signal = get_signal(getch());
        sigact(signal, &figure, &field);
      } while (seconds > 0);
      sigact(MOVE_DOWN, &figure, &field);
    }
    clean_field(&field);
    if (reply()) game_start(1);
  }
  return 0;
}

int reply() {
  int flag = 1;
  while (flag == 1) {
    napms(10);
    game_over_info();
    refresh();
    int signal = get_signal(getch());
    if (signal == TERMINATE)
      flag = 0;
    else if (signal == START)
      flag = 2;
  }
  return flag;
}
