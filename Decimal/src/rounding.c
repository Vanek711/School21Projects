#include "rounding.h"

#include <stdio.h>
#include <string.h>

#include "arithmetic.h"
#include "s21_decimal_type.h"

#define S21_DECIMAL_SIZE sizeof(a.bits)

/* Author: sebastou */
int s21_floor(s21_decimal a, s21_decimal *res) {
  int flag = 0;
  if (!s21_is_valid_decimal(a) || res == NULL)
    flag = 1;
  else {
    unsigned int rem = 0, fraction = 0;
    while (a.bits[3] != 0x00000000 && a.bits[3] != 0x80000000) {
      s21_short_div((unsigned *)a.bits, S21_MANTISSA_LEN, S21_EXPONENT_BASE,
                    &rem);
      a.bits[3] -= 0x00010000;
      fraction += rem;
    }
    if (fraction != 0 && a.bits[3] == 0x80000000)
      s21_short_add((unsigned int *)a.bits, S21_MANTISSA_LEN, 1);
    memcpy(res->bits, a.bits, S21_DECIMAL_SIZE);
  }
  return flag;
}

/* Author: sebastou */
int s21_round(s21_decimal a, s21_decimal *res) {
  int flag = 0;
  if (!s21_is_valid_decimal(a) || res == NULL)
    flag = 1;
  else {
    unsigned int rem = 0, fraction = 0;
    while (a.bits[3] != 0x00000000 && a.bits[3] != 0x80000000) {
      s21_short_div((unsigned *)a.bits, S21_MANTISSA_LEN, S21_EXPONENT_BASE,
                    &rem);
      a.bits[3] -= 0x00010000;
      fraction += rem;
    }
    if (rem == 5 && fraction == 5) {
      if (a.bits[0] % 2 == 1) {
        s21_short_add((unsigned int *)a.bits, S21_MANTISSA_LEN, 1);
      }
    } else {
      if (rem >= 5) {
        s21_short_add((unsigned int *)a.bits, S21_MANTISSA_SIZE, 1);
      }
    }
    memcpy(res->bits, a.bits, S21_DECIMAL_SIZE);
  }
  return flag;
}

/* Author: sebastou */
int s21_truncate(s21_decimal a, s21_decimal *res) {
  int flag = 0;
  if (!s21_is_valid_decimal(a) || res == NULL)
    flag = 1;
  else {
    unsigned int rem = 0;
    while (a.bits[3] != 0x00000000 && a.bits[3] != 0x80000000) {
      s21_short_div((unsigned *)a.bits, S21_MANTISSA_LEN, S21_EXPONENT_BASE,
                    &rem);
      a.bits[3] -= 0x00010000;
    }
    memcpy(res->bits, a.bits, S21_DECIMAL_SIZE);
  }
  return flag;
}
