#include "arithmetic.h"

#include <assert.h>
#include <limits.h>
#include <string.h> /* memcpy */

#include "convert.h"
#include "s21_decimal_type.h"

/* Author: niggurar */
void s21_long_add(const unsigned *a, const unsigned *b, int len,
                  unsigned *res) {
  int i = 0;
  unsigned ost = 0;
  assert(a && len > 0 && b && res);
  for (; i < len * 2; i++) {
    unsigned long long sum = (unsigned long long)a[i] + b[i] + ost;
    res[i] = sum % (UINT_MAX + 1ULL);
    ost = sum / (UINT_MAX + 1ULL);
  }
}
/* Author: niggurar */
void s21_short_add(unsigned *a, int alen, unsigned b) {
  assert(a && alen > 0);
  for (int i = 0; i < alen; i++) {
    unsigned long long t = (unsigned long long)a[i] + b;
    a[i] = t % (UINT_MAX + 1ULL);
    b = t / (UINT_MAX + 1ULL);
  }
}

/* Author: niggurar */
#define LEN S21_MANTISSA_LEN
int s21_add(s21_decimal a, s21_decimal b, s21_decimal *res) {
  int a_s, b_s, ok, exp;
  unsigned a_man[2 * LEN], b_man[2 * LEN], man[2 * LEN];
  a_s = s21_get_sign(a);
  b_s = s21_get_sign(b);
  if (a_s != b_s)
    ok = s21_sub(a, b, res);
  else {
    s21_to_common_exponent(a, b, a_man, b_man, &exp);
    s21_long_add(a_man, b_man, LEN, man);
    ok = s21_normalize(a_s, man, exp, res);
  }
  return ok;
}
#undef LEN

/* Author: niggurar */
void s21_long_sub(unsigned *a, const unsigned *b, int len, unsigned *res) {
  int i = 0;
  unsigned long long diff;
  for (; i < 2 * len; i++) {
    if (a[i] >= b[i])
      diff = (unsigned long)a[i] - b[i];
    else {
      diff = (unsigned long long)a[i] + UINT_MAX + 1ULL - b[i];
      a[i + 1] -= 1;
    }
    res[i] = diff;
  }
}

/* Author: niggurar */
void swap(s21_decimal *a, s21_decimal *b) {
  s21_decimal tmp = *a;
  *a = *b;
  *b = tmp;
}

/* Author: niggurar */
#define LEN S21_MANTISSA_LEN
int s21_sub(s21_decimal a, s21_decimal b, s21_decimal *res) {
  int a_s, b_s, ok, exp, comp;
  unsigned a_man[2 * LEN], b_man[2 * LEN], man[2 * LEN];
  a_s = s21_get_sign(a);
  b_s = s21_get_sign(b);
  if (a_s == 0 && b_s == 1) {
    s21_set_sign(&b, 0);
    ok = s21_add(a, b, res);
  } else if (a_s == 1 && b_s == 0) {
    s21_set_sign(&b, 1);
    ok = s21_add(a, b, res);
  } else {
    if (a_s == 1 && b_s == 1) {
      s21_set_sign(&b, 0);
      swap(&a, &b);
      a_s = s21_get_sign(a);
    }
    comp = s21_is_greater_or_equal(a, b);
    if (!comp) swap(&a, &b);
    s21_to_common_exponent(a, b, a_man, b_man, &exp);
    s21_long_sub(a_man, b_man, LEN, man);
    ok = s21_normalize(a_s, man, exp, res);
    if (!comp) s21_set_sign(res, 1);
  }
  return ok;
}
#undef LEN

/* Author: saerakem */
void s21_short_mul(unsigned *a, int alen, unsigned b) {
  int i;
  unsigned long long t = 0;

  assert(a && alen > 0);
  for (i = 0; i < alen; i++) {
    t = (unsigned long long)a[i] * b + t / (UINT_MAX + 1ULL);
    a[i] = t % (UINT_MAX + 1ULL);
  }
  if (t / (UINT_MAX + 1ULL)) {
    a[i] = t / (UINT_MAX + 1ULL);
  }
}

/* Author: saerakem */
void s21_long_mul(const unsigned *a, int alen, const unsigned *b, int blen,
                  unsigned *res) {
  int i, j;
  unsigned long long t;

  assert(a && alen > 0 && b && blen > 0 && res);
  memset(res, 0x00000000, (alen + blen) * sizeof(res[0]));
  for (i = 0; i < alen; i++) {
    t = 0;
    for (j = 0; j < blen; j++) {
      t = (unsigned long long)a[i] * b[j] + res[i + j] + t / (UINT_MAX + 1ULL);
      res[i + j] = t % (UINT_MAX + 1ULL);
    }
    res[i + j] = t / (UINT_MAX + 1ULL);
  }
}

