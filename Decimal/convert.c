#include "convert.h"

#include <assert.h>
#include <math.h>   /* pow trunc signbit */
#include <stdlib.h> /* abs atoi*/
#include <string.h> /* memset, memcpy atoi*/

#include "arithmetic.h"
#include "s21_decimal_type.h"

#define MAX_MANTISSA_FOR_FLOAT 999999
#define MAX_MANTISSA_FROM_FLOAT_TO_DECIMAL 7922816
/* Author: sebastou */
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int flag = 0;
  if (dst == NULL)
    flag = 1;
  else {
    memset(dst, 0x00000000, S21_MANTISSA_SIZE + sizeof(int));
    if (src < 0) {
      s21_set_sign(dst, 1);
      src = abs(src);
    }
    memcpy(dst->bits, &src, sizeof(src));
  }
  return flag;
}

/* Author: niggurar */
static s21_decimal get_decimal_from_string_float(char *str, int sign,
                                                 int *status, int exp) {
  s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  unsigned int mantissa =
      strtol(str, NULL, 10) * 1000000 + strtol(str + 2, NULL, 10);
  if (exp > 28 ||
      (exp == 28 && mantissa > MAX_MANTISSA_FROM_FLOAT_TO_DECIMAL) ||
      (exp < -29) || (exp == -29 && mantissa <= 5000000)) {
    *status = s21_conversion_error;
  } else {
    int digits_counter = 6;
    while (mantissa % 10 == 0) {
      mantissa /= 10;
      digits_counter--;
    }
    if (-28 <= exp && exp <= -1) {
      res.bits[0] = mantissa;
      exp = exp - digits_counter;
      exp = abs(exp);
      s21_set_exponent(&res, exp);
      if (sign) s21_set_sign(&res, 1);
    } else if (exp == 0) {
      res.bits[0] = mantissa;
      s21_set_exponent(&res, digits_counter);
      if (sign) s21_set_sign(&res, 1);
    } else if (1 <= exp) {
      res.bits[0] = mantissa;
      s21_decimal ten = {{0x0000000a, 0x00000000, 0x00000000, 0x00000000}};
      while (exp - digits_counter > 0) {
        s21_mul(res, ten, &res);
        exp--;
      }
      if (exp - digits_counter < 0)
        s21_set_exponent(&res, digits_counter - exp);
      if (sign) s21_set_sign(&res, 1);
    }
  }
  return res;
}

/* Author: niggurar */
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int signBit = signbit(src);
  int status = s21_success;
  if (src == 0.0) {
    memset(dst, 0x00000000, S21_MANTISSA_SIZE + sizeof(int));
    if (signBit) s21_set_sign(dst, 1);
  } else if (isinf(src) || isnan(src)) {
    status = s21_conversion_error;
  } else {
    char str[20];
    sprintf(str, "%.6E", fabsf(src));
    char *e_ptr = strchr(str, 'E');
    int result = atoi(e_ptr + 1);
    *dst = get_decimal_from_string_float(str, signBit, &status, result);
  }
  return status;
}

/* Author: sebastou */
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int flag = 0;
  if (dst == NULL || !s21_is_valid_decimal(src)) {
    flag = 1;
  } else {
    unsigned int rem = 0;
    while (src.bits[3] != 0x00000000 && src.bits[3] != 0x80000000) {
      s21_short_div((unsigned *)src.bits, S21_MANTISSA_LEN, S21_EXPONENT_BASE,
                    &rem);
      src.bits[3] -= 0x00010000;
    }
    if ((src.bits[2] != 0 || src.bits[1] != 0) || (src.bits[0] > 0x80000000) ||
        (src.bits[0] == 0x80000000 && src.bits[3] == 0x00000000))
      flag = 1;  // invalid value
    else {
      *dst = abs(src.bits[0]);
      if (src.bits[3] == 0x80000000) *dst *= -1;
    }
  }
  return flag;
}

/* Author: niggurar */
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int status = s21_success;
  if (!dst) status = s21_conversion_error;
  if (!s21_is_valid_decimal(src)) {
    *dst = 0.0;
    status = s21_conversion_error;
  } else {
    *dst = 0.0;
    double tmp = 0.0;
    int sign = s21_get_sign(src), power = s21_get_exponent(src);
    for (int i = 0; i < S21_MANTISSA_LEN * 32; i++) {
      if ((!!(src.bits[i / 32] & (1U << (i % 32)))) != 0) tmp += pow(2.0, i);
    }
    if (tmp > MAX_MANTISSA_FOR_FLOAT) {
      while (tmp > MAX_MANTISSA_FOR_FLOAT) {
        tmp /= 10;
        power--;
      }
      tmp *= 10;
      power++;
      tmp = trunc(tmp);
    }
    for (int i = 0; i < power; i++) tmp = tmp / 10;
    if (sign == 1) tmp *= -1;
    *dst = tmp;
  }
  return status;
}
