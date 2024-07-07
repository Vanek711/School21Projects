#include "../arithmetic.h"

#include "arithmetic.h"

START_TEST(s21_negate_test_1) {
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal value[] = {{{0x3130f321, 0x309aecd9, 0x318bb402, 0x80000000}},
                         {{0xc7fdcb64, 0x693934ee, 0x4d7ed236, 0x00000000}},
                         {{0x16f7fd50, 0x1c35a5d8, 0x430311ac, 0x80010000}},
                         {{0x5da05570, 0x7db3c416, 0x07f06022, 0x800f0000}},
                         {{0x50f8e2c0, 0x39211057, 0x68d3cdab, 0x801c0000}}};
  s21_decimal test[] = {{{0x3130f321, 0x309aecd9, 0x318bb402, 0x00000000}},
                        {{0xc7fdcb64, 0x693934ee, 0x4d7ed236, 0x80000000}},
                        {{0x16f7fd50, 0x1c35a5d8, 0x430311ac, 0x00010000}},
                        {{0x5da05570, 0x7db3c416, 0x07f06022, 0x000f0000}},
                        {{0x50f8e2c0, 0x39211057, 0x68d3cdab, 0x001c0000}}};
  s21_negate(value[_i], &res);
  ck_assert_mem_eq(&res, &test[_i], sizeof(s21_decimal));
}
END_TEST

START_TEST(s21_negate_test_2) {
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal value[] = {{{0x677dd11a, 0xd0139731, 0xdf64a92c, 0x80130000}},
                         {{0xf1c89997, 0x4fc157dd, 0x4d80957d, 0x000f0000}},
                         {{0xf981f909, 0x19463ad1, 0xe887f890, 0x800c0000}},
                         {{0x74818d28, 0xe6ff4bf8, 0xda98d4d4, 0x80000000}}};
  s21_decimal test[] = {{{0x677dd11a, 0xd0139731, 0xdf64a92c, 0x00130000}},
                        {{0xf1c89997, 0x4fc157dd, 0x4d80957d, 0x800f0000}},
                        {{0xf981f909, 0x19463ad1, 0xe887f890, 0x000c0000}},
                        {{0x74818d28, 0xe6ff4bf8, 0xda98d4d4, 0x00000000}}};
  s21_negate(value[_i], &res);
  ck_assert_mem_eq(&res, &test[_i], sizeof(s21_decimal));
}
END_TEST

#define COUNT_ADD_COMMON_TEST sizeof(FIRST_ADD) / sizeof(FIRST_ADD[0])

#define FIRST_ADD                                             \
  (s21_decimal[]) {                                           \
    {{0x00000000, 0x00000001, 0x00000002, 0x00020000}},       \
        {{0x00000030, 0x00030000, 0xf0000000, 0x00050000}},   \
        {{0x00000001, 0xffffffff, 0x00000000, 0x80050000}},   \
        {{0xfff1b10a, 0x000fbbaa, 0x00000000, 0x800a0000}},   \
        {{0xffffffff, 0xa00fbbaa, 0x00000000, 0x800a0000}},   \
        {{0x21303500, 0xf0f00000, 0x10000000, 0x00060000}},   \
        {{0x20202020, 0x0ab45678, 0x00002000, 0x00090000}},   \
        {{0xabcabc00, 0x0300f000, 0x00013000, 0x80030000}},   \
        {{0x000000aa, 0x10020030, 0x00000000, 0x00030000}}, { \
      { 0xffffffff, 0xffffffff, 0xffffffff, 0x00060000 }      \
    }                                                         \
  }

#define SECOND_ADD                                            \
  (s21_decimal[]) {                                           \
    {{0x00000000, 0x00000003, 0x00000003, 0x00040000}},       \
        {{0x0000232a, 0x00003200, 0x00000000, 0x00030000}},   \
        {{0x0000232a, 0xffffffff, 0x00000000, 0x80030000}},   \
        {{0xa3745455, 0xf0000fff, 0x10931a0a, 0x800b0000}},   \
        {{0xaaaaaaa0, 0x00000fff, 0x00000000, 0x800b0000}},   \
        {{0x000abcde, 0x0454a000, 0x02300000, 0x00030000}},   \
        {{0x01010101, 0x00000000, 0x00100000, 0x00040000}},   \
        {{0x000d0000, 0x0000d000, 0x00000000, 0x00040000}},   \
        {{0x00000000, 0xffffffff, 0x00000000, 0x00040000}}, { \
      { 0xffffffff, 0xffffffff, 0xffffffff, 0x00040000 }      \
    }                                                         \
  }

