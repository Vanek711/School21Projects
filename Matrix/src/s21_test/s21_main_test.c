#include <check.h>

#include "s21_matrix_test.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int main() {
  int nfailed;
  Suite *s;
  SRunner *sr;
  s = suite_create("s21_matrix");
  matrix_operations(s);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  nfailed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nfailed ? EXIT_FAILURE : EXIT_SUCCESS;
}
