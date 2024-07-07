#include "../s21_matrix.h"
#include "s21_matrix_test.h"

#define SUCCESS 0
#define MATRIX_FAILURE 1
#define CALCULATE_FAILURE 2

#define EQ_SUCCESS 1
#define EQ_FAILURE 0

START_TEST(create_matrix_test_error_1) {
  matrix_t matrix = {NULL, 0, 0};
  ck_assert_int_eq(s21_create_matrix(1, 1, &matrix), SUCCESS);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_test_error_2) {
  matrix_t matrix;
  ck_assert_int_eq(s21_create_matrix(2, 2, &matrix), SUCCESS);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_test_error_3) {
  matrix_t matrix = {NULL, 0, 0};
  ck_assert_int_eq(s21_create_matrix(0, 2, &matrix), MATRIX_FAILURE);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_test_error_4) {
  matrix_t matrix = {NULL, 0, 0};
  ck_assert_int_eq(s21_create_matrix(0, -1, &matrix), MATRIX_FAILURE);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_test_error_5) {
  matrix_t matrix = {NULL, 0, 0};
  ck_assert_int_eq(s21_create_matrix(-2, -1, &matrix), MATRIX_FAILURE);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_test_error_6) {
  matrix_t matrix = {NULL, 0, 0};
  ck_assert_int_eq(s21_create_matrix(0, 0, &matrix), MATRIX_FAILURE);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_test_error_7) {
  matrix_t matrix = {NULL, 0, 0};
  ck_assert_int_eq(s21_create_matrix(12340, 1292, &matrix), SUCCESS);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_test_error_8) {
  matrix_t matrix = {NULL, 0, 0};
  ck_assert_int_eq(s21_create_matrix(102, 122, &matrix), SUCCESS);
  s21_remove_matrix(&matrix);
}
END_TEST

static void suite_create_and_remove_matrix(Suite *s) {
  TCase *tc;
  tc = tcase_create("create_and_remove_matrix");
  tcase_add_test(tc, create_matrix_test_error_1);
  tcase_add_test(tc, create_matrix_test_error_2);
  tcase_add_test(tc, create_matrix_test_error_3);
  tcase_add_test(tc, create_matrix_test_error_4);
  tcase_add_test(tc, create_matrix_test_error_5);
  tcase_add_test(tc, create_matrix_test_error_6);
  tcase_add_test(tc, create_matrix_test_error_7);
  tcase_add_test(tc, create_matrix_test_error_8);
  suite_add_tcase(s, tc);
}

START_TEST(eq_matrix_test_1) {
  matrix_t eq_matrix_1 = {NULL, 0, 0}, eq_matrix_2 = {NULL, 0, 0};
  ck_assert_int_eq(s21_eq_matrix(&eq_matrix_1, &eq_matrix_2), EQ_FAILURE);
}
END_TEST

START_TEST(eq_matrix_test_2) {
  matrix_t eq_matrix_1, eq_matrix_2;
  s21_create_matrix(1, 1, &eq_matrix_1);
  s21_create_matrix(1, 1, &eq_matrix_2);
  eq_matrix_1.matrix[0][0] = 1;
  eq_matrix_2.matrix[0][0] = 0;
  ck_assert_int_eq(s21_eq_matrix(&eq_matrix_1, &eq_matrix_2), EQ_FAILURE);
  s21_remove_matrix(&eq_matrix_1);
  s21_remove_matrix(&eq_matrix_2);
}
END_TEST

START_TEST(eq_matrix_test_3) {
  matrix_t eq_matrix_1, eq_matrix_2;
  s21_create_matrix(1, 1, &eq_matrix_1);
  s21_create_matrix(1, 1, &eq_matrix_2);
  eq_matrix_1.matrix[0][0] = 1;
  eq_matrix_2.matrix[0][0] = 0;
  ck_assert_int_eq(s21_eq_matrix(&eq_matrix_1, &eq_matrix_2), EQ_FAILURE);
  s21_remove_matrix(&eq_matrix_1);
  s21_remove_matrix(&eq_matrix_2);
}
END_TEST

START_TEST(eq_matrix_test_4) {
  matrix_t eq_matrix_1, eq_matrix_2;
  s21_create_matrix(1, 1, &eq_matrix_1);
  s21_create_matrix(1, 1, &eq_matrix_2);
  eq_matrix_1.matrix[0][0] = 1.0000001;
  eq_matrix_2.matrix[0][0] = 1;
  ck_assert_int_eq(s21_eq_matrix(&eq_matrix_1, &eq_matrix_2), EQ_FAILURE);
  s21_remove_matrix(&eq_matrix_1);
  s21_remove_matrix(&eq_matrix_2);
}
END_TEST

START_TEST(eq_matrix_test_5) {
  matrix_t eq_matrix_1, eq_matrix_2;
  s21_create_matrix(1, 1, &eq_matrix_1);
  s21_create_matrix(1, 1, &eq_matrix_2);
  eq_matrix_1.matrix[0][0] = 1.000001;
  eq_matrix_2.matrix[0][0] = 1;
  ck_assert_int_eq(s21_eq_matrix(&eq_matrix_1, &eq_matrix_2), EQ_FAILURE);
  s21_remove_matrix(&eq_matrix_1);
  s21_remove_matrix(&eq_matrix_2);
}
END_TEST

START_TEST(eq_matrix_test_6) {
  matrix_t eq_matrix_1, eq_matrix_2;
  s21_create_matrix(2, 2, &eq_matrix_1);
  s21_create_matrix(2, 2, &eq_matrix_2);
  eq_matrix_1.matrix[0][0] = 1.000001;
  eq_matrix_1.matrix[0][1] = 1.000001;
  eq_matrix_1.matrix[1][0] = 1.000001;
  eq_matrix_1.matrix[1][1] = 1.000001;
  eq_matrix_2.matrix[0][0] = 1;
  eq_matrix_2.matrix[0][1] = 1;
  eq_matrix_2.matrix[1][0] = 1;
  eq_matrix_2.matrix[1][1] = 1;
  ck_assert_int_eq(s21_eq_matrix(&eq_matrix_1, &eq_matrix_2), EQ_FAILURE);
  s21_remove_matrix(&eq_matrix_1);
  s21_remove_matrix(&eq_matrix_2);
}
END_TEST

