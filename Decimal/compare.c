#include "compare.h"

#include <assert.h>

#include "s21_decimal_type.h"

/* Author: amycusel */
static int is_equal_zero(s21_decimal a) {
  int res = 0;
  if (a.bits[0] == 0x00000000 && a.bits[1] == 0x00000000 &&
      a.bits[2] == 0x00000000)
    res = 1;
  return res;
}

/* Author: amycusel */
static int compare_mantissa(s21_decimal a, s21_decimal b) {
  unsigned a_man[2 * S21_MANTISSA_LEN], b_man[2 * S21_MANTISSA_LEN];
  int exp = 0;
  s21_to_common_exponent(a, b, a_man, b_man, &exp);
  long long int r = 0;
  int res = 0;
  // res value:
  // 0 - equal
  // 1 - part1 > part2
  //-1 - part < part2
  for (int i = 5; i >= 0 && r == 0; i--) {
    r = (long long int)a_man[i] - (long long int)b_man[i];
  }
  if (r > 0) res = 1;
  if (r < 0) res = -1;
  return res;
}

/* Author: amycusel */
static int compare_sign(s21_decimal a, s21_decimal b) {
  int res = 0;
  // res value:
  // 0 - equal + & +
  // 2 - - & -
  // 1 - a > 0 & b < 0
  //-1 - a < 0 & b > 0
  int sign_a = s21_get_sign(a);
  int sign_b = s21_get_sign(b);
  if (sign_a == 1 && sign_b == 1) res = 2;
  if (sign_a > sign_b) res = -1;
  if (sign_a < sign_b) res = 1;
  return res;
}

/* Author: amycusel */
static void result(s21_decimal a, s21_decimal b, int *res, int cmp_man,
                   int is_g_or_l) {
  switch (compare_sign(a, b)) {
    case 0:  // +&+
      if (cmp_man == 1 && is_g_or_l == 1)
        *res = 1;
      else if (cmp_man == -1 && is_g_or_l == 0)
        *res = 1;
      else
        *res = 0;
      break;
    case 2:  // 2 - - & -
      if (cmp_man == -1 && is_g_or_l == 1)
        *res = 1;
      else if (cmp_man == 1 && is_g_or_l == 0)
        *res = 1;
      else
        *res = 0;
      break;
    case 1:  // 1 - a > 0 & b < 0
      if (is_g_or_l)
        *res = 1;
      else
        *res = 0;
      break;
    case -1:  //-1 - a < 0 & b > 0
      if (is_g_or_l)
        *res = 0;
      else
        *res = 1;
      break;
  }
}

/* Author: amycusel */
int s21_is_less(s21_decimal a, s21_decimal b) {
  return !s21_is_greater_or_equal(a, b);
}

/* Author: amycusel */
int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  assert(s21_is_valid_decimal(a) && s21_is_valid_decimal(b));
  int cmp_man = compare_mantissa(a, b);
  int res = 0;
  if (s21_is_equal(a, b)) {
    res = 1;
  } else {
    result(a, b, &res, cmp_man, 0);
  }
  return res;
}

/* Author: amycusel */
int s21_is_greater(s21_decimal a, s21_decimal b) {
  return !s21_is_less_or_equal(a, b);
}

/* Author: amycusel */
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  assert(s21_is_valid_decimal(a) && s21_is_valid_decimal(b));
  int cmp_man = compare_mantissa(a, b);
  int res = 0;
  if (s21_is_equal(a, b)) {
    res = 1;
  } else {
    result(a, b, &res, cmp_man, 1);
  }
  return res;
}

/* Author: amycusel */
int s21_is_equal(s21_decimal a, s21_decimal b) {
  assert(s21_is_valid_decimal(a) && s21_is_valid_decimal(b));
  int cmp_man = compare_mantissa(a, b);
  int res = 0;
  if (is_equal_zero(a) && is_equal_zero(b)) res = 1;
  if (res == 0 && (compare_sign(a, b) == 0 || compare_sign(a, b) == 2)) {
    if (cmp_man == 0) res = 1;
  }
  return res;
}

/* Author: amycusel */
int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_equal(a, b);
}