#define SUM                                                   \
  (s21_decimal[]) {                                           \
    {{0x00000000, 0x00000067, 0x000000cb, 0x00040000}},       \
        {{0x000dbc98, 0x00168800, 0xf0000000, 0x00050000}},   \
        {{0x000dbc69, 0xffffff9b, 0x00000064, 0x80050000}},   \
        {{0xa2e53eb9, 0xf09d64ad, 0x10931a0a, 0x800b0000}},   \
        {{0xaaaaaa96, 0x409d64ad, 0x00000006, 0x800b0000}},   \
        {{0xa11cff38, 0x62c01999, 0xdc59999b, 0x00050000}},   \
        {{0x00b90af3, 0xeba08600, 0x3e800051, 0x00070000}},   \
        {{0xb5f85800, 0x1e0a3006, 0x000be000, 0x80040000}},   \
        {{0x000006a4, 0xa01401df, 0x00000001, 0x00040000}}, { \
      { 0x374bc6a8, 0xe5604189, 0x19db22d0, 0x00030000 }      \
    }                                                         \
  }

START_TEST(s21_common_add) {
  s21_decimal *first_array = FIRST_ADD, *second_array = SECOND_ADD,
              *expected_array = SUM, res;
  s21_add(first_array[_i], second_array[_i], &res);
  ck_assert_mem_eq(&expected_array[_i], &res, sizeof(s21_decimal));
}
END_TEST

#define COUNT_OVERFLOW_TEST sizeof(FIRST_OVERFLOW) / sizeof(FIRST_OVERFLOW[0])

#define FIRST_OVERFLOW                                        \
  (s21_decimal[]) {                                           \
    {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}},       \
        {{0xffffffff, 0xffffffff, 0xaaaa0000, 0x00000000}},   \
        {{0xffffffff, 0xffffffff, 0x00000001, 0x00000000}}, { \
      { 0x00000000, 0x00000000, 0xffff0000, 0x00000000 }      \
    }                                                         \
  }

#define SECOND_OVERFLOW                                       \
  (s21_decimal[]) {                                           \
    {{0xffffffff, 0xffffffff, 0xffffffff, 0x00010000}},       \
        {{0xffffffff, 0xffffffff, 0xf0000000, 0x00000000}},   \
        {{0x00000000, 0x00000000, 0xffffffff, 0x00000000}}, { \
      { 0x00000000, 0xfffffff, 0xfffff000, 0x00000000 }       \
    }                                                         \
  }

#define COUNT_SUB_COMMON_TEST sizeof(FIRST_SUB) / sizeof(FIRST_SUB[0])

#define FIRST_SUB                                             \
  (s21_decimal[]) {                                           \
    {{0x00000010, 0x000f0000, 0x00000000, 0x00000000}},       \
        {{0x00000010, 0x000f0000, 0x0fffffff, 0x00030000}},   \
        {{0x0abcdef1, 0x01010101, 0x00202002, 0x00090000}},   \
        {{0x01234567, 0x00003456, 0x000000ab, 0x000f0000}},   \
        {{0xffff1233, 0x000a00d0, 0x000aaa00, 0x80040000}},   \
        {{0xffffffff, 0xffffffff, 0xffffffff, 0x00090000}},   \
        {{0xffffffff, 0xffffffff, 0xffffffff, 0x00090000}},   \
        {{0x20202020, 0x30303030, 0x40404040, 0x00120000}},   \
        {{0x00000001, 0x00000000, 0x00000000, 0x00020000}},   \
        {{0x12345678, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x12345678, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x12345678, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x77777777, 0x0010a020, 0x12901000, 0x80050000}},   \
        {{0x77777777, 0xffffffff, 0x12901000, 0x000f0000}},   \
        {{0xa37277a7, 0xffffffff, 0x12901aaa, 0x00040000}},   \
        {{0xfff1b10a, 0x000fbbaa, 0x00000000, 0x80050000}},   \
        {{0x12345678, 0x00230000, 0x000cf000, 0x00080000}},   \
        {{0x58693756, 0xcf000000, 0x00000000, 0x00050000}},   \
        {{0xabc12345, 0x00230000, 0x0ca00000, 0x80050000}},   \
        {{0xabc12345, 0x00235600, 0xfca00000, 0x80030000}},   \
        {{0x000000aa, 0x10020030, 0x00000000, 0x00030000}},   \
        {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}},   \
        {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}},   \
        {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}}, { \
      { 0x12345678, 0xffabffff, 0xf0000000, 0x00050000 }      \
    }                                                         \
  }

