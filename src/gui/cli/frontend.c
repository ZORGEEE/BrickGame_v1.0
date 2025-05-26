#include "frontend.h"

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);
  MVADDCH(bottom_y, i, ACS_LRCORNER);
}

void print_figure(tetris_t figure) {
  for (int i = 0; i < 4; i++) {
    if (figure.y[i] <= PADDING) continue;
    mvaddch(figure.y[i], figure.x[i], FIGURE_SYM);
  }
}

void print_tetris_blocks(Field field) {
  for (int i = field.y_start; i < field.y_end; i++) {
    for (int j = field.x_start; j < field.x_end; j++) {
      if (field.screen[i][j] == 1) {
        mvaddch(i, j, FIGURE_SYM);
      }
    }
  }
}

void print_information(Field field) {
  char score[20];
  sprintf(score, "%d", field.score);
  MVPRINTW(2, BOARD_X + 5, "SCORE");
  MVPRINTW(3, BOARD_X + 5, "%s", score);

  MVPRINTW(11, BOARD_X + 5, "NEXT");
  tetris_t figure = FIGURE.type[field.next];
  print_figure((tetris_t){
      {figure.x[0] + BOARD_X + 1, figure.x[1] + BOARD_X + 1,
       figure.x[2] + BOARD_X + 1, figure.x[3] + 1 + BOARD_X},
      {figure.y[0] + 13, figure.y[1] + 13, figure.y[2] + 13, figure.y[3] + 13},
      0,
      0});

  MVPRINTW(5, BOARD_X + 5, "LEVEL");
  char level[20];
  sprintf(level, "%d", field.level);
  MVPRINTW(6, BOARD_X + 5, "%s", level);

  MVPRINTW(8, BOARD_X + 5, "SPEED");
  char speed[20];
  sprintf(speed, "%d", field.speed);
  MVPRINTW(9, BOARD_X + 5, "%s", speed);

  MVPRINTW(16, BOARD_X + 5, "HIGH");
  MVPRINTW(17, BOARD_X + 5, "SCORE");
  char high_score[20];
  sprintf(high_score, "%d", field.high_score);
  MVPRINTW(18, BOARD_X + 5, "%s", high_score);
}

void game_paused() { MVPRINTW(BOARD_Y / 2, BOARD_X / 2 - 3, "PAUSED."); }

void updateCurrentState(Field field, tetris_t figure) {
  clear();
  print_figure(figure);
  print_tetris_blocks(field);
  print_information(field);
  print_rectangle(0, BOARD_Y, 0, BOARD_X);
  if (field.pause) game_paused();
  refresh();
}

int game_start_info(int row, int col) {
  MVPRINTW(2, col / 2 - 9, "WELCOME TO THE:");
  MVPRINTW(4, col / 2 - 11, "Brick Game Classic");
  MVPRINTW(row / 2 - 5, col / 2 - 16, "PRESS ENTER (or 'e') TO START");
  MVPRINTW(row / 2 - 3, col / 2 - 15, "IF U WANT TO QUIT PRESS 'q'");
  MVPRINTW(row / 2 + 2, col / 2 - 3, "RULES:");
  MVPRINTW(row / 2 + 4, col / 2 - 19, "TO MOVE LEFT - PRESS 'left arrow'");
  MVPRINTW(row / 2 + 6, col / 2 - 19, "TO MOVE RIGHT - PRESS 'right arrow'");
  MVPRINTW(row / 2 + 8, col / 2 - 19,
           "TO MOVE FIGURE - DOWN PRESS 'down arrow'");
  MVPRINTW(row / 2 + 10, col / 2 - 19, "TO TURN FIGURE - PRESS 'up arrow'");
  return 0;
}
void game_over_info() {
  mvprintw(0, 0, "Press ENTER to reply");
  mvprintw(1, 0, "Press q to exit");
}