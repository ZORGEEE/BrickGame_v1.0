#include "backend.h"

typedef void (*Action)(params_t *params);

Action actions[8] = {move_up,   move_down,  move_left, move_right,
                     game_over, pause_game, NULL,      NULL};

void move_up(params_t *params) {
  tetris_t *temp = params->figure;
  if (params->figure->type == 0) {
    swap_type_0(temp);
  } else if (params->figure->type == 1) {
    swap_type_1(temp);
  } else if (params->figure->type == 2) {
    swap_type_2(temp);
  } else if (params->figure->type == 4) {
    swap_type_4(temp);
  } else if (params->figure->type == 5) {
    swap_type_5(temp);
  } else if (params->figure->type == 6) {
    swap_type_6(temp);
  } else {
    return;
  }
}

int check(Field *field, tetris_t temp) {
  for (int i = 0; i < 4; i++) {
    if (field->screen[temp.y[i]][temp.x[i]] != 0) {
      return 0;
    }
  }
  return 1;
}

void swap_type_5(tetris_t *figure) {
  int x = figure->x[2];
  int y = figure->y[2];
  if (figure->swap == 0) {
    copy_figure_values(
        figure, (tetris_t){{x + 1, x, x, x}, {y, y - 1, y, y + 1}, 0, 0});
  } else if (figure->swap == 1) {
    copy_figure_values(
        figure, (tetris_t){{x, x + 1, x, x - 1}, {y + 1, y, y, y}, 0, 0});
  } else if (figure->swap == 2) {
    copy_figure_values(
        figure, (tetris_t){{x - 1, x, x, x}, {y, y + 1, y, y - 1}, 0, 0});
  } else if (figure->swap == 3) {
    copy_figure_values(
        figure, (tetris_t){{x, x - 1, x, x + 1}, {y - 1, y, y, y}, 0, 0});
  }
  figure->swap += 1;
  figure->swap %= 4;
}

void swap_type_6(tetris_t *figure) {
  int x = figure->x[2];
  int y = figure->y[2];
  if (figure->swap == 0) {
    copy_figure_values(
        figure, (tetris_t){{x - 1, x - 1, x, x}, {y + 1, y, y, y - 1}, 0, 0});
  } else if (figure->swap == 1) {
    copy_figure_values(
        figure, (tetris_t){{x - 1, x, x, x + 1}, {y - 1, y - 1, y, y}, 0, 0});
  } else if (figure->swap == 2) {
    copy_figure_values(
        figure, (tetris_t){{x + 1, x + 1, x, x}, {y - 1, y, y, y + 1}, 0, 0});
  } else if (figure->swap == 3) {
    copy_figure_values(
        figure, (tetris_t){{x - 1, x, x, x + 1}, {y - 1, y - 1, y, y}, 0, 0});
  }
  figure->swap += 1;
  figure->swap %= 4;
}

void swap_type_4(tetris_t *figure) {
  int x = figure->x[2];
  int y = figure->y[2];
  if (figure->swap == 0) {
    copy_figure_values(
        figure, (tetris_t){{x + 1, x + 1, x, x}, {y + 1, y, y, y - 1}, 0, 0});
  } else if (figure->swap == 1) {
    copy_figure_values(
        figure, (tetris_t){{x + 1, x, x, x - 1}, {y - 1, y - 1, y, y}, 0, 0});
  } else if (figure->swap == 2) {
    copy_figure_values(
        figure, (tetris_t){{x - 1, x - 1, x, x}, {y - 1, y, y, y + 1}, 0, 0});
  } else if (figure->swap == 3) {
    copy_figure_values(
        figure, (tetris_t){{x + 1, x, x, x - 1}, {y - 1, y - 1, y, y}, 0, 0});
  }
  figure->swap += 1;
  figure->swap %= 4;
}