#define SECOND_SUB                                            \
  (s21_decimal[]) {                                           \
    {{0x00000001, 0x00000123, 0x00000000, 0x00000000}},       \
        {{0xffffffff, 0x10000123, 0x000abcde, 0x00090000}},   \
        {{0x01234567, 0x00003456, 0x000000ab, 0x000f0000}},   \
        {{0x0abcdef1, 0x01010101, 0x00202002, 0x80090000}},   \
        {{0x10a0a000, 0x00000000, 0xf0000000, 0x00090000}},   \
        {{0x00000000, 0xffffffff, 0x00000000, 0x000a0000}},   \
        {{0x00000000, 0xffffffff, 0x00000000, 0x800a0000}},   \
        {{0x50505050, 0x70707070, 0x80808080, 0x80150000}},   \
        {{0x00000001, 0x00000000, 0x00000000, 0x000a0000}},   \
        {{0x99999999, 0x00000000, 0x00000000, 0x000c0000}},   \
        {{0xffffffff, 0x00000000, 0x00000000, 0x001a0000}},   \
        {{0xffffffff, 0x00000000, 0x00000000, 0x801a0000}},   \
        {{0xfff0b00a, 0xa0220f00, 0xaaa10000, 0x00050000}},   \
        {{0xfff0b00a, 0xffffffff, 0xaaa10000, 0x801a0000}},   \
        {{0xfff1b00a, 0xffffbbaa, 0xaaa10000, 0x00090000}},   \
        {{0xa3745455, 0xf0000fff, 0x10931a0a, 0x80040000}},   \
        {{0xffffffff, 0x00007000, 0x00f00000, 0x000f0000}},   \
        {{0xffffffff, 0xcdbb2000, 0x00000000, 0x80060000}},   \
        {{0xffffffff, 0xcdbb2000, 0xfffffffa, 0x80060000}},   \
        {{0xffffffff, 0xcdbb2000, 0xfff00000, 0x00020000}},   \
        {{0x00000000, 0xffffffff, 0x00000000, 0x00040000}},   \
        {{0x0000000f, 0x00000000, 0x00000000, 0x00020000}},   \
        {{0x00000009, 0x00000000, 0x00000000, 0x00010000}},   \
        {{0x00000006, 0x00000000, 0x00000000, 0x00010000}}, { \
      { 0x00000006, 0x000cffff, 0xfffd0000, 0x00050000 }      \
    }                                                         \
  }

#define SUB                                                   \
  (s21_decimal[]) {                                           \
    {{0x0000000f, 0x000efedd, 0x00000000, 0x00000000}},       \
        {{0xf5fedb06, 0xf71692cc, 0x9fffffee, 0x00040000}},   \
        {{0xee3111d1, 0xc0254414, 0x7d7d07d3, 0x000c0000}},   \
        {{0xf55ca8ff, 0x17b2940e, 0x7d7d07d4, 0x000c0000}},   \
        {{0x62f00e94, 0x8d7996ce, 0x2c0e7666, 0x80070000}},   \
        {{0x7fffffff, 0xe6666666, 0xffffffff, 0x00090000}},   \
        {{0x8ccccccd, 0x9c28f5c2, 0x19999999, 0x00080000}},   \
        {{0x2034af91, 0x573671d6, 0x406125c1, 0x00120000}},   \
        {{0x05f5e0ff, 0x00000000, 0x00000000, 0x000a0000}},   \
        {{0x70132667, 0xa7daf1b8, 0x00000001, 0x000c0000}},   \
        {{0xcf7f583a, 0xd146a3cd, 0x62afbddd, 0x00150000}},   \
        {{0xcf80a7c6, 0xd146a3cd, 0x62afbddd, 0x00150000}},   \
        {{0x77682781, 0xa032af21, 0xbd311000, 0x80050000}},   \
        {{0xddb0db4f, 0x4948d8b8, 0xb9a0a00a, 0x00100000}},   \
        {{0xee45e28c, 0x32c3c9ec, 0xb99cac72, 0x00050000}},   \
        {{0x62999a48, 0x5ff0e451, 0xa5bf046d, 0x00050000}},   \
        {{0x7ff39c9c, 0xab88e5a4, 0x328979db, 0x000b0000}},   \
        {{0x741c295b, 0xe3bb2004, 0x00000008, 0x00060000}},   \
        {{0x4a749f4d, 0xcc5d1ffa, 0x81bffffa, 0x00060000}},   \
        {{0x96329246, 0x00182f94, 0x1c1eb852, 0x80010000}},   \
        {{0xfffff95c, 0x5febfe1e, 0x00000000, 0x80040000}},   \
        {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}},   \
        {{0xfffffffe, 0xffffffff, 0xffffffff, 0x00000000}},   \
        {{0xfffffffe, 0xffffffff, 0xffffffff, 0x00000000}}, { \
      { 0xedcba98e, 0x0060ffff, 0x0ffcffff, 0x80050000 }      \
    }                                                         \
  }

