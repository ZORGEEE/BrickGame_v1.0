#ifndef SRC_BRICK_GAME_TETRIS_BACKEND_H_
#define SRC_BRICK_GAME_TETRIS_BACKEND_H_

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../../gui/cli/frontend.h"
#include "defines.h"

typedef struct {
  tetris_t *figure;
  Field *field;
} params_t;

#ifdef __cplusplus
extern "C" {
#endif

// Model
void move_up(params_t *params);
void move_down(params_t *params);
void move_left(params_t *params);
void move_right(params_t *params);
void game_over(params_t *params);

UserAction_t get_signal(int user_input);
void sigact(UserAction_t sig, tetris_t *figure, Field *field);

Field init_field();
void swap_type_0(tetris_t *figure);
void swap_type_1(tetris_t *figure);
void swap_type_2(tetris_t *figure);
void swap_type_4(tetris_t *figure);
void swap_type_5(tetris_t *figure);
void swap_type_6(tetris_t *figure);
void pause_game(params_t *params);
int check(Field *field, tetris_t temp);
void check_fild(Field *field);
int score_table(int cnt);

void copy_figure_values(tetris_t *destiny, tetris_t copy);
void clean_field(Field *field);
void game_settings(Field *field);
int get_high_score();
void set_high_score(int score);

// Controller
int game_start(int u);
int welcome_page();
int reply();

#ifdef __cplusplus
}
#endif

#endif  // SRC_BRICK_GAME_TETRIS_BACKEND_H_