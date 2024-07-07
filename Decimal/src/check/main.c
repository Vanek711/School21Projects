#include <check.h>
#include <stdlib.h>

#include "arithmetic.h"
#include "compare.h"
#include "convert.h"
#include "rounding.h"
#include "s21_decimal_type.h"

int main() {
  int nfailed;
  Suite *s;
  SRunner *sr;

  s = suite_create("s21_decimal");
  suite_add_arithmetic(s);
  suite_add_convert(s);
  suite_add_compare(s);
  suite_add_rounding(s);
  suite_add_s21_decimal_type(s);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_MINIMAL);
  nfailed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nfailed ? EXIT_FAILURE : EXIT_SUCCESS;
}