START_TEST(s21_overflow_add) {
  s21_decimal *first_array = FIRST_OVERFLOW, *second_array = SECOND_OVERFLOW,
              res;
  ck_assert_int_eq(s21_add(first_array[_i], second_array[_i], &res),
                   s21_overflow);
}
END_TEST

static void suite_add_s21_add(Suite *s) {
  TCase *tc;
  tc = tcase_create("s21_add");
  tcase_add_loop_test(tc, s21_common_add, 0, COUNT_ADD_COMMON_TEST);
  tcase_add_loop_test(tc, s21_overflow_add, 0, COUNT_OVERFLOW_TEST);
  suite_add_tcase(s, tc);
}

START_TEST(s21_common_sub) {
  s21_decimal *first_array = FIRST_SUB, *second_array = SECOND_SUB,
              *expected_array = SUB, res;
  s21_sub(first_array[_i], second_array[_i], &res);
  for (int j = 0; j < 4; j++)
    ck_assert_int_eq(expected_array[_i].bits[j], res.bits[j]);
}
END_TEST

static void suite_add_s21_sub(Suite *s) {
  TCase *tc;
  tc = tcase_create("s21_sub");
  tcase_add_loop_test(tc, s21_common_sub, 0, COUNT_SUB_COMMON_TEST);
  suite_add_tcase(s, tc);
}

#define S21_MUL_NTESTS 17

#define S21_MUL_INPUT_A                                       \
  {                                                           \
    {{0x12349455, 0x12312221, 0x23437847, 0x001a0000}},       \
        {{0x92394934, 0x29348234, 0x92342834, 0x80110000}},   \
        {{0x23443374, 0x54364322, 0x84583452, 0x801c0000}},   \
        {{0x75346532, 0x72934723, 0x32642346, 0x000e0000}},   \
        {{0x33342344, 0x34759239, 0x94854575, 0x00030000}},   \
        {{0x62456345, 0x62346234, 0x24323455, 0x80150000}},   \
        {{0x00000003, 0x00000000, 0x00000000, 0x80000000}},   \
        {{0xffffffff, 0x00000000, 0x00000000, 0x00000000}},   \
        {{0x00004453, 0x00000000, 0x00000000, 0x80000000}},   \
        {{0x99452344, 0x00008234, 0x00000000, 0x00000000}},   \
        {{0x23487453, 0x00004354, 0x00000000, 0x00030000}},   \
        {{0xffffffff, 0xffffffff, 0xffffffff, 0x801a0000}},   \
        {{0xffffffff, 0x00000000, 0x00000000, 0x00190000}},   \
        {{0xffffffff, 0xffffffff, 0xffffffff, 0x801c0000}},   \
        {{0x28add82d, 0x82bab558, 0xdcca33e2, 0x00190000}},   \
        {{0xaabcc232, 0xa234ba28, 0xf234f2aa, 0x00040000}}, { \
      { 0x00234aab, 0x00000000, 0x00000000, 0x801c0000 }      \
    }                                                         \
  }