void swap_type_2(tetris_t *figure) {
  int x = figure->x[2];
  int y = figure->y[2];

  if (figure->swap == 0) {
    copy_figure_values(
        figure, (tetris_t){{x + 1, x, x, x}, {y + 1, y + 1, y, y - 1}, 0, 0});
  } else if (figure->swap == 1) {
    copy_figure_values(
        figure, (tetris_t){{x - 1, x - 1, x, x + 1}, {y + 1, y, y, y}, 0, 0});
  } else if (figure->swap == 2) {
    copy_figure_values(
        figure, (tetris_t){{x - 1, x, x, x}, {y - 1, y - 1, y, y + 1}, 0, 0});
  } else if (figure->swap == 3) {
    copy_figure_values(
        figure, (tetris_t){{x + 1, x + 1, x, x - 1}, {y - 1, y, y, y}, 0, 0});
  }
  figure->swap += 1;
  figure->swap %= 4;
}

void swap_type_1(tetris_t *figure) {
  int x = figure->x[2];
  int y = figure->y[2];

  if (figure->swap == 0) {
    copy_figure_values(
        figure, (tetris_t){{x + 1, x, x, x}, {y - 1, y - 1, y, y + 1}, 0, 0});
  } else if (figure->swap == 1) {
    copy_figure_values(
        figure, (tetris_t){{x + 1, x + 1, x, x - 1}, {y + 1, y, y, y}, 0, 0});
  } else if (figure->swap == 2) {
    copy_figure_values(
        figure, (tetris_t){{x - 1, x, x, x}, {y + 1, y + 1, y, y - 1}, 0, 0});
  } else if (figure->swap == 3) {
    copy_figure_values(
        figure, (tetris_t){{x - 1, x - 1, x, x + 1}, {y - 1, y, y, y}, 0, 0});
  }
  figure->swap += 1;
  figure->swap %= 4;
}

void copy_figure_values(tetris_t *destiny, tetris_t copy) {
  for (int i = 0; i < 4; i++) {
    destiny->x[i] = copy.x[i];
    destiny->y[i] = copy.y[i];
  }
}

void swap_type_0(tetris_t *figure) {
  int x = figure->x[2];
  int y = figure->y[2];
  if (figure->swap == 0) {
    copy_figure_values(
        figure, (tetris_t){{x, x, x, x}, {y - 2, y - 1, y, y + 1}, 0, 0});
  } else if (figure->swap == 1) {
    copy_figure_values(
        figure, (tetris_t){{x - 2, x - 1, x, x + 1}, {y, y, y, y}, 0, 0});
  } else if (figure->swap == 2) {
    x = figure->x[1];
    y = figure->y[2];
    copy_figure_values(
        figure, (tetris_t){{x, x, x, x}, {y - 2, y - 1, y, y + 1}, 0, 0});
  } else if (figure->swap == 3) {
    copy_figure_values(
        figure, (tetris_t){{x - 1, x, x + 1, x + 2}, {y, y, y, y}, 0, 0});
  }
  figure->swap += 1;
  figure->swap %= 4;
}

void move_down(params_t *params) {
  for (int i = 0; i < 4; i++) {
    params->figure->y[i] += 1;
  }
}
void move_left(params_t *params) {
  for (int i = 0; i < 4; i++) {
    params->figure->x[i] -= 1;
  }
}
void move_right(params_t *params) {
  for (int i = 0; i < 4; i++) {
    params->figure->x[i] += 1;
  }
}

void game_over(params_t *params) { params->field->game_is_on = 0; }

UserAction_t get_signal(int user_input) {
  UserAction_t rc = ACTION;
  if (user_input == KEY_UP)
    rc = MOVE_UP;
  else if (user_input == KEY_DOWN)
    rc = MOVE_DOWN;
  else if (user_input == KEY_LEFT)
    rc = MOVE_LEFT;
  else if (user_input == KEY_RIGHT)
    rc = MOVE_RIGHT;
  else if (user_input == 'q')
    rc = TERMINATE;
  else if (user_input == SPACE_KEY)
    rc = PAUSE;
  else if (user_input == ENTER_KEY || user_input == 'e')
    rc = START;
  return rc;
}

void pause_game(params_t *params) {
  params->field->pause = params->field->pause == 0 ? 1 : 0;
}

