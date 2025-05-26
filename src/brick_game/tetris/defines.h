#ifndef SRC_DEFINES_H_
#define SRC_DEFINES_H_

#include <ncurses.h>

#define PADDING 2
#define BOARD_Y (PADDING + 20 - 1)
#define BOARD_X (PADDING + 10 - 1)
#define FIGURE_SYM 'X'
#define X BOARD_X / 2 + PADDING
#define Y PADDING + 1

#define INITIAL_SPEED 500
#define SPEED_UP 30
#define LEVEL_UP_AFTER 600
#define ENTER_KEY 10
#define SPACE_KEY 32

#define MVADDCH(y, x, c) mvaddch(PADDING + (y), PADDING + (x), c)
#define MVPRINTW(y, x, ...) mvprintw(PADDING + (y), PADDING + (x), __VA_ARGS__)

#define FIGURE                                                          \
  (figures) {                                                           \
    {                                                                   \
      (tetris_t){{X - 2, X - 1, X, X + 1}, {Y, Y, Y, Y}, 0, 0},         \
          (tetris_t){{X, X, X + 1, X + 2}, {Y - 1, Y, Y, Y}, 0, 1},     \
          (tetris_t){{X + 1, X + 1, X, X - 1}, {Y - 1, Y, Y, Y}, 0, 2}, \
          (tetris_t){{X - 1, X, X - 1, X}, {Y, Y, Y - 1, Y - 1}, 0, 3}, \
          (tetris_t){{X + 1, X, X, X - 1}, {Y - 1, Y - 1, Y, Y}, 0, 4}, \
          (tetris_t){{X, X - 1, X, X + 1}, {Y - 1, Y, Y, Y}, 0, 5},     \
          (tetris_t){{X - 1, X, X, X + 1}, {Y - 1, Y - 1, Y, Y}, 0, 6}, \
    }                                                                   \
  }

typedef struct {
  int x[4];
  int y[4];
  int swap;
  int type;
} tetris_t;

typedef struct {
  tetris_t type[7];
} figures;

typedef enum {
  MOVE_UP = 0,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,
  TERMINATE,
  PAUSE,
  START,
  ACTION
} UserAction_t;

typedef struct {
  int **screen;
  int next;
  int score;

  int pause;
  int high_score;
  int level;
  int speed;

  int game_is_on;
  int x_start;
  int x_end;
  int y_start;
  int y_end;
} Field;

#endif  // SRC_DEFINES_H_