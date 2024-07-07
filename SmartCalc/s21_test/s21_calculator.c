#include "../s21_calculator.h"

#include <stdlib.h>

#include "s21_smart_calc.h"

START_TEST(parse_expression_test_1) {
  char* str = (char*)calloc(20, sizeof(char));
  strcpy(str, "1+1");
  char* number = s21_parse_expression(str);
  free(str);
  ck_assert_str_eq(number, "2.000000");
}
END_TEST

START_TEST(parse_expression_test_2) {
  char* str = (char*)calloc(20, sizeof(char));
  strcpy(str, "sqrt(4)");
  char* number = s21_parse_expression(str);
  free(str);
  ck_assert_str_eq(number, "2.000000");
}
END_TEST

START_TEST(parse_expression_test_3) {
  char* str = (char*)calloc(20, sizeof(char));
  strcpy(str, "4/2");
  char* number = s21_parse_expression(str);
  free(str);
  ck_assert_str_eq(number, "2.000000");
}
END_TEST

START_TEST(parse_expression_test_4) {
  char* str = (char*)calloc(20, sizeof(char));
  strcpy(str, "(1 + 1 + 2) / 2");
  char* number = s21_parse_expression(str);
  free(str);
  ck_assert_str_eq(number, "2.000000");
}
END_TEST

static void suite_parse_expression(Suite* s) {
  TCase* tc;
  tc = tcase_create("parse_expression");
  tcase_add_test(tc, parse_expression_test_1);
  tcase_add_test(tc, parse_expression_test_2);
  tcase_add_test(tc, parse_expression_test_3);
  tcase_add_test(tc, parse_expression_test_4);
  suite_add_tcase(s, tc);
}

START_TEST(replace_test_1) {
  char str[20] = "sin(x)";
  char* number = replace_x_with_value(str, 3.14159);
  ck_assert_str_eq(number, "s(3.14159)");
}
END_TEST

START_TEST(replace_test_2) {
  char str[20] = "x";
  char* number = replace_x_with_value(str, 3.14159);
  ck_assert_str_eq(number, "3.14159");
}
END_TEST

START_TEST(replace_test_3) {
  char str[20] = "cos(x)";
  char* number = replace_x_with_value(str, 0);
  ck_assert_str_eq(number, "c(0)");
}
END_TEST

static void suite_replace_x(Suite* s) {
  TCase* tc;
  tc = tcase_create("replace_x");
  tcase_add_test(tc, replace_test_1);
  tcase_add_test(tc, replace_test_2);
  tcase_add_test(tc, replace_test_3);

  suite_add_tcase(s, tc);
}

void calculator_test(Suite* s) {
  suite_parse_expression(s);
  suite_replace_x(s);
}