void sigact(UserAction_t sig, tetris_t *figure, Field *field) {
  Action act = actions[sig];
  if (act) {
    tetris_t temp_figure;
    copy_figure_values(&temp_figure, *figure);
    temp_figure.swap = figure->swap;
    temp_figure.type = figure->type;
    params_t params;
    params.figure = &temp_figure;
    params.field = field;
    if (sig == PAUSE)
      act(&params);
    else if (!field->pause)
      act(&params);
    else
      return;
    if (check(field, temp_figure)) {
      copy_figure_values(figure, temp_figure);
      figure->swap = temp_figure.swap;
      figure->type = temp_figure.type;
    } else if (sig == MOVE_DOWN) {
      for (int i = 0; i < 4; i++) {
        field->screen[figure->y[i]][figure->x[i]] = 1;
        if (figure->y[i] <= PADDING + 1) field->game_is_on = 0;
      }
      tetris_t new = FIGURE.type[field->next];
      field->next = rand() % 7;
      copy_figure_values(figure, new);
      figure->swap = new.swap;
      figure->type = new.type;
    }
    check_fild(field);
  }
}

void check_fild(Field *field) {
  int cnt = 0;
  int from = PADDING + 1;
  int to = (2 + BOARD_X);
  int current = 1 + BOARD_Y;
  int pointer = 1 + BOARD_Y;
  while (pointer > 2) {
    int flag = 1;
    for (int i = from; i < to; i++) {
      if (field->screen[pointer][i] != 1) {
        flag = 0;
        break;
      }
    }
    if (flag) {
      pointer -= 1;
      cnt += 1;
      continue;
    } else if (pointer == current) {
      pointer -= 1;
      current -= 1;
    } else {
      for (int i = from; i < to; i++) {
        field->screen[current][i] = field->screen[pointer][i];
      }
      pointer -= 1;
      current -= 1;
    }
  }
  for (int i = 2; i <= current; i++) {
    for (int i = from; i < to; i++) {
      field->screen[current][i] = 0;
    }
  }
  field->score += score_table(cnt);
  game_settings(field);
}

void game_settings(Field *field) {
  if (field->score / LEVEL_UP_AFTER <= 10 &&
      (int)(field->score / LEVEL_UP_AFTER) != field->level) {
    field->level = field->score / LEVEL_UP_AFTER;
    field->speed = INITIAL_SPEED - SPEED_UP * field->level;
  }
  if (field->high_score < field->score) {
    set_high_score(field->score);
    field->high_score = field->score;
  }
}

int score_table(int cnt) {
  int result = 0;
  if (cnt == 1)
    result = 100;
  else if (cnt == 2)
    result = 300;
  else if (cnt == 3)
    result = 700;
  else if (cnt == 4)
    result = 1500;
  return result;
}

Field init_field() {
  Field field;
  int y = BOARD_Y + 3;
  int x = BOARD_X + 3;
  field.x_end = x;
  field.y_end = y;
  field.x_start = PADDING;
  field.y_start = PADDING;
  field.game_is_on = 1;
  field.score = 0;
  field.next = rand() % 7;
  field.pause = 0;
  field.speed = INITIAL_SPEED;
  field.level = 0;
  field.high_score = get_high_score();
  field.screen = calloc(y, sizeof(int *));
  for (int i = 0; i < y; i++) {
    field.screen[i] = calloc(x, sizeof(int));
  }
  for (int i = 0; i < y; i++) {
    for (int j = 0; j < x; j++) {
      field.screen[i][j] = 0;
      if (j == PADDING || j == (2 + BOARD_X) || i == (2 + BOARD_Y)) {
        field.screen[i][j] = 2;
      }
    }
  }
  return field;
}

void clean_field(Field *field) {
  for (int i = 0; i < field->y_end; i++) {
    free(field->screen[i]);
  }
  free(field->screen);
}

int get_high_score() {
  int score = 0;
  FILE *file = fopen("brick_game/tetris/highscore.txt", "r");
  if (file == NULL) {
    score = 0;
  } else {
    fscanf(file, "%d", &score);
    fclose(file);
  }
  return score;
}

void set_high_score(int score) {
  FILE *file = fopen("brick_game/tetris/highscore.txt", "w");
  fprintf(file, "%d", score);
  fclose(file);
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
  raw();
  nodelay(stdscr, TRUE);
  clear();
  srand(time(NULL));
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
