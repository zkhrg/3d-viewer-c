#include "test.h"

START_TEST(move_vertices_test) {
  dot_obj_data dod;

  dod.v_count = 2;
  dod.vertices = (double[]){0.0, 0.0, 0.0, 1.0, 1.0, 1.0};

  move_vertices(&dod, 10, 0);
  ck_assert_double_eq_tol(dod.vertices[0], 0.5, EPSILON);
  ck_assert_double_eq_tol(dod.vertices[3], 1.5, EPSILON);
}
END_TEST

START_TEST(scale_vertices_test) {
  dot_obj_data dod;

  dod.v_count = 2;
  dod.vertices = (double[]){1.0, 1.0, 1.0, 2.0, 2.0, 2.0};

  scale_vertices(&dod, 50);
  ck_assert_double_eq_tol(dod.vertices[0], 1.5, EPSILON);
  ck_assert_double_eq_tol(dod.vertices[3], 3.0, EPSILON);
}
END_TEST

START_TEST(scale_vertices_zero_test) {
  dot_obj_data dod;

  dod.v_count = 2;
  dod.vertices = (double[]){1.0, 1.0, 1.0, 2.0, 2.0, 2.0};

  scale_vertices(&dod, 0);
  ck_assert_double_eq_tol(dod.vertices[0], 1.0, EPSILON);
  ck_assert_double_eq_tol(dod.vertices[3], 2.0, EPSILON);
}
END_TEST

START_TEST(rotate_x_zero_angle_test) {
  dot_obj_data dod;

  dod.v_count = 1;
  dod.vertices = (double[]){1.0, 1.0, 1.0};

  rotate_x(&dod, 0);
  ck_assert_double_eq_tol(dod.vertices[1], 1.0, EPSILON);
  ck_assert_double_eq_tol(dod.vertices[2], 1.0, EPSILON);
}
END_TEST

START_TEST(rotate_y_zero_angle_test) {
  dot_obj_data dod;

  dod.v_count = 1;
  dod.vertices = (double[]){1.0, 1.0, 1.0};

  rotate_y(&dod, 0);
  ck_assert_double_eq_tol(dod.vertices[0], 1.0, EPSILON);
  ck_assert_double_eq_tol(dod.vertices[1], 1.0, EPSILON);
}
END_TEST

START_TEST(rotate_z_zero_angle_test) {
  dot_obj_data dod;

  dod.v_count = 1;
  dod.vertices = (double[]){1.0, 1.0, 1.0};

  rotate_z(&dod, 0);
  ck_assert_double_eq_tol(dod.vertices[0], 1.0, EPSILON);
  ck_assert_double_eq_tol(dod.vertices[1], 1.0, EPSILON);
}
END_TEST

START_TEST(move_vertices_edge_test) {
  dot_obj_data dod;

  dod.v_count = 1;
  dod.vertices = (double[]){0.0, 0.0, 0.0};

  move_vertices(&dod, 20, 0);
  ck_assert_double_eq_tol(dod.vertices[0], 1.0, EPSILON);
}
END_TEST

START_TEST(rotate_x_negative_angle_test) {
  dot_obj_data dod;

  dod.v_count = 1;
  dod.vertices = (double[]){1.0, 1.0, 1.0};

  rotate_x(&dod, -90);
  ck_assert_double_eq_tol(dod.vertices[1], -1.0, EPSILON);
  ck_assert_double_eq_tol(dod.vertices[2], 1.0, EPSILON);
}
END_TEST

START_TEST(rotate_z_negative_angle_test) {
  dot_obj_data dod;

  dod.v_count = 1;
  dod.vertices = (double[]){1.0, 1.0, 1.0};

  rotate_z(&dod, -90);
  ck_assert_double_eq_tol(dod.vertices[0], -1.0, EPSILON);
  ck_assert_double_eq_tol(dod.vertices[1], 1.0, EPSILON);
}
END_TEST

START_TEST(rotate_x_180_test) {
  dot_obj_data dod;

  dod.v_count = 1;
  dod.vertices = (double[]){0.0, 1.0, 1.0};

  rotate_x(&dod, 180);
  ck_assert_double_eq_tol(dod.vertices[1], -1.0, EPSILON);
  ck_assert_double_eq_tol(dod.vertices[2], -1.0, EPSILON);
}
END_TEST

START_TEST(rotate_y_180_test) {
  dot_obj_data dod;

  dod.v_count = 1;
  dod.vertices = (double[]){1.0, 0.0, 1.0};

  rotate_y(&dod, 180);
  ck_assert_double_eq_tol(dod.vertices[0], -1.0, EPSILON);
  ck_assert_double_eq_tol(dod.vertices[2], -1.0, EPSILON);
}
END_TEST

START_TEST(rotate_z_180_test) {
  dot_obj_data dod;

  dod.v_count = 1;
  dod.vertices = (double[]){1.0, 1.0, 0.0};

  rotate_z(&dod, 180);
  ck_assert_double_eq_tol(dod.vertices[0], -1.0, EPSILON);
  ck_assert_double_eq_tol(dod.vertices[1], -1.0, EPSILON);
}
END_TEST

START_TEST(rotate_x_360_test) {
  dot_obj_data dod;

  dod.v_count = 1;
  dod.vertices = (double[]){1.0, 1.0, 1.0};

  rotate_x(&dod, 360);
  ck_assert_double_eq_tol(dod.vertices[1], 1.0, EPSILON);
  ck_assert_double_eq_tol(dod.vertices[2], 1.0, EPSILON);
}
END_TEST

START_TEST(rotate_y_360_test) {
  dot_obj_data dod;

  dod.v_count = 1;
  dod.vertices = (double[]){1.0, 1.0, 1.0};

  rotate_y(&dod, 360);
  ck_assert_double_eq_tol(dod.vertices[0], 1.0, EPSILON);
  ck_assert_double_eq_tol(dod.vertices[1], 1.0, EPSILON);
}
END_TEST

START_TEST(rotate_z_360_test) {
  dot_obj_data dod;

  dod.v_count = 1;
  dod.vertices = (double[]){1.0, 1.0, 1.0};

  rotate_z(&dod, 360);
  ck_assert_double_eq_tol(dod.vertices[0], 1.0, EPSILON);
  ck_assert_double_eq_tol(dod.vertices[1], 1.0, EPSILON);
}

END_TEST

Suite *transformations_suite(void) {
  Suite *s;
  TCase *tc_main;

  s = suite_create("transformations_suite");
  tc_main = tcase_create("main");

  tcase_add_test(tc_main, move_vertices_test);
  tcase_add_test(tc_main, scale_vertices_test);
  tcase_add_test(tc_main, scale_vertices_zero_test);
  tcase_add_test(tc_main, rotate_x_zero_angle_test);
  tcase_add_test(tc_main, rotate_y_zero_angle_test);
  tcase_add_test(tc_main, rotate_z_zero_angle_test);
  tcase_add_test(tc_main, move_vertices_edge_test);
  tcase_add_test(tc_main, rotate_x_negative_angle_test);
  tcase_add_test(tc_main, rotate_z_negative_angle_test);
  tcase_add_test(tc_main, rotate_x_180_test);
  tcase_add_test(tc_main, rotate_y_180_test);
  tcase_add_test(tc_main, rotate_z_180_test);
  tcase_add_test(tc_main, rotate_x_360_test);
  tcase_add_test(tc_main, rotate_y_360_test);
  tcase_add_test(tc_main, rotate_z_360_test);

  suite_add_tcase(s, tc_main);
  return s;
}