#include "../s21_stack.h"

#include "s21_smart_calc.h"

START_TEST(stack_numbers_push_pop_test_1) {
  s21_stack_numbers *stack = NULL;
  double push_value = 3, pop_value;
  s21_stack_numbers_push(&stack, push_value);
  s21_stack_numbers_pop(&stack, &pop_value);
  ck_assert_double_eq(pop_value, push_value);
}
END_TEST

START_TEST(stack_numbers_push_pop_test_2) {
  s21_stack_numbers *stack = NULL;
  double push_value1 = 3, push_value2 = 5, pop_value1, pop_value2;
  s21_stack_numbers_push(&stack, push_value1);
  s21_stack_numbers_push(&stack, push_value2);
  s21_stack_numbers_pop(&stack, &pop_value2);
  s21_stack_numbers_pop(&stack, &pop_value1);
  ck_assert_double_eq(pop_value1, push_value1);
  ck_assert_double_eq(pop_value2, push_value2);
}
END_TEST

START_TEST(stack_numbers_push_pop_test_3) {
  s21_stack_numbers *stack = NULL;
  double push_value1 = 3, push_value2 = 5, push_value3 = 1, pop_value1,
         pop_value2, pop_value3;
  s21_stack_numbers_push(&stack, push_value1);
  s21_stack_numbers_push(&stack, push_value2);
  s21_stack_numbers_push(&stack, push_value3);
  s21_stack_numbers_pop(&stack, &pop_value3);
  s21_stack_numbers_pop(&stack, &pop_value2);
  s21_stack_numbers_pop(&stack, &pop_value1);
  ck_assert_double_eq(pop_value1, push_value1);
  ck_assert_double_eq(pop_value2, push_value2);
  ck_assert_double_eq(pop_value3, push_value3);
}
END_TEST

START_TEST(stack_numbers_push_pop_test_4) {
  s21_stack_numbers *stack = NULL;
  double push_value1 = 3.72, push_value2 = 5.01, push_value3 = 1.001,
         pop_value1, pop_value2, pop_value3;
  s21_stack_numbers_push(&stack, push_value1);
  s21_stack_numbers_push(&stack, push_value2);
  s21_stack_numbers_push(&stack, push_value3);
  s21_stack_numbers_pop(&stack, &pop_value3);
  s21_stack_numbers_pop(&stack, &pop_value2);
  s21_stack_numbers_pop(&stack, &pop_value1);
  ck_assert_double_eq(pop_value1, push_value1);
  ck_assert_double_eq(pop_value2, push_value2);
  ck_assert_double_eq(pop_value3, push_value3);
}
END_TEST

START_TEST(stack_numbers_push_pop_test_5) {
  s21_stack_numbers *stack = NULL;
  double push_value1 = 0.000, push_value2 = 0.000, push_value3 = 0.000,
         push_value4 = 0.000, pop_value1, pop_value2, pop_value3, pop_value4;
  s21_stack_numbers_push(&stack, push_value1);
  s21_stack_numbers_push(&stack, push_value2);
  s21_stack_numbers_push(&stack, push_value3);
  s21_stack_numbers_push(&stack, push_value4);
  s21_stack_numbers_pop(&stack, &pop_value4);
  s21_stack_numbers_pop(&stack, &pop_value3);
  s21_stack_numbers_pop(&stack, &pop_value2);
  s21_stack_numbers_pop(&stack, &pop_value1);
  ck_assert_double_eq(pop_value1, push_value1);
  ck_assert_double_eq(pop_value2, push_value2);
  ck_assert_double_eq(pop_value3, push_value3);
}
END_TEST

static void suite_eq_stack_number(Suite *s) {
  TCase *tc;
  tc = tcase_create("eq_stack_number");
  tcase_add_test(tc, stack_numbers_push_pop_test_1);
  tcase_add_test(tc, stack_numbers_push_pop_test_2);
  tcase_add_test(tc, stack_numbers_push_pop_test_3);
  tcase_add_test(tc, stack_numbers_push_pop_test_4);
  tcase_add_test(tc, stack_numbers_push_pop_test_5);
  suite_add_tcase(s, tc);
}

