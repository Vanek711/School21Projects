#include <check.h>

#include "../s21_calculator.h"
#include "s21_smart_calc.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int main() {
  int nfailed;
  Suite *s;
  SRunner *sr;
  s = suite_create("s21_smart_calc");
  stack_test_operations(s);
  scanner_test_operations(s);
  polish_notation_test(s);
  calculator_test(s);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  nfailed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nfailed ? EXIT_FAILURE : EXIT_SUCCESS;
}