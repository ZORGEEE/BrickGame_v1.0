#ifndef SRC_GUI_CLI_FRONTEND_H_
#define SRC_GUI_CLI_FRONTEND_H_

#include "../../defines.h"

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_figure(tetris_t figure);
void print_tetris_blocks(Field field);
void print_information(Field field);

void updateCurrentState(Field field, tetris_t figure);
void game_paused();
int game_start_info(int row, int col);
void game_over_info();

#endif  // SRC_GUI_CLI_FRONTEND_H_