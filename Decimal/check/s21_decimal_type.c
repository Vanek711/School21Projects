#include "s21_decimal_type.h"

#include "../s21_decimal_type.h"

#define S21_IS_VALID_DECIMAL_NTESTS 15

#define S21_IS_VALID_DECIMAL_INPUT                            \
  {                                                           \
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},       \
        {{0x00000000, 0x00000000, 0x00000000, 0x80000000}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x80010000}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x801c0000}},   \
        {{0x11223344, 0x44332211, 0x32004200, 0x80120000}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x70000000}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x0f000000}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x001d0000}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x0000f000}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x00000f00}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x000000f0}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x0000000f}}, { \
      { 0x11223344, 0x44332211, 0x32004200, 0x81120000 }      \
    }                                                         \
  }

#define S21_IS_VALID_DECIMAL_OUTPUT \
  { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }

#define NTESTS S21_IS_VALID_DECIMAL_NTESTS
START_TEST(check_s21_is_valid_decimal) {
  static s21_decimal input[NTESTS] = S21_IS_VALID_DECIMAL_INPUT;
  static int output[NTESTS] = S21_IS_VALID_DECIMAL_OUTPUT;
  int valid = s21_is_valid_decimal(input[_i]);

  ck_assert_int_eq(valid, output[_i]);
}
#undef S21_IS_VALID_DECIMAL_INPUT
#undef S21_IS_VALID_DECIMAL_OUTPUT
#undef NTESTS

static void suite_add_s21_is_valid_decimal(Suite *s) {
  TCase *tc;
  tc = tcase_create("s21_is_valid_decimal");
#define NTESTS S21_IS_VALID_DECIMAL_NTESTS
  tcase_add_loop_test(tc, check_s21_is_valid_decimal, 0, NTESTS);
#undef NTESTS
  suite_add_tcase(s, tc);
}

#define S21_DECIMAL_GET_EXPONENT_NTESTS 5

#define S21_DECIMAL_GET_EXPONENT_INPUT                        \
  {                                                           \
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},       \
        {{0x00010000, 0x000f0000, 0x001c0000, 0x00010000}},   \
        {{0x93453245, 0x09345235, 0x23643342, 0x80050000}},   \
        {{0x93453245, 0x09345235, 0x23234342, 0x80100000}}, { \
      { 0x23453245, 0x22345235, 0x53643342, 0x801c0000 }      \
    }                                                         \
  }

#define S21_DECIMAL_GET_EXPONENT_OUTPUT \
  { 0x00, 0x01, 0x05, 0x10, 0x1c }

#define NTESTS S21_DECIMAL_GET_EXPONENT_NTESTS
START_TEST(check_s21_decimal_get_exponent) {
  static s21_decimal input[NTESTS] = S21_DECIMAL_GET_EXPONENT_INPUT;
  static int output[NTESTS] = S21_DECIMAL_GET_EXPONENT_OUTPUT;
  int exp = s21_get_exponent(input[_i]);

  ck_assert_int_eq(exp, output[_i]);
}
END_TEST

#undef S21_DECIMAL_GET_EXPONENT_INPUT
#undef S21_DECIMAL_GET_EXPONENT_OUTPUT
#undef NTESTS

static void suite_add_s21_decimal_get_exponent(Suite *s) {
  TCase *tc;
  tc = tcase_create("s21_get_exponent");
#define NTESTS S21_DECIMAL_GET_EXPONENT_NTESTS
  tcase_add_loop_test(tc, check_s21_decimal_get_exponent, 0, NTESTS);
#undef NTESTS
  suite_add_tcase(s, tc);
}

#define S21_DECIMAL_SET_EXPONENT_NTESTS 5

#define S21_DECIMAL_SET_EXPONENT_INPUT_DECIMAL                \
  {                                                           \
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},       \
        {{0x00000000, 0x00000000, 0x00000000, 0x001a0000}},   \
        {{0xffffffff, 0xffffffff, 0xffffffff, 0x80050000}},   \
        {{0x23482347, 0x23947234, 0x34732477, 0x80080000}}, { \
      { 0x92843434, 0x92343247, 0x82345323, 0x801c0000 }      \
    }                                                         \
  }

#define S21_DECIMAL_SET_EXPONENT_INPUT_EXPONENT \
  { 0x01, 0x04, 0x00, 0x1c, 0x1c }

#define S21_DECIMAL_SET_EXPONENT_OUTPUT                       \
  {                                                           \
    {{0x00000000, 0x00000000, 0x00000000, 0x00010000}},       \
        {{0x00000000, 0x00000000, 0x00000000, 0x00040000}},   \
        {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}},   \
        {{0x23482347, 0x23947234, 0x34732477, 0x801c0000}}, { \
      { 0x92843434, 0x92343247, 0x82345323, 0x801c0000 }      \
    }                                                         \
  }

#define NTESTS S21_DECIMAL_SET_EXPONENT_NTESTS
START_TEST(check_s21_decimal_set_exponent) {
  static s21_decimal dec[NTESTS] = S21_DECIMAL_SET_EXPONENT_INPUT_DECIMAL;
  static int exp[NTESTS] = S21_DECIMAL_SET_EXPONENT_INPUT_EXPONENT;
  static s21_decimal output[NTESTS] = S21_DECIMAL_SET_EXPONENT_OUTPUT;

  s21_set_exponent(dec + _i, exp[_i]);

  ck_assert_mem_eq(dec + _i, output + _i, sizeof(output[_i]));
}
END_TEST