#define S21_MUL_INPUT_B                                       \
  {                                                           \
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},       \
        {{0x00000000, 0x00000000, 0x00000000, 0x801b0000}},   \
        {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},   \
        {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},   \
        {{0x00000001, 0x00000000, 0x00000000, 0x00050000}},   \
        {{0x00000001, 0x00000000, 0x00000000, 0x80030000}},   \
        {{0x00000324, 0x00000000, 0x00000000, 0x80000000}},   \
        {{0xffffffff, 0x00000000, 0x00000000, 0x00000000}},   \
        {{0x34957435, 0x94753454, 0x00000043, 0x00000000}},   \
        {{0x39457343, 0x00000053, 0x00000000, 0x00000000}},   \
        {{0x72743248, 0x00000632, 0x00000000, 0x80050000}},   \
        {{0xffffffff, 0x00000000, 0x00000000, 0x00190000}},   \
        {{0xffffffff, 0xffffffff, 0xffffffff, 0x801a0000}},   \
        {{0xffffffff, 0xffffffff, 0xffffffff, 0x801c0000}},   \
        {{0xaedd23fd, 0xff232558, 0x28b82b52, 0x00180000}},   \
        {{0x27f7f3af, 0xbb8347a4, 0xaa2348ac, 0x00070000}}, { \
      { 0x0008abff, 0x00000000, 0x00000000, 0x001b0000 }      \
    }                                                         \
  }

#define S21_MUL_OUTPUT                                        \
  {                                                           \
    {{0x00000000, 0x00000000, 0x00000000, 0x001a0000}},       \
        {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},   \
        {{0x23443374, 0x54364322, 0x84583452, 0x801c0000}},   \
        {{0x75346532, 0x72934723, 0x32642346, 0x800e0000}},   \
        {{0x33342344, 0x34759239, 0x94854575, 0x00080000}},   \
        {{0x62456345, 0x62346234, 0x24323455, 0x00180000}},   \
        {{0x0000096c, 0x00000000, 0x00000000, 0x00000000}},   \
        {{0x00000001, 0xfffffffe, 0x00000000, 0x00000000}},   \
        {{0xbf52c12f, 0x43e65544, 0x00120958, 0x80000000}},   \
        {{0xd143c6cc, 0xba57d826, 0x002a542e, 0x00000000}},   \
        {{0xbeb4ed58, 0x9df04965, 0x01a13d5c, 0x80080000}},   \
        {{0x9ffd424f, 0x000c16d9, 0x00000000, 0x801c0000}},   \
        {{0x9ffd424f, 0x000c16d9, 0x00000000, 0x801c0000}},   \
        {{0x096ee456, 0x359a3b3e, 0xcad2f7f5, 0x001b0000}},   \
        {{0x984c0047, 0x9fed2d33, 0x1bd2f469, 0x00140000}},   \
        {{0x00000000, 0x00000000, 0x00000000, 0x00000000}}, { \
      { 0x00000000, 0x00000000, 0x00000000, 0x00000000 }      \
    }                                                         \
  }

#define S21_MUL_RETURN_CODE                                              \
  {                                                                      \
    s21_success, s21_success, s21_success, s21_success, s21_success,     \
        s21_success, s21_success, s21_success, s21_success, s21_success, \
        s21_success, s21_success, s21_success, s21_success, s21_success, \
        s21_overflow, s21_underflow                                      \
  }

START_TEST(check_s21_mul) {
  static s21_decimal a[S21_MUL_NTESTS] = S21_MUL_INPUT_A;
  static s21_decimal b[S21_MUL_NTESTS] = S21_MUL_INPUT_B;
  static s21_decimal output[S21_MUL_NTESTS] = S21_MUL_OUTPUT;
  static int code[S21_MUL_NTESTS] = S21_MUL_RETURN_CODE;
  int ret;
  s21_decimal res;

  ret = s21_mul(a[_i], b[_i], &res);
  ck_assert_int_eq(ret, code[_i]);
  if (code[_i] == s21_success) {
    ck_assert_mem_eq(&res, output + _i, sizeof(output[_i]));
  }
}
END_TEST

#undef S21_MUL_INPUT_A
#undef S21_MUL_INPUT_B
#undef S21_MUL_OUTPUT
#undef S21_MUL_RETURN_CODE

static void suite_add_s21_mul(Suite *s) {
  TCase *tc;
  tc = tcase_create("s21_mul");
  tcase_add_loop_test(tc, check_s21_mul, 0, S21_MUL_NTESTS);
  suite_add_tcase(s, tc);
}

#define S21_DIV_NTESTS 9

