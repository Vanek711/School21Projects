#include <stdlib.h>

#include "../s21_calculator.h"
#include "s21_smart_calc.h"

START_TEST(s21_priority_of_operations_test_1) {
  ck_assert_double_eq(s21_priority_of_operations('/'), 5);
}
END_TEST

START_TEST(s21_priority_of_operations_test_2) {
  ck_assert_double_eq(s21_priority_of_operations('*'), 5);
}
END_TEST

START_TEST(s21_priority_of_operations_test_3) {
  ck_assert_double_eq(s21_priority_of_operations('%'), 5);
}
END_TEST

START_TEST(s21_priority_of_operations_test_4) {
  ck_assert_double_eq(s21_priority_of_operations('^'), 6);
}
END_TEST

START_TEST(s21_priority_of_operations_test_5) {
  ck_assert_double_eq(s21_priority_of_operations('('), 1);
}
END_TEST

START_TEST(s21_priority_of_operations_test_6) {
  ck_assert_double_eq(s21_priority_of_operations('+'), 4);
}
END_TEST

START_TEST(s21_priority_of_operations_test_7) {
  ck_assert_double_eq(s21_priority_of_operations('-'), 4);
}
END_TEST

START_TEST(s21_priority_of_operations_test_8) {
  ck_assert_double_eq(s21_priority_of_operations(COS), 6);
}
END_TEST

static void suite_priority_of_operations(Suite *s) {
  TCase *tc;
  tc = tcase_create("eq_priority_of_operations");
  tcase_add_test(tc, s21_priority_of_operations_test_1);
  tcase_add_test(tc, s21_priority_of_operations_test_2);
  tcase_add_test(tc, s21_priority_of_operations_test_3);
  tcase_add_test(tc, s21_priority_of_operations_test_4);
  tcase_add_test(tc, s21_priority_of_operations_test_5);
  tcase_add_test(tc, s21_priority_of_operations_test_6);
  tcase_add_test(tc, s21_priority_of_operations_test_7);
  tcase_add_test(tc, s21_priority_of_operations_test_8);
  suite_add_tcase(s, tc);
}

START_TEST(replace_ln_test_1) {
  char *str = (char *)calloc(10, sizeof(char));
  strcpy(str, "ln(20)");
  char *return_str = s21_replace_ln(str);
  ck_assert_str_eq(return_str, "l(20)");
}
END_TEST

START_TEST(replace_ln_test_2) {
  char *str = (char *)calloc(10, sizeof(char));
  strcpy(str, "ln(20)");
  char *return_str = s21_replace_ln(str);
  ck_assert_str_eq(return_str, "l(20)");
}
END_TEST

START_TEST(replace_ln_test_3) {
  char *str = (char *)calloc(10, sizeof(char));
  strcpy(str, "ln(20)");
  char *return_str = s21_replace_ln(str);
  ck_assert_str_eq(return_str, "l(20)");
}
END_TEST

static void suite_replace_ln_test(Suite *s) {
  TCase *tc;
  tc = tcase_create("replace_ln");
  tcase_add_test(tc, replace_ln_test_1);
  tcase_add_test(tc, replace_ln_test_2);
  tcase_add_test(tc, replace_ln_test_3);
  suite_add_tcase(s, tc);
}

START_TEST(replace_trigonometric_test_1) {
  char *str = (char *)calloc(10, sizeof(char));
  strcpy(str, "ln(20)");
  char *return_str = s21_replace_trigonometric(str);
  ck_assert_str_eq(return_str, "ln(20)");
}
END_TEST

START_TEST(replace_trigonometric_test_2) {
  char *str = (char *)calloc(20, sizeof(char));
  strcpy(str, "ln(20)");
  char *return_str = s21_replace_trigonometric(str);
  ck_assert_str_eq(return_str, "ln(20)");
}
END_TEST

START_TEST(replace_trigonometric_test_3) {
  char *str = (char *)calloc(30, sizeof(char));
  strcpy(str, "tan(0.5)/ln(20)*sin(1)*cos(x)");
  char *return_str = s21_replace_trigonometric(str);
  ck_assert_str_eq(return_str, "t(0.5)/ln(20)*s(1)*c(x)");
}
END_TEST