START_TEST(stack_operations_push_pop_test_1) {
  s21_stack_operations *stack = NULL;
  char push_value = '/', pop_value;
  s21_stack_operations_push(&stack, push_value);
  s21_stack_operations_pop(&stack, &pop_value);
  ck_assert_double_eq(pop_value, push_value);
}
END_TEST

START_TEST(stack_operations_push_pop_test_2) {
  s21_stack_operations *stack = NULL;
  char push_value1 = '/', push_value2 = '(', pop_value1, pop_value2;
  s21_stack_operations_push(&stack, push_value1);
  s21_stack_operations_push(&stack, push_value2);
  s21_stack_operations_pop(&stack, &pop_value2);
  s21_stack_operations_pop(&stack, &pop_value1);
  ck_assert_double_eq(push_value1, pop_value1);
  ck_assert_double_eq(push_value2, pop_value2);
}
END_TEST

START_TEST(stack_operations_push_pop_test_3) {
  s21_stack_operations *stack = NULL;
  char push_value1 = '*', push_value2 = '+', push_value3 = SIN, pop_value1,
       pop_value2, pop_value3;
  s21_stack_operations_push(&stack, push_value1);
  s21_stack_operations_push(&stack, push_value2);
  s21_stack_operations_push(&stack, push_value3);
  s21_stack_operations_pop(&stack, &pop_value3);
  s21_stack_operations_pop(&stack, &pop_value2);
  s21_stack_operations_pop(&stack, &pop_value1);
  ck_assert_double_eq(push_value1, pop_value1);
  ck_assert_double_eq(push_value2, pop_value2);
  ck_assert_double_eq(push_value3, pop_value3);
}
END_TEST

START_TEST(stack_operations_push_pop_test_4) {
  s21_stack_operations *stack = NULL;
  char push_value1 = SQRT, push_value2 = TAN, push_value3 = COS, pop_value1,
       pop_value2, pop_value3;
  s21_stack_operations_push(&stack, push_value1);
  s21_stack_operations_push(&stack, push_value2);
  s21_stack_operations_push(&stack, push_value3);
  s21_stack_operations_pop(&stack, &pop_value3);
  s21_stack_operations_pop(&stack, &pop_value2);
  s21_stack_operations_pop(&stack, &pop_value1);
  ck_assert_double_eq(push_value1, pop_value1);
  ck_assert_double_eq(push_value2, pop_value2);
  ck_assert_double_eq(push_value3, pop_value3);
}
END_TEST

START_TEST(stack_operations_push_pop_test_5) {
  s21_stack_operations *stack = NULL;
  char push_value1 = LOG, push_value2 = LN, push_value3 = MOD, pop_value1,
       pop_value2, pop_value3;
  s21_stack_operations_push(&stack, push_value1);
  s21_stack_operations_push(&stack, push_value2);
  s21_stack_operations_push(&stack, push_value3);
  s21_stack_operations_pop(&stack, &pop_value3);
  s21_stack_operations_pop(&stack, &pop_value2);
  s21_stack_operations_pop(&stack, &pop_value1);
  ck_assert_double_eq(push_value1, pop_value1);
  ck_assert_double_eq(push_value2, pop_value2);
  ck_assert_double_eq(push_value3, pop_value3);
}
END_TEST

START_TEST(stack_operations_push_pop_test_6) {
  s21_stack_operations *stack = NULL;
  char push_value1 = ACOS, push_value2 = ASIN, push_value3 = ATAN, pop_value1,
       pop_value2, pop_value3;
  s21_stack_operations_push(&stack, push_value1);
  s21_stack_operations_push(&stack, push_value2);
  s21_stack_operations_push(&stack, push_value3);
  s21_stack_operations_pop(&stack, &pop_value3);
  s21_stack_operations_pop(&stack, &pop_value2);
  s21_stack_operations_pop(&stack, &pop_value1);
  ck_assert_double_eq(push_value1, pop_value1);
  ck_assert_double_eq(push_value2, pop_value2);
  ck_assert_double_eq(push_value3, pop_value3);
}
END_TEST