#define S21_DIV_INPUT_A                                     \
  {                                                         \
    {{0x23423aab, 0xbbc33242, 0x0234441f, 0x00000000}},     \
        {{0x45abacae, 0x28348acd, 0x238432ff, 0x80000000}}, \
        {{0xa28dd8c7, 0x2938d8d8, 0x123faad8, 0x00000000}}, \
        {{0x00000001, 0x00000000, 0x00000000, 0x00000000}}, \
        {{0x00000002, 0x00000000, 0x00000000, 0x00000000}}, \
        {{0x00000000, 0x00000001, 0x00000000, 0x00000000}}, \
        {{0x2843bb88, 0x82382455, 0x28348512, 0x00030000}}, \
        {{0xf7d7aca3, 0xaa82384a, 0x238abba9, 0x801a0000}}, \
        {{0x2463eaa1, 0x923478ac, 0xf8a8f32e, 0x80030000}}, \
  }

#define S21_DIV_INPUT_B                                     \
  {                                                         \
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},     \
        {{0x00000002, 0x00000000, 0x00000000, 0x00000000}}, \
        {{0x00000002, 0x00000000, 0x00000000, 0x80000000}}, \
        {{0x00000003, 0x00000000, 0x00000000, 0x00000000}}, \
        {{0x00000003, 0x00000000, 0x00000000, 0x00000000}}, \
        {{0x00000000, 0x00000001, 0x00000000, 0x00000000}}, \
        {{0x82752355, 0xfca8a0dc, 0x23750309, 0x00050000}}, \
        {{0x00000000, 0x00000000, 0x00000000, 0x80190000}}, \
        {{0x00000007, 0x00000000, 0x00000000, 0x001b0000}}, \
  }

#define S21_DIV_OUTPUT                                      \
  {                                                         \
    {{0xc5deeacc, 0x583fa1d5, 0xdc6a9c65, 0x00020000}},     \
        {{0x5c5a5f66, 0xc906b602, 0xb194fefb, 0x80010000}}, \
        {{0x2cc53be3, 0xce1c3c3b, 0x5b3e5638, 0x80010000}}, \
        {{0x05555555, 0x14b700cb, 0x0ac544ca, 0x001c0000}}, \
        {{0x0aaaaaaa, 0x296e0196, 0x158a8994, 0x001c0000}}, \
        {{0x10000000, 0x3e250261, 0x204fce5e, 0x001c0000}}, \
        {{0x0b08dee9, 0x350499a3, 0x24a37d0e, 0x001a0000}}, \
        {{0x00000000, 0x00000000, 0x00000000, 0x00000000}}, \
        {{0x00000000, 0x00000000, 0x00000000, 0x00000000}}, \
  }

#define S21_DIV_RETURN_CODE                                          \
  {                                                                  \
    s21_success, s21_success, s21_success, s21_success, s21_success, \
        s21_success, s21_success, s21_division_by_0, s21_overflow,   \
  }

START_TEST(check_s21_div) {
  static s21_decimal a[S21_DIV_NTESTS] = S21_DIV_INPUT_A;
  static s21_decimal b[S21_DIV_NTESTS] = S21_DIV_INPUT_B;
  static s21_decimal output[S21_DIV_NTESTS] = S21_DIV_OUTPUT;
  static int code[S21_DIV_NTESTS] = S21_DIV_RETURN_CODE;
  int ret;
  s21_decimal res;

  ret = s21_div(a[_i], b[_i], &res);
  ck_assert_int_eq(ret, code[_i]);
  if (code[_i] == s21_success) {
    ck_assert_mem_eq(&res, output + _i, sizeof(output[_i]));
  }
}
END_TEST

#undef S21_DIV_INPUT_A
#undef S21_DIV_INPUT_B
#undef S21_DIV_OUTPUT
#undef S21_DIV_RETURN_CODE

static void suite_add_s21_div(Suite *s) {
  TCase *tc;
  tc = tcase_create("s21_div");
  tcase_add_loop_test(tc, check_s21_div, 0, S21_DIV_NTESTS);
  suite_add_tcase(s, tc);
}

static void suite_add_s21_negate(Suite *s) {
  TCase *tc;
  tc = tcase_create("s21_negate");
  tcase_add_loop_test(tc, s21_negate_test_1, 0, 4);
  tcase_add_loop_test(tc, s21_negate_test_2, 0, 3);
  suite_add_tcase(s, tc);
}

void suite_add_arithmetic(Suite *s) {
  suite_add_s21_add(s);
  suite_add_s21_sub(s);
  suite_add_s21_mul(s);
  suite_add_s21_div(s);
  suite_add_s21_negate(s);
}