#undef S21_DECIMAL_SET_EXPONENT_INPUT_DECIMAL
#undef S21_DECIMAL_SET_EXPONENT_INPUT_EXPONENT
#undef S21_DECIMAL_SET_EXPONENT_OUTPUT
#undef NTESTS

static void suite_add_s21_decimal_set_exponent(Suite *s) {
  TCase *tc;
  tc = tcase_create("s21_set_exponent");
#define NTESTS S21_DECIMAL_SET_EXPONENT_NTESTS
  tcase_add_loop_test(tc, check_s21_decimal_set_exponent, 0, NTESTS);
#undef NTESTS
  suite_add_tcase(s, tc);
}

#define S21_DECIMAL_GET_SIGN_NTESTS 5

#define S21_DECIMAL_GET_SIGN_INPUT                            \
  {                                                           \
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},       \
        {{0x00000000, 0x00000000, 0x00000000, 0x80000000}},   \
        {{0x02347350, 0x23742394, 0x29942375, 0x801b0000}},   \
        {{0x12344321, 0x29348124, 0x92384238, 0x001c0000}}, { \
      { 0x00123412, 0x20273450, 0x73423424, 0x801c0000 }      \
    }                                                         \
  }

#define S21_DECIMAL_GET_SIGN_OUTPUT \
  { 0, 1, 1, 0, 1 }

#define NTESTS S21_DECIMAL_GET_SIGN_NTESTS
START_TEST(check_s21_decimal_get_sign) {
  static s21_decimal input[NTESTS] = S21_DECIMAL_GET_SIGN_INPUT;
  static int output[NTESTS] = S21_DECIMAL_GET_SIGN_OUTPUT;
  int sign = s21_get_sign(input[_i]);

  ck_assert_int_eq(sign, output[_i]);
}
END_TEST

#undef S21_DECIMAL_GET_SIGN_INPUT
#undef S21_DECIMAL_GET_SIGN_OUTPUT
#undef NTESTS

static void suite_add_s21_decimal_get_sign(Suite *s) {
  TCase *tc;
  tc = tcase_create("s21_get_sign");
#define NTESTS S21_DECIMAL_GET_SIGN_NTESTS
  tcase_add_loop_test(tc, check_s21_decimal_get_sign, 0, NTESTS);
#undef NTESTS
  suite_add_tcase(s, tc);
}

#define S21_DECIMAL_SET_SIGN_NTESTS 5

#define S21_DECIMAL_SET_SIGN_INPUT_DECIMAL                    \
  {                                                           \
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},       \
        {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x80000000}},   \
        {{0x82165324, 0x23432423, 0x43241542, 0x00170000}}, { \
      { 0x72412045, 0x18234727, 0x46263436, 0x801c0000 }      \
    }                                                         \
  }

#define S21_DECIMAL_SET_SIGN_INPUT_SIGN \
  { 0, 1, 1, 1, 0 }

#define S21_DECIMAL_SET_SIGN_OUTPUT                           \
  {                                                           \
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},       \
        {{0x00000000, 0x00000000, 0x00000000, 0x80000000}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x80000000}},   \
        {{0x82165324, 0x23432423, 0x43241542, 0x80170000}}, { \
      { 0x72412045, 0x18234727, 0x46263436, 0x001c0000 }      \
    }                                                         \
  }

#define NTESTS S21_DECIMAL_SET_SIGN_NTESTS
START_TEST(check_s21_decimal_set_sign) {
  static s21_decimal dec[NTESTS] = S21_DECIMAL_SET_SIGN_INPUT_DECIMAL;
  static int sign[NTESTS] = S21_DECIMAL_SET_SIGN_INPUT_SIGN;
  static s21_decimal output[NTESTS] = S21_DECIMAL_SET_SIGN_OUTPUT;

  s21_set_sign(dec + _i, sign[_i]);

  ck_assert_mem_eq(dec + _i, output + _i, sizeof(output[_i]));
}
END_TEST

#undef S21_DECIMAL_SET_SIGN_INPUT_DECIMAL
#undef S21_DECIMAL_SET_SIGN_INPUT_SIGN
#undef S21_DECIMAL_SET_SIGN_OUTPUT
#undef NTESTS

static void suite_add_s21_decimal_set_sign(Suite *s) {
  TCase *tc;
  tc = tcase_create("s21_set_sign");
#define NTESTS S21_DECIMAL_SET_SIGN_NTESTS
  tcase_add_loop_test(tc, check_s21_decimal_set_sign, 0, NTESTS);
#undef NTESTS
  suite_add_tcase(s, tc);
}

void suite_add_s21_decimal_type(Suite *s) {
  suite_add_s21_is_valid_decimal(s);
  suite_add_s21_decimal_get_exponent(s);
  suite_add_s21_decimal_set_exponent(s);
  suite_add_s21_decimal_get_sign(s);
  suite_add_s21_decimal_set_sign(s);
}
