#include "../convert.h"

#include <limits.h>

#include "convert.h"

START_TEST(from_int_to_decimal_test_1) {
  s21_decimal value = {.bits[0] = 32, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  s21_decimal test_value = {0};
  s21_from_int_to_decimal(32, &test_value);
  ck_assert_int_eq(value.bits[0], test_value.bits[0]);
  ck_assert_int_eq(value.bits[1], test_value.bits[1]);
  ck_assert_int_eq(value.bits[2], test_value.bits[2]);
  ck_assert_int_eq(value.bits[3], test_value.bits[3]);
}
END_TEST

START_TEST(from_int_to_decimal_test_2) {
  s21_decimal value = {
      .bits[0] = 32, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0x80000000};
  s21_decimal test_value = {0};
  s21_from_int_to_decimal(-32, &test_value);
  ck_assert_int_eq(value.bits[0], test_value.bits[0]);
  ck_assert_int_eq(value.bits[1], test_value.bits[1]);
  ck_assert_int_eq(value.bits[2], test_value.bits[2]);
  ck_assert_int_eq(value.bits[3], test_value.bits[3]);
}
END_TEST

START_TEST(from_int_to_decimal_test_3) {
  s21_decimal value = {
      .bits[0] = 1 << 30, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  s21_decimal test_value = {0};
  s21_from_int_to_decimal(1 << 30, &test_value);
  ck_assert_int_eq(value.bits[0], test_value.bits[0]);
  ck_assert_int_eq(value.bits[1], test_value.bits[1]);
  ck_assert_int_eq(value.bits[2], test_value.bits[2]);
  ck_assert_int_eq(value.bits[3], test_value.bits[3]);
}
END_TEST

START_TEST(from_int_to_decimal_test_4) {
  s21_decimal value = {
      .bits[0] = INT_MAX, .bits[1] = 0, .bits[2] = 0, .bits[3] = INT_MIN};
  s21_decimal test_value = {0};
  s21_from_int_to_decimal(-INT_MAX, &test_value);
  ck_assert_int_eq(value.bits[0], test_value.bits[0]);
  ck_assert_int_eq(value.bits[1], test_value.bits[1]);
  ck_assert_int_eq(value.bits[2], test_value.bits[2]);
  ck_assert_int_eq(value.bits[3], test_value.bits[3]);
}
END_TEST

START_TEST(from_int_to_decimal_test_5) {
  s21_decimal value = {
      .bits[0] = 0xfffffff, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  s21_decimal test_value = {0};
  s21_from_int_to_decimal(0xfffffff, &test_value);
  ck_assert_int_eq(value.bits[0], test_value.bits[0]);
  ck_assert_int_eq(value.bits[1], test_value.bits[1]);
  ck_assert_int_eq(value.bits[2], test_value.bits[2]);
  ck_assert_int_eq(value.bits[3], test_value.bits[3]);
}
END_TEST

START_TEST(from_int_to_decimal_test_6) {
  s21_decimal value = {.bits[0] = 0, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  s21_decimal test_value = {0};
  s21_from_int_to_decimal(0, &test_value);
  ck_assert_int_eq(value.bits[0], test_value.bits[0]);
  ck_assert_int_eq(value.bits[1], test_value.bits[1]);
  ck_assert_int_eq(value.bits[2], test_value.bits[2]);
  ck_assert_int_eq(value.bits[3], test_value.bits[3]);
}
END_TEST

START_TEST(from_int_to_decimal_test_7) {
  s21_decimal value = {
      .bits[0] = INT_MIN, .bits[1] = 0, .bits[2] = 0, .bits[3] = INT_MIN};
  s21_decimal test_value = {0};
  s21_from_int_to_decimal(INT_MIN, &test_value);
  ck_assert_int_eq(value.bits[0], test_value.bits[0]);
  ck_assert_int_eq(value.bits[1], test_value.bits[1]);
  ck_assert_int_eq(value.bits[2], test_value.bits[2]);
  ck_assert_int_eq(value.bits[3], test_value.bits[3]);
}
END_TEST

START_TEST(from_int_to_decimal_test_8) {
  s21_decimal value = {
      .bits[0] = INT_MAX, .bits[1] = 0, .bits[2] = 0, .bits[3] = INT_MIN};
  s21_decimal test_value = {0};
  s21_from_int_to_decimal(INT_MIN + 1, &test_value);
  ck_assert_int_eq(value.bits[0], test_value.bits[0]);
  ck_assert_int_eq(value.bits[1], test_value.bits[1]);
  ck_assert_int_eq(value.bits[2], test_value.bits[2]);
  ck_assert_int_eq(value.bits[3], test_value.bits[3]);
}
END_TEST

START_TEST(from_int_to_decimal_test_9) {
  s21_decimal value = {
      .bits[0] = 123321, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  s21_decimal test_value = {0};
  s21_from_int_to_decimal(123321, &test_value);
  ck_assert_int_eq(value.bits[0], test_value.bits[0]);
  ck_assert_int_eq(value.bits[1], test_value.bits[1]);
  ck_assert_int_eq(value.bits[2], test_value.bits[2]);
  ck_assert_int_eq(value.bits[3], test_value.bits[3]);
}
END_TEST

static void suite_add_from_int_to_decimal(Suite *s) {
  TCase *tc;
  tc = tcase_create("from_int_to_decimal");
  tcase_add_test(tc, from_int_to_decimal_test_1);
  tcase_add_test(tc, from_int_to_decimal_test_2);
  tcase_add_test(tc, from_int_to_decimal_test_3);
  tcase_add_test(tc, from_int_to_decimal_test_4);
  tcase_add_test(tc, from_int_to_decimal_test_5);
  tcase_add_test(tc, from_int_to_decimal_test_6);
  tcase_add_test(tc, from_int_to_decimal_test_7);
  tcase_add_test(tc, from_int_to_decimal_test_8);
  tcase_add_test(tc, from_int_to_decimal_test_9);
  suite_add_tcase(s, tc);
}
#define COUNT_ERROR_DECIMAL_TO_INT \
  sizeof(ERROR_DECIMAL_TO_INT) / sizeof(ERROR_DECIMAL_TO_INT[0])

#define ERROR_DECIMAL_TO_INT                                  \
  (s21_decimal[]) {                                           \
    {{0x00000010, 0x00000000, 0x00000000, 0x11111000}},       \
        {{0x00000010, 0x00000000, 0x00000000, 0x00001000}},   \
        {{0x00000010, 0x00000000, 0x00000000, 0x00000100}},   \
        {{0x00000010, 0x00000000, 0x00000000, 0x80001000}},   \
        {{0x00000010, 0x00000000, 0x00000000, 0x8001D000}},   \
        {{0x00000010, 0x00000000, 0x00000000, 0xFFFFFFFF}},   \
        {{0x00000000, 0x00000001, 0x00000000, 0x00000000}},   \
        {{0x00000000, 0x00000010, 0x00000000, 0x00000000}},   \
        {{0x00000000, 0x00000010, 0x00001000, 0x00000000}},   \
        {{0x00000000, 0x00000000, 0x00010000, 0x80010000}},   \
        {{0x00000000, 0x00000010, 0x00000000, 0x80000000}},   \
        {{0x80000000, 0x00000000, 0x00000000, 0x00000000}},   \
        {{0x80000001, 0x00000000, 0x00000000, 0x80000000}},   \
        {{0x00000010, 0x00000100, 0x00010000, 0x00001000}}, { \
      { 0x00000000, 0x00000000, 0x10000000, 0x80010000 }      \
    }                                                         \
  }

START_TEST(from_decimal_to_int_error_test) {
  s21_decimal *test_decimal_arr = ERROR_DECIMAL_TO_INT;
  int test_int = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(test_decimal_arr[_i], &test_int), 1);
}

#define COUNT_DECIMAL_TO_INT sizeof(DECIMAL_TO_INT) / sizeof(DECIMAL_TO_INT[0])

#define DECIMAL_TO_INT                                        \
  (s21_decimal[]) {                                           \
    {{0x00000010, 0x00000000, 0x00000000, 0x00010000}},       \
        {{0x00000011, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x00000012, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x00000013, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x00000014, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x00000015, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x00000016, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x000F0000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x000E0000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x000D0000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x000C0000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x000B0000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x000A0000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x00090000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x00080000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x00070000}},   \
        {{0x00000100, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x00001000, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x00010000, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x00100000, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x01000000, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x10000000, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x01000000, 0x00000000, 0x00000000, 0x00060000}},   \
        {{0x00100000, 0x00000000, 0x00000000, 0x00050000}},   \
        {{0x00010000, 0x00000000, 0x00000000, 0x00040000}},   \
        {{0x00001000, 0x00000000, 0x00000000, 0x00030000}},   \
        {{0x00000100, 0x00000000, 0x00000000, 0x00020000}},   \
        {{0x00000010, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x00020000}},   \
        {{0xAAAAAAAA, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0xBBBBBBBB, 0x00000000, 0x00000000, 0x00050000}},   \
        {{0x0012ACBD, 0x00000000, 0x00000000, 0x00090000}},   \
        {{0x0000ACAB, 0x00000000, 0x00000000, 0x00080000}},   \
        {{0x000BAC4A, 0x00000000, 0x00000000, 0x00030000}},   \
        {{0x1BACACAC, 0x00000000, 0x00000000, 0x00040000}},   \
        {{0xFEDCBA98, 0x00000000, 0x00000000, 0x00020000}},   \
        {{0x12345678, 0x00000000, 0x00000000, 0x00090000}},   \
        {{0x87654321, 0x00000000, 0x00000000, 0x00020000}},   \
        {{0x00000010, 0x00000000, 0x00000000, 0x80010000}},   \
        {{0x00000011, 0x00000000, 0x00000000, 0x80010000}},   \
        {{0x00000012, 0x00000000, 0x00000000, 0x80010000}},   \
        {{0x00000013, 0x00000000, 0x00000000, 0x80010000}},   \
        {{0x00000014, 0x00000000, 0x00000000, 0x80010000}},   \
        {{0x00000015, 0x00000000, 0x00000000, 0x80010000}},   \
        {{0x00000016, 0x00000000, 0x00000000, 0x80010000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x800F0000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x800E0000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x800D0000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x800C0000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x800B0000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x800A0000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x80090000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x80080000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x80070000}},   \
        {{0x00000100, 0x00000000, 0x00000000, 0x80010000}},   \
        {{0x00001000, 0x00000000, 0x00000000, 0x80010000}},   \
        {{0x00010000, 0x00000000, 0x00000000, 0x80010000}},   \
        {{0x00100000, 0x00000000, 0x00000000, 0x80010000}},   \
        {{0x01000000, 0x00000000, 0x00000000, 0x80010000}},   \
        {{0x10000000, 0x00000000, 0x00000000, 0x80010000}},   \
        {{0x01000000, 0x00000000, 0x00000000, 0x80060000}},   \
        {{0x00100000, 0x00000000, 0x00000000, 0x80050000}},   \
        {{0x00010000, 0x00000000, 0x00000000, 0x80040000}},   \
        {{0x00001000, 0x00000000, 0x00000000, 0x80030000}},   \
        {{0x00000100, 0x00000000, 0x00000000, 0x80020000}},   \
        {{0x00000010, 0x00000000, 0x00000000, 0x80010000}},   \
        {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},   \
        {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x80020000}},   \
        {{0xAAAAAAAA, 0x00000000, 0x00000000, 0x80010000}},   \
        {{0xBBBBBBBB, 0x00000000, 0x00000000, 0x80050000}},   \
        {{0x0012ACBD, 0x00000000, 0x00000000, 0x80090000}},   \
        {{0x0000ACAB, 0x00000000, 0x00000000, 0x80080000}},   \
        {{0x000BAC4A, 0x00000000, 0x00000000, 0x80030000}},   \
        {{0x1BACACAC, 0x00000000, 0x00000000, 0x80040000}},   \
        {{0xFEDCBA98, 0x00000000, 0x00000000, 0x80020000}},   \
        {{0x12345678, 0x00000000, 0x00000000, 0x80090000}},   \
        {{0x87654321, 0x00000000, 0x00000000, 0x80020000}},   \
        {{0x00000000, 0x00000000, 0x10000000, 0x801C0000}},   \
        {{0x00000000, 0x00000000, 0x00000010, 0x80100000}},   \
        {{0x00000000, 0x00000000, 0x00000101, 0x80100000}},   \
        {{0x00000000, 0x00000000, 0x00001101, 0x80100000}},   \
        {{0x00000000, 0x00000000, 0x00011101, 0x80120000}},   \
        {{0xFFFFFFFF, 0x11111111, 0x00AAAAAA, 0x80150000}},   \
        {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}}, { \
      { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000 }      \
    }                                                         \
  }

#define EXPECTED_INT                                                          \
  (int[]) {                                                                   \
    1, 1, 1, 1, 2, 2, 2, 0, 0, 0, 0, 0, 0, 4, 42, 429, 25, 409, 6553, 104857, \
        1677721, 26843545, 16, 10, 6, 4, 2, 1, 1, 42949672, 286331153, 31496, \
        0, 0, 765, 46430, 42758785, 0, 22715604, -1, -1, -1, -1, -2, -2, -2,  \
        0, 0, 0, 0, 0, 0, -4, -42, -429, -25, -409, -6553, -104857, -1677721, \
        -26843545, -16, -10, -6, -4, -2, -1, -1, -42949672, -286331153,       \
        -31496, 0, 0, -765, -46430, -42758785, 0, -22715604, 0, -29514,       \
        -474081, -8029867, -1289224, -206323, -7, -79                         \
  }

START_TEST(from_decimal_to_int) {
  s21_decimal *decimal_array = DECIMAL_TO_INT;
  int result, *int_array = EXPECTED_INT;
  s21_from_decimal_to_int(decimal_array[_i], &result);
  ck_assert_int_eq(int_array[_i], result);
}
END_TEST

static void suite_add_from_decimal_to_int(Suite *s) {
  TCase *tc;
  tc = tcase_create("from_decimal_to_int");
  tcase_add_loop_test(tc, from_decimal_to_int, 0, COUNT_DECIMAL_TO_INT);
  tcase_add_loop_test(tc, from_decimal_to_int_error_test, 0,
                      COUNT_ERROR_DECIMAL_TO_INT);
  suite_add_tcase(s, tc);
}

#define COUNT_FLOAT_TO_FLOAT \
  sizeof(FLOAT_TO_DECIMAL) / sizeof(FLOAT_TO_DECIMAL[0])

#define FLOAT_TO_DECIMAL                                                     \
  (float[]) {                                                                \
    1.2344567E-7F, 1.123, 0.000001231231F, 0.0F, -0.0F, -3.141592F, -9.01F,  \
        0.99999999F, 0.9999999F, -0.9999999F, 0.12321321312F,                \
        0.000000000000000000001F, -9.6666666666666666666F, 1.0e-28,          \
        -9.12345678e-12F, 0.000000000000000000000015678F, 7.77777777777F,    \
        123.123F, 1e+28, 314159265.0f, 1000.78f, 75.753e+10f, 0.0001e-10f,   \
        123.5f, 0.000000000000001f, 9999999e+20, 1.3e+20, 23456788.8766553f, \
        1000000000000000.0f, 3345.323f, 123.0000001f, 1.0, -1230.34f,        \
        -99999e+20f, -100.1250e-15, -100.1250e+15, -0.00001e+15,             \
        -9.991223456e+15, 1e-30, 1e-32, 1e-37                                \
  }

#define EXPECTED_DECIMAL                                      \
  (s21_decimal[]) {                                           \
    {{0x0012d619, 0x00000000, 0x00000000, 0x000d0000}},       \
        {{0x00000463, 0x00000000, 0x00000000, 0x00030000}},   \
        {{0x0012c97f, 0x00000000, 0x00000000, 0x000c0000}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x80000000}},   \
        {{0x002fefd8, 0x00000000, 0x00000000, 0x80060000}},   \
        {{0x00000385, 0x00000000, 0x00000000, 0x80020000}},   \
        {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},   \
        {{0x0098967f, 0x00000000, 0x00000000, 0x00070000}},   \
        {{0x0098967f, 0x00000000, 0x00000000, 0x80070000}},   \
        {{0x0012cd04, 0x00000000, 0x00000000, 0x00070000}},   \
        {{0x00000001, 0x00000000, 0x00000000, 0x00150000}},   \
        {{0x0093806b, 0x00000000, 0x00000000, 0x80060000}},   \
        {{0x00000001, 0x00000000, 0x00000000, 0x001c0000}},   \
        {{0x008b3681, 0x00000000, 0x00000000, 0x80120000}},   \
        {{0x00003d3e, 0x00000000, 0x00000000, 0x001b0000}},   \
        {{0x0076adf2, 0x00000000, 0x00000000, 0x00060000}},   \
        {{0x0001e0f3, 0x00000000, 0x00000000, 0x00030000}},   \
        {{0x31600000, 0x085b549b, 0x204fce28, 0x00000000}},   \
        {{0x12b9b0c4, 0x00000000, 0x00000000, 0x00000000}},   \
        {{0x000186ee, 0x00000000, 0x00000000, 0x00020000}},   \
        {{0x604e7a80, 0x000000b0, 0x00000000, 0x00000000}},   \
        {{0x00000001, 0x00000000, 0x00000000, 0x000e0000}},   \
        {{0x000004d3, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x00000001, 0x00000000, 0x00000000, 0x000f0000}},   \
        {{0x84f00000, 0x3409220f, 0x033b2e37, 0x00000000}},   \
        {{0x00c80000, 0x0c1cc73b, 0x00000007, 0x00000000}},   \
        {{0x0165ec16, 0x00000000, 0x00000000, 0x00000000}},   \
        {{0xa4c68000, 0x00038d7e, 0x00000000, 0x00000000}},   \
        {{0x00330bab, 0x00000000, 0x00000000, 0x00030000}},   \
        {{0x0000007b, 0x00000000, 0x00000000, 0x00000000}},   \
        {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},   \
        {{0x0001e09a, 0x00000000, 0x00000000, 0x80020000}},   \
        {{0xe6f00000, 0xaa4ca31a, 0x0008458f, 0x80000000}},   \
        {{0x0001871d, 0x00000000, 0x00000000, 0x80120000}},   \
        {{0x3222d000, 0x0163b728, 0x00000000, 0x80000000}},   \
        {{0x540be400, 0x00000002, 0x00000000, 0x80000000}},   \
        {{0x1d643000, 0x00237ef7, 0x00000000, 0x80000000}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x00000000}}, { \
      { 0x00000000, 0x00000000, 0x00000000, 0x00000000 }      \
    }                                                         \
  }