/* Author: saerakem */
#define LEN S21_MANTISSA_LEN
int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *res) {
  int a_s, b_s, a_e, b_e, ok;
  unsigned man[2 * LEN];

  a_s = s21_get_sign(a);
  b_s = s21_get_sign(b);

  s21_long_mul((unsigned *)a.bits, LEN, (unsigned *)b.bits, LEN, man);

  a_e = s21_get_exponent(a);
  b_e = s21_get_exponent(b);

  ok = s21_normalize(a_s ^ b_s, man, a_e + b_e, res);

  return ok;
}
#undef LEN

/* Author: saerakem */
#define LEN S21_MANTISSA_LEN
void s21_mul_and_sub(unsigned *a, const unsigned *b, int len, unsigned k) {
  unsigned b_ext[LEN + 1], p, t;
  int i;

  memcpy(b_ext, b, len * sizeof(*b));
  b_ext[len] = 0x00000000;
  s21_short_mul(b_ext, len, k);
  t = 0;
  for (i = 0; i < len + 1; i++) {
    p = a[i];
    a[i] = p - b_ext[i] - t;
    t = (long long)p - b_ext[i] - t < 0;
  }
}
#undef LEN

/* Author: saerakem */
#define LEN S21_MANTISSA_LEN
void s21_long_div(const unsigned *a, int alen, const unsigned *b, int blen,
                  unsigned *quot, unsigned *rem) {
  unsigned a_norm[2 * LEN + 1], *b_norm, d;
  int i;

  assert(a && alen > 0 && b && blen > 1 && quot && rem);
  memcpy(a_norm, a, alen * sizeof(*a));
  a_norm[alen] = 0x00000000;
  b_norm = rem;
  memcpy(b_norm, b, blen * sizeof(*b));
  d = (UINT_MAX + 1ULL) / (b[blen - 1] + 1ULL);
  s21_short_mul(a_norm, alen, d);
  s21_short_mul(b_norm, blen, d);
  for (i = alen - blen; i >= 0; i--) {
    unsigned long long q, r, t;
    t = a_norm[i + blen] * (UINT_MAX + 1ULL) + a_norm[i + blen - 1];
    q = t / b_norm[blen - 1];
    r = t % b_norm[blen - 1];
    while (q == UINT_MAX + 1ULL ||
           q * b_norm[blen - 2] >
               (UINT_MAX + 1ULL) * r + a_norm[i + blen - 2]) {
      q--;
      r += b_norm[blen - 1];
    }
    s21_mul_and_sub(a_norm + i, b_norm, blen, q);
    quot[i] = q;
  }
  s21_short_div(a_norm, blen, d, &d);
  memcpy(rem, a_norm, blen * sizeof(*a_norm));
}
#undef LEN

/* Author: saerakem */
void s21_short_div(unsigned *a, int alen, unsigned b, unsigned *rem) {
  int i;
  unsigned long long r = 0;

  assert(a && alen > 0 && b && rem);
  for (i = alen - 1; i >= 0; i--) {
    r = (r << 32) + a[i];
    a[i] = r / b;
    r %= b;
  }
  *rem = r;
}

/* Author: saerakem */
#define LEN S21_MANTISSA_LEN
int s21_div(s21_decimal a, s21_decimal b, s21_decimal *res) {
  int a_s, b_s, a_e, b_e, ok, i, j;
  unsigned a_ext[2 * LEN], man[2 * LEN], rem[LEN];

  for (i = LEN - 1; i >= 0 && !b.bits[i]; i--) {
  }
  if (i == -1) {
    ok = s21_division_by_0;
  } else {
    memcpy(a_ext, a.bits, S21_MANTISSA_SIZE);
    memset(a_ext + LEN, 0x00000000, S21_MANTISSA_SIZE);
    for (j = 0; j < S21_EXPONENT_MAX; j++)
      s21_short_mul(a_ext, 2 * LEN, S21_EXPONENT_BASE);

    a_s = s21_get_sign(a);
    b_s = s21_get_sign(b);
    a_e = s21_get_exponent(a);
    b_e = s21_get_exponent(b);
    if (i == 0) {
      s21_short_div(a_ext, 2 * LEN, b.bits[0], rem);
      ok = s21_normalize(a_s ^ b_s, a_ext, a_e - b_e + S21_EXPONENT_MAX, res);
    } else {
      s21_long_div(a_ext, 2 * LEN, (unsigned *)b.bits, i + 1, man, rem);
      memset(man + (2 * LEN - i), 0x00000000, i * sizeof(*man));
      ok = s21_normalize(a_s ^ b_s, man, a_e - b_e + S21_EXPONENT_MAX, res);
    }
  }

  return ok;
}
#undef LEN

/* Author: amycusel */
int s21_negate(s21_decimal a, s21_decimal *res) {
  assert(s21_is_valid_decimal(a) && res);
  int r = !s21_is_valid_decimal(a);
  *res = a;
  res->bits[3] = a.bits[3] ^ 0x80000000;
  return r;
}
