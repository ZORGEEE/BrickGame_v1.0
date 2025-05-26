#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../brick_game/tetris/backend.h"
#include "../defines.h"
#include "../gui/cli/frontend.h"

void my_x_ck_equel_figure(tetris_t first, tetris_t second) {
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(first.x[i], second.x[i]);
  }
}

void my_y_ck_equel_figure(tetris_t first, tetris_t second) {
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(first.y[i], second.y[i]);
  }
}

int two_figure_is_equal(tetris_t f1, tetris_t f2) {
  int flag = 1;
  for (int i = 0; i < 4; i++) {
    if (f1.x[i] != f2.x[i] || f1.y[i] != f2.y[i]) {
      flag = 0;
      break;
    }
  }
  return flag;
}

void tester_move_down(Field *field, tetris_t *figure1) {
  tetris_t figure2 = FIGURE.type[figure1->type];
  sigact(MOVE_DOWN, figure1, field);
  while (!two_figure_is_equal(*figure1, figure2)) {
    sigact(MOVE_DOWN, figure1, field);
  }
}

void tester_move_left(Field *field, tetris_t *figure, int index) {
  for (int i = 0; i < index; i++) {
    sigact(MOVE_LEFT, figure, field);
  }
}
void tester_move_right(Field *field, tetris_t *figure, int index) {
  for (int i = 0; i < index; i++) {
    sigact(MOVE_RIGHT, figure, field);
  }
}

START_TEST(memory_allocation) {
  Field field = init_field();
  ck_assert_ptr_nonnull(field.screen);
  clean_field(&field);
}

START_TEST(check_signal) {
  ck_assert_int_eq(get_signal(KEY_UP), MOVE_UP);
  ck_assert_int_eq(get_signal(KEY_DOWN), MOVE_DOWN);
  ck_assert_int_eq(get_signal(KEY_RIGHT), MOVE_RIGHT);
  ck_assert_int_eq(get_signal(KEY_LEFT), MOVE_LEFT);
  ck_assert_int_eq(get_signal('q'), TERMINATE);
  ck_assert_int_eq(get_signal(KEY_ENTER), START);
  ck_assert_int_eq(get_signal(' '), PAUSE);
}

START_TEST(check_movement) {
  params_t params;
  tetris_t new = FIGURE.type[3];
  params.figure = &new;
  params.field = NULL;
  tetris_t old = FIGURE.type[3];

  move_left(&params);
  move_right(&params);

  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(new.x[i], old.x[i]);
    ck_assert_int_eq(new.y[i], old.y[i]);
  }

  move_down(&params);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(new.x[i], old.x[i]);
    ck_assert_int_eq(new.y[i], old.y[i] + 1);
  }
}

START_TEST(check_swapping_figure_type_0) {
  tetris_t new = FIGURE.type[0];
  tetris_t old = FIGURE.type[0];
  params_t params;
  params.figure = &new;
  move_up(&params);
  move_up(&params);
  move_up(&params);
  move_up(&params);
  my_x_ck_equel_figure(new, old);
  my_y_ck_equel_figure(new, old);
}

START_TEST(check_swapping_figure_type_1) {
  tetris_t new = FIGURE.type[1];
  tetris_t old = FIGURE.type[1];
  params_t params;
  params.figure = &new;
  move_up(&params);
  move_up(&params);
  move_up(&params);
  move_up(&params);
  my_x_ck_equel_figure(new, old);
  my_y_ck_equel_figure(new, old);
}
START_TEST(check_swapping_figure_type_2) {
  tetris_t new = FIGURE.type[2];
  tetris_t old = FIGURE.type[2];
  params_t params;
  params.figure = &new;
  move_up(&params);
  move_up(&params);
  move_up(&params);
  move_up(&params);
  my_x_ck_equel_figure(new, old);
  my_y_ck_equel_figure(new, old);
}
START_TEST(check_swapping_figure_type_4) {
  tetris_t new = FIGURE.type[4];
  tetris_t old = FIGURE.type[4];
  params_t params;
  params.figure = &new;
  move_up(&params);
  move_up(&params);
  move_up(&params);
  move_up(&params);
  my_x_ck_equel_figure(new, old);
  my_y_ck_equel_figure(new, old);
}
START_TEST(check_swapping_figure_type_5) {
  tetris_t new = FIGURE.type[5];
  tetris_t old = FIGURE.type[5];
  params_t params;
  params.figure = &new;
  move_up(&params);
  move_up(&params);
  move_up(&params);
  move_up(&params);
  my_x_ck_equel_figure(new, old);
  my_y_ck_equel_figure(new, old);
}