START_TEST(eq_matrix_test_7) {
  matrix_t eq_matrix_1, eq_matrix_2;
  s21_create_matrix(2, 2, &eq_matrix_1);
  s21_create_matrix(2, 2, &eq_matrix_2);
  eq_matrix_1.matrix[0][0] = 1.00000001;
  eq_matrix_1.matrix[0][1] = 1.00000001;
  eq_matrix_1.matrix[1][0] = 1.00000001;
  eq_matrix_1.matrix[1][1] = 1.00000001;
  eq_matrix_2.matrix[0][0] = 1;
  eq_matrix_2.matrix[0][1] = 1;
  eq_matrix_2.matrix[1][0] = 1;
  eq_matrix_2.matrix[1][1] = 1;
  ck_assert_int_eq(s21_eq_matrix(&eq_matrix_1, &eq_matrix_2), EQ_SUCCESS);
  s21_remove_matrix(&eq_matrix_1);
  s21_remove_matrix(&eq_matrix_2);
}
END_TEST

START_TEST(eq_matrix_test_8) {
  matrix_t eq_matrix_1, eq_matrix_2;
  s21_create_matrix(2, 2, &eq_matrix_1);
  s21_create_matrix(2, 2, &eq_matrix_2);
  eq_matrix_1.matrix[0][0] = 1.0000001;
  eq_matrix_1.matrix[0][1] = 2.0000001;
  eq_matrix_1.matrix[1][0] = 3.0000001;
  eq_matrix_1.matrix[1][1] = 4.0000001;
  eq_matrix_2.matrix[0][0] = 0.9999999;
  eq_matrix_2.matrix[0][1] = 1.9999999;
  eq_matrix_2.matrix[1][0] = 2.9999999;
  eq_matrix_2.matrix[1][1] = 3.9999999;
  ck_assert_int_eq(s21_eq_matrix(&eq_matrix_1, &eq_matrix_2), EQ_FAILURE);
  s21_remove_matrix(&eq_matrix_1);
  s21_remove_matrix(&eq_matrix_2);
}
END_TEST

START_TEST(eq_matrix_test_9) {
  matrix_t eq_matrix_1, eq_matrix_2;
  s21_create_matrix(2, 2, &eq_matrix_1);
  s21_create_matrix(2, 2, &eq_matrix_2);
  eq_matrix_1.matrix[0][0] = 1.0000001;
  eq_matrix_1.matrix[0][1] = 2.0000001;
  eq_matrix_1.matrix[1][0] = 3.0000001;
  eq_matrix_1.matrix[1][1] = 4.0000001;
  eq_matrix_2.matrix[0][0] = -1.0000001;
  eq_matrix_2.matrix[0][1] = -2.0000001;
  eq_matrix_2.matrix[1][0] = -3.0000001;
  eq_matrix_2.matrix[1][1] = -4.0000001;
  ck_assert_int_eq(s21_eq_matrix(&eq_matrix_1, &eq_matrix_2), EQ_FAILURE);
  s21_remove_matrix(&eq_matrix_1);
  s21_remove_matrix(&eq_matrix_2);
}
END_TEST

START_TEST(eq_matrix_test_10) {
  matrix_t eq_matrix_1, eq_matrix_2;
  s21_create_matrix(2, 2, &eq_matrix_1);
  s21_create_matrix(2, 2, &eq_matrix_2);
  eq_matrix_1.matrix[0][0] = 1.0000001;
  eq_matrix_1.matrix[0][1] = 2.0000001;
  eq_matrix_1.matrix[1][0] = 3.0000001;
  eq_matrix_1.matrix[1][1] = 4.0000001;
  eq_matrix_2.matrix[0][0] = -1.0000001;
  eq_matrix_2.matrix[0][1] = -2.0000001;
  eq_matrix_2.matrix[1][0] = -3.0000001;
  eq_matrix_2.matrix[1][1] = -4.0000001;
  ck_assert_int_eq(s21_eq_matrix(&eq_matrix_1, &eq_matrix_2), EQ_FAILURE);
  s21_remove_matrix(&eq_matrix_1);
  s21_remove_matrix(&eq_matrix_2);
}
END_TEST

START_TEST(eq_matrix_test_11) {
  matrix_t eq_matrix_1, eq_matrix_2;
  s21_create_matrix(2, 2, &eq_matrix_1);
  s21_create_matrix(2, 2, &eq_matrix_2);
  eq_matrix_1.matrix[0][0] = 1.0000001;
  eq_matrix_1.matrix[0][1] = 2.0000001;
  eq_matrix_1.matrix[1][0] = 3.0000001;
  eq_matrix_1.matrix[1][1] = 4.0000001;
  eq_matrix_2.matrix[0][0] = 11.0000001;
  eq_matrix_2.matrix[0][1] = 22.0000001;
  eq_matrix_2.matrix[1][0] = 33.0000001;
  eq_matrix_2.matrix[1][1] = 44.0000001;
  ck_assert_int_eq(s21_eq_matrix(&eq_matrix_1, &eq_matrix_2), EQ_FAILURE);
  s21_remove_matrix(&eq_matrix_1);
  s21_remove_matrix(&eq_matrix_2);
}
END_TEST

START_TEST(eq_matrix_test_12) {
  matrix_t eq_matrix_1 = {NULL, 0, 0}, eq_matrix_2 = {NULL, 0, 0};
  ck_assert_int_eq(s21_eq_matrix(&eq_matrix_1, NULL), EQ_FAILURE);
}
END_TEST

static void suite_eq_matrix(Suite *s) {
  TCase *tc;
  tc = tcase_create("eq_matrix");
  tcase_add_test(tc, eq_matrix_test_1);
  tcase_add_test(tc, eq_matrix_test_2);
  tcase_add_test(tc, eq_matrix_test_3);
  tcase_add_test(tc, eq_matrix_test_4);
  tcase_add_test(tc, eq_matrix_test_5);
  tcase_add_test(tc, eq_matrix_test_6);
  tcase_add_test(tc, eq_matrix_test_7);
  tcase_add_test(tc, eq_matrix_test_8);
  tcase_add_test(tc, eq_matrix_test_9);
  tcase_add_test(tc, eq_matrix_test_10);
  tcase_add_test(tc, eq_matrix_test_11);
  tcase_add_test(tc, eq_matrix_test_12);
  suite_add_tcase(s, tc);
}

