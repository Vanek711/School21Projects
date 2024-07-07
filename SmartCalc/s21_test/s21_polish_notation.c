#include <stdlib.h>

#include "../s21_calculator.h"
#include "s21_smart_calc.h"

START_TEST(calculate_test_1) {
  char str[20] = "1 1 +";
  double number = s21_calculate(str);
  ck_assert_double_eq(number, 2.0);
}
END_TEST

START_TEST(calculate_test_2) {
  char str[20] = "1 1 *";
  double number = s21_calculate(str);
  ck_assert_double_eq(number, 1.0);
}
END_TEST

START_TEST(calculate_test_3) {
  char str[20] = "1 s 2 ^ 1 c 2 ^ + ";
  double number = s21_calculate(str);
  ck_assert_double_eq_tol(number, 0.54, 0.1);
}
END_TEST

START_TEST(calculate_test_4) {
  char str[20] = "- 1 + l 1";
  double number = s21_calculate(str);
  ck_assert_double_eq_tol(number, 1.0, 0.1);
}
END_TEST

START_TEST(calculate_test_5) {
  char str[30] = "3 n 2 t / 1 a 1 i / + 4 q +";
  double number = s21_calculate(str);
  ck_assert_double_eq_tol(number, 1.428, 0.1);
}
END_TEST

START_TEST(calculate_test_6) {
  char str[20] = "4 q";
  double number = s21_calculate(str);
  ck_assert_double_eq_tol(number, 2, 0.1);
}
END_TEST

START_TEST(calculate_test_7) {
  char str[20] = "m 1";
  double number = s21_calculate(str);
  ck_assert_double_eq_tol(number, 1, 0.1);
}
END_TEST

START_TEST(calculate_test_8) {
  char str[20] = "g 1";
  double number = s21_calculate(str);
  ck_assert_double_eq_tol(number, 1, 0.1);
}
END_TEST

START_TEST(calculate_test_9) {
  char str[20] = "c 0";
  double number = s21_calculate(str);
  ck_assert_double_eq_tol(number, 0, 0.1);
}
END_TEST

static void suite_eq_calculate(Suite* s) {
  TCase* tc;
  tc = tcase_create("eq_calculate");
  tcase_add_test(tc, calculate_test_1);
  tcase_add_test(tc, calculate_test_2);
  tcase_add_test(tc, calculate_test_3);
  tcase_add_test(tc, calculate_test_4);
  tcase_add_test(tc, calculate_test_5);
  tcase_add_test(tc, calculate_test_6);
  tcase_add_test(tc, calculate_test_7);
  tcase_add_test(tc, calculate_test_8);
  tcase_add_test(tc, calculate_test_9);
  suite_add_tcase(s, tc);
}

START_TEST(parser_test_1) {
  char* str = calloc(10, sizeof(char));
  strcpy(str, "1+1");
  char* number = s21_parser(str);
  ck_assert_str_eq(number, "1 1 + ");
}
END_TEST

START_TEST(parser_test_2) {
  char* str = calloc(10, sizeof(char));
  strcpy(str, "1*1");
  char* number = s21_parser(str);
  ck_assert_str_eq(number, "1 1 * ");
}
END_TEST

START_TEST(parser_test_3) {
  char* str = calloc(10, sizeof(char));
  strcpy(str, "sqrt(4)");
  char* number = s21_parser(str);
  ck_assert_str_eq(number, "s q 4 t ");
}
END_TEST

static void suite_eq_parser(Suite* s) {
  TCase* tc;
  tc = tcase_create("eq_parser");
  tcase_add_test(tc, parser_test_1);
  tcase_add_test(tc, parser_test_2);
  tcase_add_test(tc, parser_test_3);

  suite_add_tcase(s, tc);
}

void polish_notation_test(Suite* s) {
  suite_eq_calculate(s);
  suite_eq_parser(s);
}