START_TEST(from_float_to_decimal) {
  float *first_array = FLOAT_TO_DECIMAL;
  s21_decimal *expected_array = EXPECTED_DECIMAL, res;
  s21_from_float_to_decimal(first_array[_i], &res);
  ck_assert_mem_eq(&res, &expected_array[_i], sizeof(s21_decimal));
}
END_TEST

#define COUNT_ERROR_CONVERTATION_FLOAT_TO_DECIMAL \
  sizeof(ERROR_CONVERTATION_FLOAT_TO_DECIMAL) /   \
      sizeof(ERROR_CONVERTATION_FLOAT_TO_DECIMAL[0])

#define ERROR_CONVERTATION_FLOAT_TO_DECIMAL                                    \
  (float[]) {                                                                  \
    1e-30, 0.432e-29, 3.1415e+30, 1e+29, 0.000000000000000000000000000015678,  \
        1e+37, -2e-30, -3.3e-30, 3e+30, 9.9999999e+28f, 8e+28f, 9.999999e+28f, \
        INFINITY, -INFINITY, NAN, -NAN                                         \
  }

START_TEST(error_from_float_to_decimal) {
  float *first_array = ERROR_CONVERTATION_FLOAT_TO_DECIMAL;
  s21_decimal res;
  ck_assert_int_eq(s21_from_float_to_decimal(first_array[_i], &res), 1);
}
END_TEST

