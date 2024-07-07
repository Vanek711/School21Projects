#ifndef S21_DECIMAL_TYPE_H_SENTRY
#define S21_DECIMAL_TYPE_H_SENTRY

#include <stdio.h>
#include <string.h>

#include "arithmetic.h"
#include "s21_decimal.h"

#define S21_DECIMAL_SIZE sizeof(a.bits)
#define S21_MANTISSA_SIZE S21_MANTISSA_LEN * sizeof(int)

int s21_is_valid_decimal(s21_decimal d);
int s21_get_exponent(s21_decimal d);
void s21_set_exponent(s21_decimal *d, int exp);
int s21_get_sign(s21_decimal d);
void s21_set_sign(s21_decimal *d, int sign);

void s21_to_common_exponent(s21_decimal a, s21_decimal b,
                            unsigned a_man[2 * S21_MANTISSA_LEN],
                            unsigned b_man[2 * S21_MANTISSA_LEN], int *exp);

int s21_normalize(int sign, unsigned man[2 * S21_MANTISSA_LEN], int exp,
                  s21_decimal *res);

#endif