START_TEST(check_swapping_figure_type_6) {
  tetris_t new = FIGURE.type[6];
  tetris_t old = FIGURE.type[6];
  params_t params;
  params.figure = &new;
  move_up(&params);
  move_up(&params);
  move_up(&params);
  move_up(&params);
  new.type = 10;
  move_up(&params);
  my_x_ck_equel_figure(new, old);
  my_y_ck_equel_figure(new, old);
}

START_TEST(check_db) {
  int score = 100;
  set_high_score(100);
  ck_assert_int_eq(score, get_high_score());
}

START_TEST(check_game_over) {
  params_t params;
  Field field = init_field();
  ck_assert_ptr_nonnull(field.screen);
  params.field = &field;
  field.game_is_on = 1;
  game_over(&params);
  ck_assert_int_eq(field.game_is_on, 0);
  clean_field(&field);
}

START_TEST(check_field_test) {
  Field field = init_field();
  Field field2 = init_field();
  tetris_t figure = FIGURE.type[0];
  field.next = 0;
  ck_assert_ptr_nonnull(field.screen);
  for (int i = field.x_start; i < field.x_end - 2; i++) {
    field.next = 0;
    sigact(MOVE_UP, &figure, &field);
    sigact(MOVE_DOWN, &figure, &field);
    sigact(MOVE_DOWN, &figure, &field);
    sigact(MOVE_DOWN, &figure, &field);
    sigact(MOVE_DOWN, &figure, &field);

    tester_move_left(&field, &figure, field.x_end);
    tester_move_right(&field, &figure, i - field.x_start);
    tester_move_down(&field, &figure);
  }
  for (int i = field2.y_start; i < field2.y_end; i++) {
    for (int j = field2.x_start; j < field2.x_end; j++) {
      ck_assert_int_eq(field2.screen[i][j], field.screen[i][j]);
    }
  }
  clean_field(&field);
  clean_field(&field2);
}

START_TEST(check_pause_game) {
  Field field = init_field();
  tetris_t figure = FIGURE.type[0];
  tetris_t figure2 = FIGURE.type[0];

  sigact(MOVE_DOWN, &figure2, &field);
  sigact(PAUSE, &figure, &field);
  sigact(MOVE_DOWN, &figure, &field);
  sigact(MOVE_DOWN, &figure, &field);
  sigact(MOVE_DOWN, &figure, &field);
  sigact(MOVE_DOWN, &figure, &field);
  sigact(PAUSE, &figure, &field);
  sigact(MOVE_DOWN, &figure, &field);

  ck_assert_int_eq(two_figure_is_equal(figure2, figure), 1);
  clean_field(&field);
}

Suite *Tetris_suite() {
  Suite *suite;

  suite = suite_create("Tetris");
  TCase *tcase_core = tcase_create("Core");

  tcase_add_test(tcase_core, memory_allocation);
  tcase_add_test(tcase_core, check_signal);
  tcase_add_test(tcase_core, check_movement);
  tcase_add_test(tcase_core, check_swapping_figure_type_0);
  tcase_add_test(tcase_core, check_swapping_figure_type_1);
  tcase_add_test(tcase_core, check_swapping_figure_type_2);
  tcase_add_test(tcase_core, check_swapping_figure_type_4);
  tcase_add_test(tcase_core, check_swapping_figure_type_5);
  tcase_add_test(tcase_core, check_swapping_figure_type_6);
  tcase_add_test(tcase_core, check_db);
  tcase_add_test(tcase_core, check_game_over);
  tcase_add_test(tcase_core, check_field_test);
  tcase_add_test(tcase_core, check_pause_game);
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main() {
  Suite *suite = Tetris_suite();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_VERBOSE);

  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return (failed_count == 0) ? 0 : 1;
}