static void suite_replace_trigonometric_test(Suite *s) {
  TCase *tc;
  tc = tcase_create("replace_trigonometric");
  tcase_add_test(tc, replace_trigonometric_test_1);
  tcase_add_test(tc, replace_trigonometric_test_2);
  tcase_add_test(tc, replace_trigonometric_test_3);
  suite_add_tcase(s, tc);
}

START_TEST(replace_atrigonometric_test_1) {
  char *str = (char *)calloc(10, sizeof(char));
  strcpy(str, "atan(20)");
  char *return_str = s21_replace_atrigonometric(str);
  ck_assert_str_eq(return_str, "n(20)");
}
END_TEST

START_TEST(replace_atrigonometric_test_2) {
  char *str = (char *)calloc(20, sizeof(char));
  strcpy(str, "atan(20)");
  char *return_str = s21_replace_atrigonometric(str);
  ck_assert_str_eq(return_str, "n(20)");
}
END_TEST

START_TEST(replace_atrigonometric_test_3) {
  char *str = (char *)calloc(30, sizeof(char));
  strcpy(str, "atan(20)");
  char *return_str = s21_replace_atrigonometric(str);
  ck_assert_str_eq(return_str, "n(20)");
}
END_TEST

static void suite_replace_atrigonometric_test(Suite *s) {
  TCase *tc;
  tc = tcase_create("replace_atrigonometric");
  tcase_add_test(tc, replace_atrigonometric_test_1);
  tcase_add_test(tc, replace_atrigonometric_test_2);
  tcase_add_test(tc, replace_atrigonometric_test_3);
  suite_add_tcase(s, tc);
}

START_TEST(input_test_1) {
  char str[20] = "+sin(1)*cos(x)";
  bool flag = s21_test_input_string(str);
  ck_assert_int_eq(flag, true);
}
END_TEST

START_TEST(input_test_2) {
  char str[40] = "sqrt(0.5)/ln(20.......)*sin(1)*cos(x)";
  bool flag = s21_test_input_string(str);
  ck_assert_int_eq(flag, false);
}
END_TEST

START_TEST(input_test_3) {
  char str[40] = "sqrt(0.5)/ln(20)*sin(1)*cos(x)";
  bool flag = s21_test_input_string(str);
  ck_assert_int_eq(flag, true);
}
END_TEST

static void suite_input_test(Suite *s) {
  TCase *tc;
  tc = tcase_create("input_test");
  tcase_add_test(tc, input_test_1);
  tcase_add_test(tc, input_test_2);
  tcase_add_test(tc, input_test_3);
  suite_add_tcase(s, tc);
}

START_TEST(processing_test_1) {
  char *str = (char *)calloc(40, sizeof(char));
  strcpy(str, "ln(20)*sin(1)*acos(x)/atan(10)+11-20");
  char *return_str = s21_processing(str);
  ck_assert_str_eq(return_str, "l(20)*s(1)*a(x)/n(10)+11-20");
}
END_TEST

START_TEST(processing_test_2) {
  char *str = (char *)calloc(50, sizeof(char));
  strcpy(str, "aaaaaaaaaa(20)*sin(1)*acos(x)/atan(10)+11-20");
  char *return_str = s21_processing(str);
  ck_assert_str_eq(return_str, "aaaaaaaaaa(20)*s(1)*a(x)/n(10)+11-20");
}
END_TEST

START_TEST(processing_test_3) {
  char *str = (char *)calloc(40, sizeof(char));
  strcpy(str, "ln(20)*sin(1)*asin(x)/atan(10)+11-20");
  char *return_str = s21_processing(str);
  ck_assert_str_eq(return_str, "l(20)*s(1)*i(x)/n(10)+11-20");
}
END_TEST

static void suite_processing_test(Suite *s) {
  TCase *tc;
  tc = tcase_create("processing_test");
  tcase_add_test(tc, processing_test_1);
  tcase_add_test(tc, processing_test_2);
  tcase_add_test(tc, processing_test_3);
  suite_add_tcase(s, tc);
}

void scanner_test_operations(Suite *s) {
  suite_priority_of_operations(s);
  suite_replace_ln_test(s);
  suite_replace_trigonometric_test(s);
  suite_replace_atrigonometric_test(s);
  suite_input_test(s);
  suite_processing_test(s);
}