static void suite_add_from_float_to_decimal(Suite *s) {
  TCase *tc;
  tc = tcase_create("from_float_to_decimal");
  tcase_add_loop_test(tc, from_float_to_decimal, 0, COUNT_FLOAT_TO_FLOAT);
  tcase_add_loop_test(tc, error_from_float_to_decimal, 0,
                      COUNT_ERROR_CONVERTATION_FLOAT_TO_DECIMAL);
  suite_add_tcase(s, tc);
}

#define COUNT_TESTS_DECIMAL_TO_FLOAT \
  sizeof(EXPECTED_FLOAT) / sizeof(EXPECTED_FLOAT[0])

#define DECIMAL_TO_FLOAT                                      \
  (s21_decimal[]) {                                           \
    {{0x00000001, 0x00000000, 0x00000000, 0x00010000}},       \
        {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x80000000}},   \
        {{0x00000001, 0x00000000, 0x00000000, 0x80040000}},   \
        {{0x00000000, 0x00000001, 0x00000000, 0x00010000}},   \
        {{0x00000000, 0x00000213, 0x00000000, 0x80050000}},   \
        {{0xffffffff, 0x00000000, 0x00000000, 0x80080000}},   \
        {{0xabcdef00, 0x00000888, 0x00000000, 0x800c0000}},   \
        {{0x00000000, 0xfffffff0, 0x00000000, 0x00000000}},   \
        {{0x00000000, 0x00000000, 0x00000001, 0x000f0000}},   \
        {{0x00000000, 0x00000000, 0xffffffff, 0x800f0000}},   \
        {{0xffffffff, 0xffffffff, 0xffffffff, 0x001c0000}},   \
        {{0x00000001, 0x00000000, 0x00000000, 0x000f0000}},   \
        {{0x12345678, 0x12345678, 0x12345678, 0x001c0000}},   \
        {{0x000009d5, 0x00000000, 0x00000000, 0x80050000}},   \
        {{0x0000000a, 0x00000000, 0x00000000, 0x801c0000}},   \
        {{0x0000000a, 0x00000000, 0x00000000, 0x801c0000}}, { \
      { 0x00000000, 0x00000000, 0x00000000, 0x00000000 }      \
    }                                                         \
  }

