#include "test.h"

START_TEST(parse_dot_obj_file_test_success) {
  dot_obj_data dod;
  memset(&dod, 0, sizeof(dod));

  FILE *f = fopen("test.obj", "w");
  fprintf(f, "v 0.0 0.0 0.0\n");
  fprintf(f, "v 1.0 1.0 1.0\n");
  fprintf(f, "f 1 2\n");
  fclose(f);

  int result = parse_dot_obj_file("test.obj", &dod);

  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(dod.v_count, 2);
  ck_assert_int_eq(dod.f_count, 4);
  ck_assert_double_eq_tol(dod.vertices[0], 0.0, EPSILON);
  ck_assert_double_eq_tol(dod.vertices[3], 1.0, EPSILON);
  ck_assert_int_eq(dod.faces[0], 0);
  ck_assert_int_eq(dod.faces[1], 1);
  ck_assert_int_eq(dod.faces[2], 1);
  ck_assert_int_eq(dod.faces[3], 0);

  free_dod(&dod);
  remove("test.obj");
}
END_TEST

START_TEST(parse_dot_obj_file_test_failure) {
  dot_obj_data dod;
  memset(&dod, 0, sizeof(dod));

  int result = parse_dot_obj_file("notfounded.obj", &dod);

  ck_assert_int_eq(result, ERROR);
}
END_TEST

START_TEST(dodalloc_test) {
  dot_obj_data dod;
  memset(&dod, 0, sizeof(dod));

  dod.v_count = 2;
  dod.f_count = 2;

  int result = dodalloc(&dod);
  ck_assert_int_eq(result, OK);

  ck_assert_ptr_nonnull(dod.vertices);
  ck_assert_ptr_nonnull(dod.faces);

  free_dod(&dod);
}
END_TEST

START_TEST(count_v_and_f_test) {
  dot_obj_data dod;
  memset(&dod, 0, sizeof(dod));

  FILE *f = fopen("test.obj", "w");
  fprintf(f, "v 0.0 0.0 0.0\n");
  fprintf(f, "v 1.0 1.0 1.0\n");
  fprintf(f, "v 1.0 1.0 12.0\n");
  fprintf(f, "f 1 2 3 1 2\n");
  fclose(f);

  f = fopen("test.obj", "r");
  count_v_and_f(f, &dod);
  fclose(f);

  ck_assert_int_eq(dod.v_count, 3);
  ck_assert_int_eq(dod.f_count, 10);

  free_dod(&dod);
  remove("test.obj");
}
END_TEST

START_TEST(free_dod_test) {
  dot_obj_data dod;
  memset(&dod, 0, sizeof(dod));

  dod.v_count = 2;
  dod.f_count = 2;
  dod.vertices = malloc(dod.v_count * 3 * sizeof(double));
  dod.faces = malloc(dod.f_count * 2 * sizeof(int));

  free_dod(&dod);

  ck_assert_ptr_null(dod.vertices);
  ck_assert_ptr_null(dod.faces);
}
END_TEST

START_TEST(parse_v_and_f_test_with_comments) {
  dot_obj_data dod;
  memset(&dod, 0, sizeof(dod));

  dod.v_count = 2;
  dod.f_count = 2;
  dod.vertices = malloc(dod.v_count * 3 * sizeof(double));
  dod.faces = malloc(dod.f_count * 2 * sizeof(int));

  FILE *f = fopen("test.obj", "w");
  fprintf(f, "# Comment\n");
  fprintf(f, "v 0.0 0.0 0.0\n");
  fprintf(f, "v 1.0 1.0 1.0\n");
  fprintf(f, "f -1 -2\n");
  fprintf(f, "\n");
  fclose(f);

  f = fopen("test.obj", "r");
  int result = parse_v_and_f(f, &dod);
  fclose(f);

  ck_assert_int_eq(result, OK);
  ck_assert_double_eq_tol(dod.vertices[0], 0.0, EPSILON);
  ck_assert_double_eq_tol(dod.vertices[3], 1.0, EPSILON);
  ck_assert_int_eq(dod.faces[0], 1);
  ck_assert_int_eq(dod.faces[1], 0);
  ck_assert_int_eq(dod.faces[2], 0);
  ck_assert_int_eq(dod.faces[3], 1);

  free(dod.vertices);
  free(dod.faces);
  remove("test.obj");
}
END_TEST

Suite *dot_obj_parser_suite(void) {
  Suite *s;
  TCase *tc_main;

  s = suite_create("dot_obj_parser_suite");
  tc_main = tcase_create("main");
  tcase_add_test(tc_main, parse_dot_obj_file_test_success);
  tcase_add_test(tc_main, parse_dot_obj_file_test_failure);
  tcase_add_test(tc_main, dodalloc_test);
  tcase_add_test(tc_main, count_v_and_f_test);
  tcase_add_test(tc_main, free_dod_test);
  tcase_add_test(tc_main, parse_v_and_f_test_with_comments);

  suite_add_tcase(s, tc_main);
  return s;
}