START_TEST(sum_matrix_test_1) {
  matrix_t matrix_1, matrix_2, result, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &matrix_2);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  matrix_2.matrix[0][0] = 1;
  eq_matrix.matrix[0][0] = 2;
  if (s21_sum_matrix(&matrix_1, &matrix_2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_sum_matrix(&matrix_1, &matrix_2, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(sum_matrix_test_2) {
  matrix_t matrix_1, matrix_2, result, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &matrix_2);
  matrix_1.matrix[0][0] = 1;
  matrix_2.matrix[0][0] = 1;
  ck_assert_int_eq(s21_sum_matrix(&matrix_1, &matrix_2, &result), SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_test_3) {
  matrix_t matrix_1, matrix_2, result, eq_matrix;
  s21_create_matrix(1, 2, &matrix_1);
  s21_create_matrix(1, 1, &matrix_2);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[0][1] = 2;
  matrix_2.matrix[0][0] = 1;
  eq_matrix.matrix[0][0] = 2;
  ck_assert_int_eq(s21_sum_matrix(&matrix_1, &matrix_2, &result),
                   CALCULATE_FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(sum_matrix_test_4) {
  matrix_t matrix_1, matrix_2, result, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &matrix_2);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1.0 / 0.0;
  matrix_2.matrix[0][0] = NAN;
  eq_matrix.matrix[0][0] = 2;
  if (s21_sum_matrix(&matrix_1, &matrix_2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_sum_matrix(&matrix_1, &matrix_2, &result),
                     CALCULATE_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(sum_matrix_test_5) {
  matrix_t matrix_1, matrix_2, result, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &matrix_2);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 123;
  matrix_2.matrix[0][0] = 123;
  eq_matrix.matrix[0][0] = 246;
  if (s21_sum_matrix(&matrix_1, &matrix_2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_sum_matrix(&matrix_1, &matrix_2, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(sum_matrix_test_6) {
  matrix_t matrix_1, matrix_2, result, eq_matrix;
  s21_create_matrix(2, 1, &matrix_1);
  s21_create_matrix(2, 1, &matrix_2);
  s21_create_matrix(2, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 123;
  matrix_1.matrix[1][0] = 123;
  matrix_2.matrix[0][0] = 123;
  matrix_2.matrix[1][0] = 123;
  eq_matrix.matrix[0][0] = 236;
  eq_matrix.matrix[1][0] = 236;
  if (s21_sum_matrix(&matrix_1, &matrix_2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_FAILURE);
  } else {
    ck_assert_int_eq(s21_sum_matrix(&matrix_1, &matrix_2, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(sum_matrix_test_7) {
  matrix_t matrix_1 = {NULL, 0, 0}, matrix_2 = {NULL, 0, 0},
           result = {NULL, 0, 0};
  ck_assert_int_eq(s21_sum_matrix(&matrix_1, &matrix_2, &result),
                   MATRIX_FAILURE);
}
END_TEST

START_TEST(sum_matrix_test_8) {
  matrix_t matrix_1 = {NULL, 1, 1}, matrix_2 = {NULL, 1, 1},
           result = {NULL, 0, 1};
  ck_assert_int_eq(s21_sum_matrix(&matrix_1, &matrix_2, &result),
                   MATRIX_FAILURE);
}
END_TEST

START_TEST(sum_matrix_test_9) {
  matrix_t matrix_1, matrix_2;
  s21_create_matrix(2, 1, &matrix_1);
  s21_create_matrix(2, 1, &matrix_2);
  matrix_1.matrix[0][0] = 123;
  matrix_1.matrix[1][0] = 123;
  matrix_2.matrix[0][0] = 123;
  matrix_2.matrix[1][0] = 123;
  ck_assert_int_eq(s21_sum_matrix(&matrix_1, &matrix_2, NULL), MATRIX_FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

static void suite_sum_matrix(Suite *s) {
  TCase *tc;
  tc = tcase_create("sum_matrix");
  tcase_add_test(tc, sum_matrix_test_1);
  tcase_add_test(tc, sum_matrix_test_2);
  tcase_add_test(tc, sum_matrix_test_3);
  tcase_add_test(tc, sum_matrix_test_4);
  tcase_add_test(tc, sum_matrix_test_5);
  tcase_add_test(tc, sum_matrix_test_6);
  tcase_add_test(tc, sum_matrix_test_7);
  tcase_add_test(tc, sum_matrix_test_8);
  tcase_add_test(tc, sum_matrix_test_9);
  suite_add_tcase(s, tc);
}

START_TEST(sub_matrix_test_1) {
  matrix_t matrix_1, matrix_2, result, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &matrix_2);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  matrix_2.matrix[0][0] = 1;
  eq_matrix.matrix[0][0] = 0;
  if (s21_sub_matrix(&matrix_1, &matrix_2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_sub_matrix(&matrix_1, &matrix_2, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(sub_matrix_test_2) {
  matrix_t matrix_1, matrix_2, result, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &matrix_2);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  matrix_2.matrix[0][0] = 1;
  eq_matrix.matrix[0][0] = 3;
  if (s21_sub_matrix(&matrix_1, &matrix_2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_FAILURE);
  } else {
    ck_assert_int_eq(s21_sub_matrix(&matrix_1, &matrix_2, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(sub_matrix_test_3) {
  matrix_t matrix_1, matrix_2, result = {NULL, 0, 0};
  s21_create_matrix(1, 2, &matrix_1);
  s21_create_matrix(1, 1, &matrix_2);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[0][1] = 2;
  matrix_2.matrix[0][0] = 1;
  ck_assert_int_eq(s21_sub_matrix(&matrix_1, &matrix_2, &result),
                   CALCULATE_FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(sub_matrix_test_4) {
  matrix_t matrix_1, matrix_2, result, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &matrix_2);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1.0 / 0.0;
  matrix_2.matrix[0][0] = NAN;
  eq_matrix.matrix[0][0] = 2;
  if (s21_sub_matrix(&matrix_1, &matrix_2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_sub_matrix(&matrix_1, &matrix_2, &result),
                     CALCULATE_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(sub_matrix_test_5) {
  matrix_t matrix_1, matrix_2, result, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &matrix_2);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 123;
  matrix_2.matrix[0][0] = 123;
  eq_matrix.matrix[0][0] = 236;
  if (s21_sub_matrix(&matrix_1, &matrix_2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_FAILURE);
  } else {
    ck_assert_int_eq(s21_sub_matrix(&matrix_1, &matrix_2, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(sub_matrix_test_6) {
  matrix_t matrix_1, matrix_2, result, eq_matrix;
  s21_create_matrix(2, 1, &matrix_1);
  s21_create_matrix(2, 1, &matrix_2);
  s21_create_matrix(2, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 123;
  matrix_1.matrix[1][0] = 123;
  matrix_2.matrix[0][0] = 123;
  matrix_2.matrix[1][0] = 123;
  eq_matrix.matrix[0][0] = 236;
  eq_matrix.matrix[1][0] = 236;
  if (s21_sub_matrix(&matrix_1, &matrix_2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_FAILURE);
  } else {
    ck_assert_int_eq(s21_sub_matrix(&matrix_1, &matrix_2, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(sub_matrix_test_7) {
  matrix_t matrix_1 = {NULL, 0, 0}, matrix_2 = {NULL, 0, 0},
           result = {NULL, 0, 0};
  ck_assert_int_eq(s21_sub_matrix(&matrix_1, &matrix_2, &result),
                   MATRIX_FAILURE);
}
END_TEST

START_TEST(sub_matrix_test_8) {
  matrix_t matrix_1 = {NULL, 1, 1}, matrix_2 = {NULL, 1, 1},
           result = {NULL, 0, 1};
  ck_assert_int_eq(s21_sub_matrix(&matrix_1, &matrix_2, &result),
                   MATRIX_FAILURE);
}
END_TEST

START_TEST(sub_matrix_test_9) {
  matrix_t matrix_1, matrix_2;
  s21_create_matrix(2, 1, &matrix_1);
  s21_create_matrix(2, 1, &matrix_2);
  matrix_1.matrix[0][0] = 123;
  matrix_1.matrix[1][0] = 123;
  matrix_2.matrix[0][0] = 123;
  matrix_2.matrix[1][0] = 123;
  ck_assert_int_eq(s21_sub_matrix(&matrix_1, &matrix_2, NULL), MATRIX_FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

static void suite_sub_matrix(Suite *s) {
  TCase *tc;
  tc = tcase_create("sub_matrix");
  tcase_add_test(tc, sub_matrix_test_1);
  tcase_add_test(tc, sub_matrix_test_2);
  tcase_add_test(tc, sub_matrix_test_3);
  tcase_add_test(tc, sub_matrix_test_4);
  tcase_add_test(tc, sub_matrix_test_5);
  tcase_add_test(tc, sub_matrix_test_6);
  tcase_add_test(tc, sub_matrix_test_7);
  tcase_add_test(tc, sub_matrix_test_8);
  tcase_add_test(tc, sub_matrix_test_9);
  suite_add_tcase(s, tc);
}

//------------------------------------------
START_TEST(mult_number_test_1) {
  matrix_t matrix_1, result, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  matrix_1.matrix[0][0] = 1;
  ck_assert_int_eq(s21_mult_number(&matrix_1, 0, &result), SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_test_2) {
  matrix_t matrix_1, result, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  eq_matrix.matrix[0][0] = 3;
  if (s21_mult_number(&matrix_1, 2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_FAILURE);
  } else {
    ck_assert_int_eq(s21_mult_number(&matrix_1, 2, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(mult_number_test_3) {
  matrix_t matrix_1, result, eq_matrix;
  s21_create_matrix(1, 2, &matrix_1);
  s21_create_matrix(1, 2, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[0][1] = 2;
  eq_matrix.matrix[0][0] = 1;
  eq_matrix.matrix[0][1] = 2;
  if (s21_mult_number(&matrix_1, 0, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_FAILURE);
  } else {
    ck_assert_int_eq(s21_mult_number(&matrix_1, 0, &result), MATRIX_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(mult_number_test_4) {
  matrix_t matrix_1, result, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1.0 / 0.0;
  eq_matrix.matrix[0][0] = 2;
  if (s21_mult_number(&matrix_1, 0, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_mult_number(&matrix_1, 0, &result), CALCULATE_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(mult_number_test_5) {
  matrix_t matrix_1, result, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 123;
  eq_matrix.matrix[0][0] = 246;
  if (s21_mult_number(&matrix_1, 2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_mult_number(&matrix_1, 2, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(mult_number_test_6) {
  matrix_t matrix_1, result, eq_matrix;
  s21_create_matrix(2, 1, &matrix_1);
  s21_create_matrix(2, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 123;
  matrix_1.matrix[1][0] = 123;
  eq_matrix.matrix[0][0] = 236;
  eq_matrix.matrix[1][0] = 236;
  if (s21_mult_number(&matrix_1, 2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_FAILURE);
  } else {
    ck_assert_int_eq(s21_mult_number(&matrix_1, 2, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(mult_number_test_7) {
  matrix_t matrix_1 = {NULL, 0, 0}, result = {NULL, 0, 0};
  ck_assert_int_eq(s21_mult_number(&matrix_1, 0, &result), MATRIX_FAILURE);
}
END_TEST

START_TEST(mult_number_test_8) {
  matrix_t matrix_1 = {NULL, 1, 1}, result = {NULL, 0, 1};
  ck_assert_int_eq(s21_mult_number(&matrix_1, 0, &result), MATRIX_FAILURE);
}
END_TEST

START_TEST(mult_number_test_9) {
  matrix_t matrix_1, matrix_2;
  s21_create_matrix(2, 1, &matrix_1);
  matrix_1.matrix[0][0] = 123;
  matrix_1.matrix[1][0] = 123;
  ck_assert_int_eq(s21_mult_number(&matrix_1, 0, NULL), MATRIX_FAILURE);
  s21_remove_matrix(&matrix_1);
}
END_TEST

static void suite_mult_number(Suite *s) {
  TCase *tc;
  tc = tcase_create("mult_number");
  tcase_add_test(tc, mult_number_test_1);
  tcase_add_test(tc, mult_number_test_2);
  tcase_add_test(tc, mult_number_test_3);
  tcase_add_test(tc, mult_number_test_4);
  tcase_add_test(tc, mult_number_test_5);
  tcase_add_test(tc, mult_number_test_6);
  tcase_add_test(tc, mult_number_test_7);
  tcase_add_test(tc, mult_number_test_8);
  tcase_add_test(tc, mult_number_test_9);
  suite_add_tcase(s, tc);
}

//       MULT MATRIX

START_TEST(mult_matrix_test_1) {
  matrix_t matrix_1, matrix_2, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &matrix_2);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  matrix_2.matrix[0][0] = 1;
  eq_matrix.matrix[0][0] = 1;
  if (s21_mult_matrix(&matrix_1, &matrix_2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_2, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(mult_matrix_test_2) {
  matrix_t matrix_1, matrix_2, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &matrix_2);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  matrix_2.matrix[0][0] = 2;
  eq_matrix.matrix[0][0] = 3;
  if (s21_mult_matrix(&matrix_1, &matrix_2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_FAILURE);
  } else {
    ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_2, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(mult_matrix_test_3) {
  matrix_t matrix_1, matrix_2, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(1, 2, &matrix_1);
  s21_create_matrix(1, 1, &matrix_2);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[0][1] = 2;
  matrix_2.matrix[0][0] = 1;
  eq_matrix.matrix[0][0] = 2;
  ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_2, &result),
                   CALCULATE_FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(mult_matrix_test_4) {
  matrix_t matrix_1, matrix_2, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &matrix_2);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1.0 / 0.0;
  matrix_2.matrix[0][0] = NAN;
  eq_matrix.matrix[0][0] = 2;
  if (s21_mult_matrix(&matrix_1, &matrix_2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_2, &result),
                     CALCULATE_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(mult_matrix_test_5) {
  matrix_t matrix_1, matrix_2, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &matrix_2);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 123;
  matrix_2.matrix[0][0] = 123;
  eq_matrix.matrix[0][0] = 15129;
  if (s21_mult_matrix(&matrix_1, &matrix_2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_2, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(mult_matrix_test_6) {
  matrix_t matrix_1, matrix_2, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(2, 1, &matrix_1);
  s21_create_matrix(2, 1, &matrix_2);
  s21_create_matrix(2, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 123;
  matrix_1.matrix[1][0] = 123;
  matrix_2.matrix[0][0] = 123;
  matrix_2.matrix[1][0] = 123;
  eq_matrix.matrix[0][0] = 236;
  eq_matrix.matrix[1][0] = 236;
  if (s21_mult_matrix(&matrix_1, &matrix_2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_FAILURE);
  } else {
    ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_2, &result),
                     CALCULATE_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(mult_matrix_test_7) {
  matrix_t matrix_1, matrix_2, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(2, 1, &matrix_1);
  s21_create_matrix(1, 2, &matrix_2);
  s21_create_matrix(2, 2, &eq_matrix);
  matrix_1.matrix[0][0] = 123;
  matrix_1.matrix[1][0] = 123;
  matrix_2.matrix[0][0] = 123;
  matrix_2.matrix[0][1] = 123;
  eq_matrix.matrix[0][0] = 15129;
  eq_matrix.matrix[1][0] = 15129;
  eq_matrix.matrix[0][1] = 15129;
  eq_matrix.matrix[1][1] = 15129;
  if (s21_mult_matrix(&matrix_1, &matrix_2, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_2, &result),
                     MATRIX_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(mult_matrix_test_8) {
  matrix_t matrix_1 = {NULL, 0, 0}, matrix_2 = {NULL, 0, 0},
           result = {NULL, 0, 0};
  ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_2, &result),
                   MATRIX_FAILURE);
}
END_TEST

START_TEST(mult_matrix_test_9) {
  matrix_t matrix_1 = {NULL, 1, 1}, matrix_2 = {NULL, 1, 1},
           result = {NULL, 0, 1};
  ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_2, &result),
                   MATRIX_FAILURE);
}
END_TEST

START_TEST(mult_matrix_test_10) {
  matrix_t matrix_1, matrix_2;
  s21_create_matrix(2, 1, &matrix_1);
  s21_create_matrix(2, 1, &matrix_2);
  matrix_1.matrix[0][0] = 123;
  matrix_1.matrix[1][0] = 123;
  matrix_2.matrix[0][0] = 123;
  matrix_2.matrix[1][0] = 123;
  ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_2, NULL), MATRIX_FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

static void suite_mult_matrix(Suite *s) {
  TCase *tc;
  tc = tcase_create("mult_matrix");
  tcase_add_test(tc, mult_matrix_test_1);
  tcase_add_test(tc, mult_matrix_test_2);
  tcase_add_test(tc, mult_matrix_test_3);
  tcase_add_test(tc, mult_matrix_test_4);
  tcase_add_test(tc, mult_matrix_test_5);
  tcase_add_test(tc, mult_matrix_test_6);
  tcase_add_test(tc, mult_matrix_test_7);
  tcase_add_test(tc, mult_matrix_test_8);
  tcase_add_test(tc, mult_matrix_test_9);
  tcase_add_test(tc, mult_matrix_test_10);
  suite_add_tcase(s, tc);
}

START_TEST(transpose_matrix_test_1) {
  matrix_t matrix_1, matrix_2, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  eq_matrix.matrix[0][0] = 1;
  if (s21_transpose(&matrix_1, &matrix_2) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&matrix_2, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_transpose(&matrix_1, &matrix_2), MATRIX_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(transpose_matrix_test_2) {
  matrix_t matrix_1, matrix_2, eq_matrix;
  s21_create_matrix(2, 1, &matrix_1);
  s21_create_matrix(1, 2, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[1][0] = 2;
  eq_matrix.matrix[0][0] = 1;
  eq_matrix.matrix[0][1] = 2;
  if (s21_transpose(&matrix_1, &matrix_2) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&matrix_2, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_transpose(&matrix_1, &matrix_2), MATRIX_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(transpose_matrix_test_3) {
  matrix_t matrix_1, matrix_2, eq_matrix;
  s21_create_matrix(2, 1, &matrix_1);
  s21_create_matrix(1, 2, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[1][0] = 2;
  eq_matrix.matrix[0][0] = 1;
  eq_matrix.matrix[0][1] = 2;
  if (s21_transpose(&matrix_1, &matrix_2) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&matrix_2, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_transpose(&matrix_1, &matrix_2), MATRIX_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(transpose_matrix_test_4) {
  matrix_t matrix_1, matrix_2, eq_matrix;
  s21_create_matrix(2, 1, &matrix_1);
  s21_create_matrix(1, 2, &eq_matrix);
  matrix_1.matrix[0][0] = 1.0 / 0.0;
  matrix_1.matrix[1][0] = 2;
  eq_matrix.matrix[0][0] = 1;
  eq_matrix.matrix[0][1] = 2;
  if (s21_transpose(&matrix_1, &matrix_2) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&matrix_2, &eq_matrix), EQ_FAILURE);
  } else {
    ck_assert_int_eq(s21_transpose(&matrix_1, &matrix_2), CALCULATE_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(transpose_matrix_test_5) {
  matrix_t matrix_1 = {NULL, 0, 0}, result = {NULL, 0, 0};
  ck_assert_int_eq(s21_transpose(&matrix_1, &result), MATRIX_FAILURE);
}
END_TEST

START_TEST(transpose_matrix_test_6) {
  matrix_t matrix_1 = {NULL, 1, 1}, result = {NULL, 0, 1};
  ck_assert_int_eq(s21_transpose(&matrix_1, &result), MATRIX_FAILURE);
}
END_TEST

START_TEST(transpose_matrix_test_7) {
  matrix_t matrix_1;
  s21_create_matrix(2, 1, &matrix_1);
  matrix_1.matrix[0][0] = 123;
  matrix_1.matrix[1][0] = 123;
  ck_assert_int_eq(s21_transpose(&matrix_1, NULL), MATRIX_FAILURE);
  s21_remove_matrix(&matrix_1);
}
END_TEST

static void suite_transpose_matrix(Suite *s) {
  TCase *tc;
  tc = tcase_create("eq_matrix");
  tcase_add_test(tc, transpose_matrix_test_1);
  tcase_add_test(tc, transpose_matrix_test_2);
  tcase_add_test(tc, transpose_matrix_test_3);
  tcase_add_test(tc, transpose_matrix_test_4);
  tcase_add_test(tc, transpose_matrix_test_5);
  tcase_add_test(tc, transpose_matrix_test_6);
  tcase_add_test(tc, transpose_matrix_test_7);
  suite_add_tcase(s, tc);
}

START_TEST(calc_number_test_1) {
  matrix_t matrix_1, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  eq_matrix.matrix[0][0] = 1;
  if (s21_calc_complements(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_calc_complements(&matrix_1, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(calc_number_test_2) {
  matrix_t matrix_1, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  eq_matrix.matrix[0][0] = 3;
  if (s21_calc_complements(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_FAILURE);
  } else {
    ck_assert_int_eq(s21_calc_complements(&matrix_1, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(calc_number_test_3) {
  matrix_t matrix_1, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(2, 1, &matrix_1);
  s21_create_matrix(2, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[1][0] = 1;
  eq_matrix.matrix[0][0] = 3;
  eq_matrix.matrix[1][0] = 3;
  if (s21_calc_complements(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_FAILURE);
  } else {
    ck_assert_int_eq(s21_calc_complements(&matrix_1, &result),
                     CALCULATE_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(calc_number_test_4) {
  matrix_t matrix_1, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(1, 2, &matrix_1);
  s21_create_matrix(1, 2, &eq_matrix);
  matrix_1.matrix[0][0] = 1.0 / 0.0;
  matrix_1.matrix[0][1] = 1.0 / 0.0;
  eq_matrix.matrix[0][0] = 2;
  eq_matrix.matrix[0][1] = 2;
  if (s21_calc_complements(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_FAILURE);
  } else {
    ck_assert_int_eq(s21_calc_complements(&matrix_1, &result),
                     CALCULATE_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(calc_number_test_5) {
  matrix_t matrix_1, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(2, 2, &matrix_1);
  s21_create_matrix(2, 2, &eq_matrix);
  matrix_1.matrix[0][0] = 4;
  matrix_1.matrix[0][1] = 1;
  matrix_1.matrix[1][0] = 2;
  matrix_1.matrix[1][1] = 3;
  eq_matrix.matrix[0][0] = 3;
  eq_matrix.matrix[0][1] = -2;
  eq_matrix.matrix[1][0] = -1;
  eq_matrix.matrix[1][1] = 4;
  if (s21_calc_complements(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_calc_complements(&matrix_1, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(calc_number_test_6) {
  matrix_t matrix_1, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(2, 2, &matrix_1);
  s21_create_matrix(2, 2, &eq_matrix);
  matrix_1.matrix[0][1] = 2;
  matrix_1.matrix[1][0] = 3;
  matrix_1.matrix[1][1] = 0;
  matrix_1.matrix[0][0] = 9;
  eq_matrix.matrix[0][0] = 0;
  eq_matrix.matrix[0][1] = -3;
  eq_matrix.matrix[1][0] = -2;
  eq_matrix.matrix[1][1] = 9;
  if (s21_calc_complements(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_calc_complements(&matrix_1, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(calc_number_test_7) {
  matrix_t matrix_1, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[0][1] = 2;
  matrix_1.matrix[0][2] = 3;
  matrix_1.matrix[1][0] = 0;
  matrix_1.matrix[1][1] = 4;
  matrix_1.matrix[1][2] = 2;
  matrix_1.matrix[2][0] = 5;
  matrix_1.matrix[2][1] = 2;
  matrix_1.matrix[2][2] = 1;
  eq_matrix.matrix[0][0] = 0;
  eq_matrix.matrix[0][1] = 10;
  eq_matrix.matrix[0][2] = -20;
  eq_matrix.matrix[1][0] = 4;
  eq_matrix.matrix[1][1] = -14;
  eq_matrix.matrix[1][2] = 8;
  eq_matrix.matrix[2][0] = -8;
  eq_matrix.matrix[2][1] = -2;
  eq_matrix.matrix[2][2] = 4;
  if (s21_calc_complements(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_calc_complements(&matrix_1, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(calc_number_test_8) {
  matrix_t matrix_1 = {NULL, 0, 0}, result = {NULL, 0, 0};
  ck_assert_int_eq(s21_calc_complements(&matrix_1, &result), MATRIX_FAILURE);
}
END_TEST

START_TEST(calc_number_test_9) {
  matrix_t matrix_1 = {NULL, 1, 1}, matrix_2 = {NULL, 1, 1},
           result = {NULL, 0, 1};
  ck_assert_int_eq(s21_calc_complements(&matrix_1, &result), MATRIX_FAILURE);
}
END_TEST

START_TEST(calc_number_test_10) {
  matrix_t matrix_1, matrix_2;
  s21_create_matrix(-1, -1, &matrix_1);
  s21_create_matrix(-1, -1, &matrix_2);

  ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_2, NULL), MATRIX_FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

static void suite_calc_number(Suite *s) {
  TCase *tc;
  tc = tcase_create("calc_matrix");
  tcase_add_test(tc, calc_number_test_1);
  tcase_add_test(tc, calc_number_test_2);
  tcase_add_test(tc, calc_number_test_3);
  tcase_add_test(tc, calc_number_test_4);
  tcase_add_test(tc, calc_number_test_5);
  tcase_add_test(tc, calc_number_test_6);
  tcase_add_test(tc, calc_number_test_7);
  tcase_add_test(tc, calc_number_test_8);
  tcase_add_test(tc, calc_number_test_9);
  tcase_add_test(tc, calc_number_test_10);
  suite_add_tcase(s, tc);
}
//---------------------------------

START_TEST(determinant_number_test_1) {
  matrix_t matrix_1;
  s21_create_matrix(1, 1, &matrix_1);
  matrix_1.matrix[0][0] = 1;
  double result = 0;
  if (s21_determinant(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(s21_determinant(&matrix_1, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(determinant_number_test_2) {
  matrix_t matrix_1;
  s21_create_matrix(3, 3, &matrix_1);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[0][1] = 2;
  matrix_1.matrix[0][2] = 3;
  matrix_1.matrix[1][0] = 4;
  matrix_1.matrix[1][1] = 5;
  matrix_1.matrix[1][2] = 6;
  matrix_1.matrix[2][0] = 7;
  matrix_1.matrix[2][1] = 8;
  matrix_1.matrix[2][2] = 9;

  double result = 0;
  if (s21_determinant(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(s21_determinant(&matrix_1, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(determinant_number_test_3) {
  matrix_t matrix_1;
  s21_create_matrix(3, 3, &matrix_1);
  matrix_1.matrix[0][0] = 9;
  matrix_1.matrix[0][1] = 8;
  matrix_1.matrix[0][2] = 7;
  matrix_1.matrix[1][0] = 6;
  matrix_1.matrix[1][1] = 5;
  matrix_1.matrix[1][2] = 4;
  matrix_1.matrix[2][0] = 3;
  matrix_1.matrix[2][1] = 2;
  matrix_1.matrix[2][2] = 1;
  double result = 0;
  if (s21_determinant(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(s21_determinant(&matrix_1, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(determinant_number_test_4) {
  matrix_t matrix_1;
  s21_create_matrix(3, 3, &matrix_1);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[0][1] = 1;
  matrix_1.matrix[0][2] = 1;
  matrix_1.matrix[1][0] = 1;
  matrix_1.matrix[1][1] = 1;
  matrix_1.matrix[1][2] = 1;
  matrix_1.matrix[2][0] = 1;
  matrix_1.matrix[2][1] = 1;
  matrix_1.matrix[2][2] = 1;
  double result = 0;
  if (s21_determinant(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(result, 0);
  } else {
    ck_assert_int_eq(s21_determinant(&matrix_1, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(determinant_number_test_5) {
  matrix_t matrix_1;
  s21_create_matrix(3, 3, &matrix_1);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[0][1] = -2;
  matrix_1.matrix[0][2] = 3;
  matrix_1.matrix[1][0] = 4;
  matrix_1.matrix[1][1] = 0;
  matrix_1.matrix[1][2] = 6;
  matrix_1.matrix[2][0] = -7;
  matrix_1.matrix[2][1] = 8;
  matrix_1.matrix[2][2] = 9;
  double result = 0;
  if (s21_determinant(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(result, 204);
  } else {
    ck_assert_int_eq(s21_determinant(&matrix_1, &result), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(determinant_number_test_6) {
  matrix_t matrix_1;
  s21_create_matrix(1, 2, &matrix_1);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[0][1] = 1;
  double result = 0;
  if (s21_determinant(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(s21_determinant(&matrix_1, &result), MATRIX_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(determinant_number_test_7) {
  matrix_t matrix_1;
  s21_create_matrix(1, 1, &matrix_1);
  matrix_1.matrix[0][0] = 1;
  double result = 0;
  if (s21_determinant(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(result, 1);
  } else {
    ck_assert_int_eq(s21_determinant(&matrix_1, &result), CALCULATE_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
}
END_TEST

static void suite_determinant_number(Suite *s) {
  TCase *tc;
  tc = tcase_create("determinant_matrix");
  tcase_add_test(tc, determinant_number_test_1);
  tcase_add_test(tc, determinant_number_test_2);
  tcase_add_test(tc, determinant_number_test_3);
  tcase_add_test(tc, determinant_number_test_4);
  tcase_add_test(tc, determinant_number_test_5);
  tcase_add_test(tc, determinant_number_test_6);
  tcase_add_test(tc, determinant_number_test_7);
  suite_add_tcase(s, tc);
}

START_TEST(inverse_matrix_test_1) {
  matrix_t matrix_1, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  eq_matrix.matrix[0][0] = 1;
  if (s21_inverse_matrix(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(inverse_matrix_test_2) {
  matrix_t matrix_1, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 10;
  eq_matrix.matrix[0][0] = 0.1;
  if (s21_inverse_matrix(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(inverse_matrix_test_3) {
  matrix_t matrix_1, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &eq_matrix);
  matrix_1.matrix[0][0] = 1.0 / 0.0;
  eq_matrix.matrix[0][0] = 0.1;
  if (s21_inverse_matrix(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_inverse_matrix(&matrix_1, &result), CALCULATE_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(inverse_matrix_test_4) {
  matrix_t matrix_1, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(1, 2, &matrix_1);
  s21_create_matrix(1, 2, &eq_matrix);
  matrix_1.matrix[0][0] = 1.0;
  matrix_1.matrix[0][1] = 1.0;
  eq_matrix.matrix[0][0] = 0.1;
  if (s21_inverse_matrix(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_FAILURE);
  } else {
    ck_assert_int_eq(s21_inverse_matrix(&matrix_1, &result), CALCULATE_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(inverse_matrix_test_5) {
  matrix_t matrix_1, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(2, 2, &matrix_1);
  s21_create_matrix(2, 2, &eq_matrix);
  matrix_1.matrix[0][0] = 10;
  matrix_1.matrix[0][1] = 5;
  matrix_1.matrix[1][0] = 9;
  matrix_1.matrix[1][1] = 8;
  eq_matrix.matrix[0][0] = (double)8 / 35;
  eq_matrix.matrix[0][1] = (double)-1 / 7;
  eq_matrix.matrix[1][0] = (double)-9 / 35;
  eq_matrix.matrix[1][1] = (double)2 / 7;
  if (s21_inverse_matrix(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_inverse_matrix(&matrix_1, &result), MATRIX_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(inverse_matrix_test_6) {
  matrix_t matrix_1, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &eq_matrix);
  matrix_1.matrix[0][0] = 2;
  matrix_1.matrix[0][1] = 5;
  matrix_1.matrix[0][2] = 7;
  matrix_1.matrix[1][0] = 6;
  matrix_1.matrix[1][1] = 3;
  matrix_1.matrix[1][2] = 4;
  matrix_1.matrix[2][0] = 5;
  matrix_1.matrix[2][1] = -2;
  matrix_1.matrix[2][2] = -3;
  eq_matrix.matrix[0][0] = 1;
  eq_matrix.matrix[0][1] = -1;
  eq_matrix.matrix[0][2] = 1;
  eq_matrix.matrix[1][0] = -38;
  eq_matrix.matrix[1][1] = 41;
  eq_matrix.matrix[1][2] = -34;
  eq_matrix.matrix[2][0] = 27;
  eq_matrix.matrix[2][1] = -29;
  eq_matrix.matrix[2][2] = 24;
  if (s21_inverse_matrix(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  } else {
    ck_assert_int_eq(s21_inverse_matrix(&matrix_1, &result), MATRIX_FAILURE);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(inverse_matrix_test_7) {
  matrix_t matrix_1, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[0][1] = 3;
  matrix_1.matrix[0][2] = 5;
  matrix_1.matrix[1][0] = 1;
  matrix_1.matrix[1][1] = 2;
  matrix_1.matrix[1][2] = 3;
  matrix_1.matrix[2][0] = 1;
  matrix_1.matrix[2][1] = 4;
  matrix_1.matrix[2][2] = 8;
  eq_matrix.matrix[0][0] = -4;
  eq_matrix.matrix[0][1] = 4;
  eq_matrix.matrix[0][2] = 1;
  eq_matrix.matrix[1][0] = 5;
  eq_matrix.matrix[1][1] = -3;
  eq_matrix.matrix[1][2] = -2;
  eq_matrix.matrix[2][0] = -2;
  eq_matrix.matrix[2][1] = 1;
  eq_matrix.matrix[2][2] = 1;
  if (s21_inverse_matrix(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(inverse_matrix_test_8) {
  matrix_t matrix_1, result = {NULL, 0, 0}, eq_matrix;
  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &eq_matrix);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[0][1] = 2;
  matrix_1.matrix[0][2] = 3;
  matrix_1.matrix[1][0] = 1;
  matrix_1.matrix[1][1] = 2;
  matrix_1.matrix[1][2] = 3;
  matrix_1.matrix[2][0] = 1;
  matrix_1.matrix[2][1] = 2;
  matrix_1.matrix[2][2] = 3;
  eq_matrix.matrix[0][0] = -4;
  eq_matrix.matrix[0][1] = 4;
  eq_matrix.matrix[0][2] = 1;
  eq_matrix.matrix[1][0] = 5;
  eq_matrix.matrix[1][1] = -3;
  eq_matrix.matrix[1][2] = -2;
  eq_matrix.matrix[2][0] = -2;
  eq_matrix.matrix[2][1] = 1;
  eq_matrix.matrix[2][2] = 1;
  if (s21_inverse_matrix(&matrix_1, &result) == SUCCESS) {
    ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), EQ_SUCCESS);
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(inverse_matrix_test_9) {
  matrix_t matrix_1 = {NULL, 0, 0}, result = {NULL, 0, 0};
  ck_assert_int_eq(s21_inverse_matrix(&matrix_1, &result), MATRIX_FAILURE);
}
END_TEST

START_TEST(inverse_matrix_test_10) {
  matrix_t matrix_1 = {NULL, 1, 1}, result = {NULL, 0, 1};
  ck_assert_int_eq(s21_inverse_matrix(&matrix_1, &result), MATRIX_FAILURE);
}
END_TEST

START_TEST(inverse_matrix_test_11) {
  matrix_t matrix_1;
  s21_create_matrix(2, 1, &matrix_1);
  matrix_1.matrix[0][0] = 123;
  matrix_1.matrix[1][0] = 123;
  ck_assert_int_eq(s21_inverse_matrix(&matrix_1, NULL), MATRIX_FAILURE);
  s21_remove_matrix(&matrix_1);
}
END_TEST

static void suite_inverse_matrix(Suite *s) {
  TCase *tc;
  tc = tcase_create("inverse_matrix");
  tcase_add_test(tc, inverse_matrix_test_1);
  tcase_add_test(tc, inverse_matrix_test_2);
  tcase_add_test(tc, inverse_matrix_test_3);
  tcase_add_test(tc, inverse_matrix_test_4);
  tcase_add_test(tc, inverse_matrix_test_5);
  tcase_add_test(tc, inverse_matrix_test_6);
  tcase_add_test(tc, inverse_matrix_test_7);
  tcase_add_test(tc, inverse_matrix_test_8);
  tcase_add_test(tc, inverse_matrix_test_9);
  tcase_add_test(tc, inverse_matrix_test_10);
  tcase_add_test(tc, inverse_matrix_test_11);
  suite_add_tcase(s, tc);
}

void matrix_operations(Suite *s) {
  suite_eq_matrix(s);
  suite_create_and_remove_matrix(s);
  suite_sum_matrix(s);
  suite_sub_matrix(s);
  suite_mult_number(s);
  suite_mult_matrix(s);
  suite_transpose_matrix(s);
  suite_calc_number(s);
  suite_determinant_number(s);
  suite_inverse_matrix(s);
}