#define EXPECTED_FLOAT                                                    \
  (float[]) {                                                             \
    0.1, 0.0, -0.0, -0.0001, 4294967.0, -2280627.0, -42.94967, -9.383090, \
        1844674.0, 18446.74, -7922816.0, 7.922816, 0.000000000000001,     \
        0.5634002, -0.02517, -0.0000000000000000000000000010              \
  }

START_TEST(from_decimal_to_float_test) {
  s21_decimal *first_array = DECIMAL_TO_FLOAT;
  float *expected_array = EXPECTED_FLOAT, res;
  s21_from_decimal_to_float(first_array[_i], &res);
  ck_assert_float_eq(expected_array[_i], res);
}
END_TEST

#define COUNT_DECIMAL_TO_FLOAT_ERROR \
  sizeof(DECIMAL_TO_FLOAT_ERROR) / sizeof(DECIMAL_TO_FLOAT_ERROR[0])
#define DECIMAL_TO_FLOAT_ERROR                            \
  (s21_decimal[]) {                                       \
    {{0x00000001, 0x00000001, 0x00000001, 0x001f0000}}, { \
      { 0x00000001, 0x00000001, 0x00000001, 0x801f0000 }  \
    }                                                     \
  }

START_TEST(from_decimal_to_float_test_error) {
  s21_decimal *first_array = DECIMAL_TO_FLOAT_ERROR;
  float res;
  int status = s21_from_decimal_to_float(first_array[_i], &res);
  ck_assert_int_eq(status, 1);
}

static void suite_add_from_decimal_to_float(Suite *s) {
  TCase *tc;
  tc = tcase_create("from_decimal_to_float");
  tcase_add_loop_test(tc, from_decimal_to_float_test, 0,
                      COUNT_TESTS_DECIMAL_TO_FLOAT);
  tcase_add_loop_test(tc, from_decimal_to_float_test_error, 0,
                      COUNT_DECIMAL_TO_FLOAT_ERROR);
  suite_add_tcase(s, tc);
}

void suite_add_convert(Suite *s) {
  suite_add_from_int_to_decimal(s);
  suite_add_from_float_to_decimal(s);
  suite_add_from_decimal_to_int(s);
  suite_add_from_decimal_to_float(s);
}