START_TEST(stack_operations_push_pop_test_7) {
  s21_stack_operations *stack = NULL;
  char push_value1 = UMINUS, push_value2 = UPLUS, push_value3 = MOD, pop_value1,
       pop_value2, pop_value3;
  s21_stack_operations_push(&stack, push_value1);
  s21_stack_operations_push(&stack, push_value2);
  s21_stack_operations_push(&stack, push_value3);
  s21_stack_operations_pop(&stack, &pop_value3);
  s21_stack_operations_pop(&stack, &pop_value2);
  s21_stack_operations_pop(&stack, &pop_value1);
  ck_assert_double_eq(push_value1, pop_value1);
  ck_assert_double_eq(push_value2, pop_value2);
  ck_assert_double_eq(push_value3, pop_value3);
}
END_TEST

static void suite_eq_stack_operations_push_pop(Suite *s) {
  TCase *tc;
  tc = tcase_create("eq_stack_operations_push_pop");
  tcase_add_test(tc, stack_operations_push_pop_test_1);
  tcase_add_test(tc, stack_operations_push_pop_test_2);
  tcase_add_test(tc, stack_operations_push_pop_test_3);
  tcase_add_test(tc, stack_operations_push_pop_test_4);
  tcase_add_test(tc, stack_operations_push_pop_test_5);
  tcase_add_test(tc, stack_operations_push_pop_test_6);
  tcase_add_test(tc, stack_operations_push_pop_test_7);
  suite_add_tcase(s, tc);
}

START_TEST(stack_operation_test_1) {
  s21_stack_operations *stack = NULL;
  char push_value1 = UMINUS, push_value2 = UPLUS, push_value3 = MOD, pop_value1,
       pop_value2, pop_value3, check_operation;
  s21_stack_operations_push(&stack, push_value1);
  s21_stack_operations_push(&stack, push_value2);
  s21_stack_operations_push(&stack, push_value3);
  s21_stack_check_operation(stack, &check_operation);
  s21_stack_operations_pop(&stack, &pop_value3);
  s21_stack_operations_pop(&stack, &pop_value2);
  s21_stack_operations_pop(&stack, &pop_value1);
  ck_assert_double_eq(push_value1, pop_value1);
  ck_assert_double_eq(push_value2, pop_value2);
  ck_assert_double_eq(push_value3, pop_value3);
  ck_assert_double_eq(push_value3, check_operation);
}
END_TEST

START_TEST(stack_operation_test_2) {
  s21_stack_operations *stack = NULL;
  char push_value1 = '^', push_value2 = '-', push_value3 = '+', pop_value1,
       pop_value2, pop_value3, check_operation;
  s21_stack_operations_push(&stack, push_value1);
  s21_stack_operations_push(&stack, push_value2);
  s21_stack_operations_push(&stack, push_value3);
  s21_stack_check_operation(stack, &check_operation);
  s21_stack_operations_pop(&stack, &pop_value3);
  s21_stack_operations_pop(&stack, &pop_value2);
  s21_stack_operations_pop(&stack, &pop_value1);
  ck_assert_double_eq(push_value1, pop_value1);
  ck_assert_double_eq(push_value2, pop_value2);
  ck_assert_double_eq(push_value3, pop_value3);
  ck_assert_double_eq(push_value3, check_operation);
  ck_assert_double_eq(s21_stack_operations_is_null(stack), 1);
}
END_TEST

static void suite_eq_stack_operations(Suite *s) {
  TCase *tc;
  tc = tcase_create("eq_stack_operations");
  tcase_add_test(tc, stack_operation_test_1);
  tcase_add_test(tc, stack_operation_test_2);
  suite_add_tcase(s, tc);
}

void stack_test_operations(Suite *s) {
  suite_eq_stack_number(s);
  suite_eq_stack_operations_push_pop(s);
  suite_eq_stack_operations(s);
}