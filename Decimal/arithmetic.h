#ifndef ARITHMETIC_H_SENTRY
#define ARITHMETIC_H_SENTRY

#include "s21_decimal.h"

void s21_short_add(unsigned *a, int alen, unsigned b);

void s21_long_add(const unsigned *a, const unsigned *b, int len, unsigned *res);

void s21_long_sub(unsigned *a, const unsigned *b, int len, unsigned *res);

void s21_short_mul(unsigned *a, int alen, unsigned b);

void s21_long_mul(const unsigned *a, int alen, const unsigned *b, int blen,
                  unsigned *res);

void s21_mul_and_sub(unsigned *a, const unsigned *b, int len, unsigned k);

void s21_short_div(unsigned *a, int alen, unsigned b, unsigned *rem);

void s21_long_div(const unsigned *a, int alen, const unsigned *b, int blen,
                  unsigned *quot, unsigned *rem);

#endif
