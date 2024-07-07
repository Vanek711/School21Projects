#include "s21_decimal_type.h"

#include <assert.h>
#include <string.h> /* memset, memcpy */

#include "arithmetic.h"

/* Author: saerakem */
int s21_is_valid_decimal(s21_decimal d) {
  const unsigned b = d.bits[S21_MANTISSA_LEN];
  return !(b & 0x7f00ffff) && ((b & 0x00ff0000) >> 0x10 <= S21_EXPONENT_MAX);
}

/* Author: saerakem */
int s21_get_exponent(s21_decimal d) {
  const unsigned b = d.bits[S21_MANTISSA_LEN];
  assert(s21_is_valid_decimal(d));
  return (b & 0x00ff0000) >> 0x10;
}

/* Author: saerakem */
void s21_set_exponent(s21_decimal *d, int exp) {
  unsigned *b;
  assert(d && s21_is_valid_decimal(*d));
  assert(exp >= 0 && exp <= S21_EXPONENT_MAX);
  b = (unsigned *)d->bits + S21_MANTISSA_LEN;
  *b &= 0xff00ffff;
  *b |= exp << 0x10;
}

/* Author: saerakem */
int s21_get_sign(s21_decimal d) {
  const unsigned b = d.bits[S21_MANTISSA_LEN];
  assert(s21_is_valid_decimal(d));
  return !!(b & 0x80000000);
}

/* Author: saerakem */
void s21_set_sign(s21_decimal *d, int sign) {
  unsigned *b;
  assert(d && s21_is_valid_decimal(*d) && (sign == 0 || sign == 1));
  b = (unsigned *)d->bits + S21_MANTISSA_LEN;
  *b &= 0x00ff0000;
  *b |= (unsigned)sign << 0x1f;
}

/* Author: saerakem */
void s21_to_common_exponent(s21_decimal a, s21_decimal b,
                            unsigned a_man[2 * S21_MANTISSA_LEN],
                            unsigned b_man[2 * S21_MANTISSA_LEN], int *exp) {
  int a_exp, b_exp;

  assert(a_man && b_man && exp);
  a_exp = s21_get_exponent(a);
  b_exp = s21_get_exponent(b);
  if (a_exp < b_exp) {
    s21_to_common_exponent(b, a, b_man, a_man, exp);
  } else {
    *exp = a_exp;

    memcpy(a_man, a.bits, S21_MANTISSA_SIZE);
    memcpy(b_man, b.bits, S21_MANTISSA_SIZE);
    memset(a_man + S21_MANTISSA_LEN, 0x00000000, S21_MANTISSA_SIZE);
    memset(b_man + S21_MANTISSA_LEN, 0x00000000, S21_MANTISSA_SIZE);

    for (; a_exp > b_exp; b_exp++) {
      s21_short_mul(b_man, 2 * S21_MANTISSA_LEN, S21_EXPONENT_BASE);
    }
  }
}

/* Author: saerakem */
int s21_normalize(int sign, unsigned man[2 * S21_MANTISSA_LEN], int exp,
                  s21_decimal *res) {
  int i, has_rem = 0, ret;
  unsigned r = 0;

  assert((sign == 0 || sign == 1) && man && res);
  assert(exp >= 0 && exp <= 2 * S21_EXPONENT_MAX);
  for (i = 2 * S21_MANTISSA_LEN - 1; !man[i] && i > 0; i--) {
  }
  while (i >= S21_MANTISSA_LEN || (exp > S21_EXPONENT_MAX && i >= 0)) {
    has_rem |= r;
    s21_short_div(man, i + 1, S21_EXPONENT_BASE, &r);
    exp--;
    if (!man[i]) i--;
  }
  if ((2 * r == S21_EXPONENT_BASE && ((!has_rem && man[0] % 2) || has_rem)) ||
      (2 * r > S21_EXPONENT_BASE)) {
    s21_short_add(man, 2 * S21_MANTISSA_LEN, 0x00000001);
    if (man[S21_MANTISSA_LEN]) {
      s21_short_div(man, S21_MANTISSA_LEN + 1, S21_EXPONENT_BASE, &r);
      exp--;
    }
  }
  if (exp < 0) {
    ret = s21_overflow;
  } else if (i == -1) {
    if (has_rem || r) {
      ret = s21_underflow;
    } else {
      ret = s21_success;
      memset(res->bits, 0x00000000, sizeof(res->bits));
    }
  } else {
    ret = s21_success;
    memcpy(res->bits, man, S21_MANTISSA_SIZE);
    res->bits[S21_MANTISSA_LEN] = 0x00000000;
    s21_set_sign(res, sign);
    s21_set_exponent(res, exp);
  }
  return ret;
}
