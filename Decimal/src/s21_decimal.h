#ifndef S21_DECIMAL_H_SENTRY
#define S21_DECIMAL_H_SENTRY

typedef struct {
#define S21_MANTISSA_LEN 3
#define S21_EXPONENT_BASE 10
#define S21_EXPONENT_MAX 28
  int bits[S21_MANTISSA_LEN + 1];
} s21_decimal;

enum { s21_success, s21_overflow, s21_underflow, s21_division_by_0 };

int s21_add(s21_decimal a, s21_decimal b, s21_decimal *res);
int s21_sub(s21_decimal a, s21_decimal b, s21_decimal *res);
int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *res);
int s21_div(s21_decimal a, s21_decimal b, s21_decimal *res);
int s21_negate(s21_decimal a, s21_decimal *res);

int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

enum { s21_conversion_error = 1 };

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal a, s21_decimal *res);
int s21_round(s21_decimal a, s21_decimal *res);
int s21_truncate(s21_decimal a, s21_decimal *res);

#endif
