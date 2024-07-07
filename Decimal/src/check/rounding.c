#include "../rounding.h"

#include "rounding.h"

/***************************************************************/
/*                                                             */
/*                        FLOOR TESTS                          */
/*                                                             */
/***************************************************************/
/*                        POSITIVE TESTS                       */
/***************************************************************/

// 30 * 10^(0xFFFFFFFF) = 3 * 10^(0) XXX 10
START_TEST(s21_floor_test_1) {
  s21_decimal test_value = {.bits[0] = 0x0000001E,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x00000003,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  for (int i = 30; i < 40; i++) {
    test_value.bits[0] = i;
    s21_floor(test_value, &returned_value);
    ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
  }
}
END_TEST

// 322 *10^(-2) = 3 * 10^(0)
START_TEST(s21_floor_test_2) {
  s21_decimal test_value = {.bits[0] = 0x00000142,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00020000};
  s21_decimal set_value = {.bits[0] = 0x00000003,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 322 * 10^(-3) = 0 * 10^(0)
START_TEST(s21_floor_test_3) {
  s21_decimal test_value = {.bits[0] = 0x00000142,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00030000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 2*(31) * 10 ^ (-28) = 0
START_TEST(s21_floor_test_4) {
  s21_decimal test_value = {.bits[0] = 0x7FFFFFFF,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x001C0000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 2*(96) * 10 ^ (-28) = 7
START_TEST(s21_floor_test_5) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x001C0000};
  s21_decimal set_value = {.bits[0] = 0x00000007,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2^(96) - 1) * 10^(-28)
START_TEST(s21_floor_test_6) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x7FFFFFFF,
                            .bits[3] = 0x001C0000};
  s21_decimal set_value = {.bits[0] = 0x00000003,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 2^(33) * 10^(-9) = 8  ||  2**33 / 10 ** 9 = 8.589934592
START_TEST(s21_floor_test_7) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000001,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00090000};
  s21_decimal set_value = {.bits[0] = 0x00000004,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 2^(34) * 10^(-9) = 17  ||  2**34 / 10 ** 9 = 17.179869184
START_TEST(s21_floor_test_8) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000002,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00090000};
  s21_decimal set_value = {.bits[0] = 0x00000008,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2^(34) + 2^(35)) * 10^(-9) = 51  ||  (2**34+2**35) / 10 ** 9 = 51.539607552
START_TEST(s21_floor_test_9) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x0000000C,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00090000};
  s21_decimal set_value = {.bits[0] = 0x00000033,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 0 = 79 228 162 514 264 337 593 543 950 335
START_TEST(s21_floor_test_10) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00000000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFF,
                           .bits[1] = 0xFFFFFFFF,
                           .bits[2] = 0xFFFFFFFF,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 1 = 7 922 816 251 426 433 759 354 395 033
START_TEST(s21_floor_test_11) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x99999999,
                           .bits[1] = 0x99999999,
                           .bits[2] = 0x19999999,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 2 = 792 281 625 142 643 375 935 439 503
START_TEST(s21_floor_test_12) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00020000};
  s21_decimal set_value = {.bits[0] = 0x28F5C28F,
                           .bits[1] = 0xF5C28F5C,
                           .bits[2] = 0x028F5C28,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 3 = 79 228 162 514 264 337 593 543 950
START_TEST(s21_floor_test_13) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00030000};
  s21_decimal set_value = {.bits[0] = 0x9db22d0e,
                           .bits[1] = 0x4bc6a7ef,
                           .bits[2] = 0x00418937,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 4 = 7 922 816 251 426 433 759 354 395
START_TEST(s21_floor_test_14) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00040000};
  s21_decimal set_value = {.bits[0] = 0x295E9E1B,
                           .bits[1] = 0xBAC710CB,
                           .bits[2] = 0x00068DB8,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 9 = 79 228 162 514 264 337 593
START_TEST(s21_floor_test_15) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00090000};
  s21_decimal set_value = {.bits[0] = 0xB5A52CB9,
                           .bits[1] = 0x4B82FA09,
                           .bits[2] = 0x00000004,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 10 = 7 922 816 251 426 433 759
START_TEST(s21_floor_test_16) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x000A0000};
  s21_decimal set_value = {.bits[0] = 0x5EF6EADF,
                           .bits[1] = 0x6DF37F67,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 11 = 792 281 625 142 643 375
START_TEST(s21_floor_test_17) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x000B0000};
  s21_decimal set_value = {.bits[0] = 0xBCB24AAF,
                           .bits[1] = 0x0AFEBFF0,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 12 = 79 228 162 514 264 337
START_TEST(s21_floor_test_18) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x000C0000};
  s21_decimal set_value = {.bits[0] = 0x12DEA111,
                           .bits[1] = 0x01197998,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 18 = 79 228 162 514
START_TEST(s21_floor_test_19) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00120000};
  s21_decimal set_value = {.bits[0] = 0x725DD1D2,
                           .bits[1] = 0x00000012,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 19 = 7 922 816 251
START_TEST(s21_floor_test_20) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00130000};
  s21_decimal set_value = {.bits[0] = 0xD83C94FB,
                           .bits[1] = 0x00000001,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 20 = 792 281 625
START_TEST(s21_floor_test_21) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00140000};
  s21_decimal set_value = {.bits[0] = 0x2F394219,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 27 = 79
START_TEST(s21_floor_test_22) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x001B0000};
  s21_decimal set_value = {.bits[0] = 0x0000004F,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 28 = 7
START_TEST(s21_floor_test_23) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x001C0000};
  s21_decimal set_value = {.bits[0] = 0x00000007,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

/***************************************************************/
/*                      POSITIVE EDGE TESTS                    */
/***************************************************************/

// 21474836485 / 10 ** 1 = 2147483648.5s = 2147483648
START_TEST(s21_floor_test_24) {
  s21_decimal test_value = {.bits[0] = 0x00000005,
                            .bits[1] = 0x00000005,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x80000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 21474836490 / 10 **  1 = 2147483649
START_TEST(s21_floor_test_25) {
  s21_decimal test_value = {.bits[0] = 0x0000000A,
                            .bits[1] = 0x00000005,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x80000001,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 429496729565 / 10 **  1 = 42949672956
START_TEST(s21_floor_test_26) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFDD,
                            .bits[1] = 0x00000063,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFC,
                           .bits[1] = 0x00000009,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 42949672956 / 10 **  1 = 4294967295
START_TEST(s21_floor_test_27) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFC,
                            .bits[1] = 0x00000009,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFF,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 42949672966 / 10 **  1 = 4294967296
START_TEST(s21_floor_test_28) {
  s21_decimal test_value = {.bits[0] = 0x00000005,
                            .bits[1] = 0x0000000A,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000001,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 184467440737095516161 / 10 **  1 = 18446744073709551616
START_TEST(s21_floor_test_29) {
  s21_decimal test_value = {.bits[0] = 0x00000001,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x0000000A,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000001,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 184467440737095516151 / 10 **  1 = 18446744073709551615
START_TEST(s21_floor_test_30) {
  s21_decimal test_value = {.bits[0] = 0x00000009,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x00000009,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0xE6666667,
                           .bits[1] = 0xFFFFFFFF,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 184467440737095516141 / 10 **  1 = -18446744073709551614
START_TEST(s21_floor_test_31) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFED,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x00000009,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFE,
                           .bits[1] = 0xFFFFFFFF,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

/***************************************************************/
/*                        NEGATIVE TESTS                       */
/***************************************************************/

//- 31 to 40 * 10^(0xFFFFFFFF) = - 3 * 10^(0)
START_TEST(s21_floor_test_32) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x00000004,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  for (int i = 31; i < 41; i++) {
    test_value.bits[0] = i;
    s21_floor(test_value, &returned_value);
    ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
  }
}
END_TEST

// 79228162514264337593543950335 / 10 ** 28 = -7.9 = -7
START_TEST(s21_floor_test_33) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x801C0000};
  s21_decimal set_value = {.bits[0] = 0x00000008,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 79228162514264337593543950335 / 10 ** 27 = -79.2 = -80
START_TEST(s21_floor_test_34) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x801B0000};
  s21_decimal set_value = {.bits[0] = 0x00000050,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 79228162514264337593543950335 / 10 ** 26 = -792.2 = -792
START_TEST(s21_floor_test_35) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x801B0000};
  s21_decimal set_value = {.bits[0] = 0x00000050,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 792281625 14 264 337 593 543 950 335 / 10 ** 20 = -792 281 625.1 = -792 281
// 625
START_TEST(s21_floor_test_36) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80140000};
  s21_decimal set_value = {.bits[0] = 0x2F39421A,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 7922816251 4 264 337 593 543 950 335 / 10 ** 19 = -7 922 816 251.4 = -7 922
// 816 251
START_TEST(s21_floor_test_37) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80130000};
  s21_decimal set_value = {.bits[0] = 0xD83C94FC,
                           .bits[1] = 0x00000001,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -79228162514 264 337 593 543 950 335 / 10 ** 18 = -79 228 162 514.2 = -79 228
// 162 514
START_TEST(s21_floor_test_38) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80120000};
  s21_decimal set_value = {.bits[0] = 0x725DD1D3,
                           .bits[1] = 0x00000012,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -79228162514264337593 543 950 335 / 10 ** 9 = -79228162514264337593.2 =
// -79228162514264337593
START_TEST(s21_floor_test_39) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80090000};
  s21_decimal set_value = {.bits[0] = 0xB5A52CBA,
                           .bits[1] = 0x4B82FA09,
                           .bits[2] = 0x00000004,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -792281625142643375935 43 950 335 / 10 ** 8 = -792281625142643375935.4 =
// -792281625142643375935
START_TEST(s21_floor_test_40) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80080000};
  s21_decimal set_value = {.bits[0] = 0x1873BF40,
                           .bits[1] = 0xF31DC461,
                           .bits[2] = 0x0000002A,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -7922816251426433759354 3 950 335 / 10 ** 7 = -7922816251426433759354.3 =
// -7922816251426433759354
START_TEST(s21_floor_test_41) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80070000};
  s21_decimal set_value = {.bits[0] = 0xF485787B,
                           .bits[1] = 0x7F29ABCA,
                           .bits[2] = 0x000001AD,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -79228162514264337593543950335 / 10 ** 0 = -79228162514264337593543950335 =
// -79228162514264337593543950335
START_TEST(s21_floor_test_42) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80000000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFF,
                           .bits[1] = 0xFFFFFFFF,
                           .bits[2] = 0xFFFFFFFF,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

/***************************************************************/
/*                    NEGATIVE EDGE TESTS                      */
/***************************************************************/

// -21474836485 / 10 ** 1 = 0x80000000.5 = 0x80000000
START_TEST(s21_floor_test_43) {
  s21_decimal test_value = {.bits[0] = 0x00000005,
                            .bits[1] = 0x00000005,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x80000001,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -21474836470 / 10 **  1 = -2147483647
START_TEST(s21_floor_test_44) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFF6,
                            .bits[1] = 0x00000004,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x7FFFFFFF,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -429496729565 / 10 **  1 = -42949672956
START_TEST(s21_floor_test_45) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFD,
                            .bits[1] = 0x00000063,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x0000000A,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -18446744073709551612 / 10 **  6 = -18446744073709.551612
START_TEST(s21_floor_test_46) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFC,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80060000};
  s21_decimal set_value = {.bits[0] = 0xf7a0b5ee,
                           .bits[1] = 0x000010c6,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -42949672946 / 10 **  1 = -4294967294
START_TEST(s21_floor_test_47) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFF2,
                            .bits[1] = 0x00000009,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFF,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -184467440737095516161 / 10 **  1 = -18446744073709551616
START_TEST(s21_floor_test_48) {
  s21_decimal test_value = {.bits[0] = 0x00000001,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x0000000A,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x00000001,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000001,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -184467440737095516151 / 10 **  1 = -18446744073709551615
START_TEST(s21_floor_test_49) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x00000009,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000001,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -184467440737095516141 / 10 **  1 = -18446744073709551614
START_TEST(s21_floor_test_50) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFED,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x00000009,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFF,
                           .bits[1] = 0xFFFFFFFF,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -18446744073709551616 / 10 **  1 = -1844674407370955161
START_TEST(s21_floor_test_51) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000001,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x9999999A,
                           .bits[1] = 0x19999999,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_floor(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

/***************************************************************/
/*                    EXCEPTION EDGE TESTS                     */
/***************************************************************/
START_TEST(s21_floor_test_52) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000001,
                            .bits[3] = 0x80000001};
  s21_decimal returned_value = {0x00000000};
  ck_assert_int_eq(s21_floor(test_value, &returned_value), 1);
}
END_TEST

START_TEST(s21_floor_test_53) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000001,
                            .bits[3] = 0x10000001};
  s21_decimal returned_value = {0x00000000};
  ck_assert_int_eq(s21_floor(test_value, &returned_value), 1);
}
END_TEST

START_TEST(s21_floor_test_54) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000001,
                            .bits[3] = 0x50000000};
  s21_decimal returned_value = {0x00000000};
  ck_assert_int_eq(s21_floor(test_value, &returned_value), 1);
}
END_TEST

START_TEST(s21_floor_test_55) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000001,
                            .bits[3] = 0x001D0000};
  s21_decimal returned_value = {0x00000000};
  ck_assert_int_eq(s21_floor(test_value, &returned_value), 1);
}
END_TEST

static void suite_add_s21_floor(Suite *s) {
  TCase *tc;
  tc = tcase_create("s21_floor");
  tcase_add_test(tc, s21_floor_test_1);
  tcase_add_test(tc, s21_floor_test_2);
  tcase_add_test(tc, s21_floor_test_3);
  tcase_add_test(tc, s21_floor_test_4);
  tcase_add_test(tc, s21_floor_test_5);
  tcase_add_test(tc, s21_floor_test_6);
  tcase_add_test(tc, s21_floor_test_7);
  tcase_add_test(tc, s21_floor_test_8);
  tcase_add_test(tc, s21_floor_test_9);
  tcase_add_test(tc, s21_floor_test_10);
  tcase_add_test(tc, s21_floor_test_11);
  tcase_add_test(tc, s21_floor_test_12);
  tcase_add_test(tc, s21_floor_test_13);
  tcase_add_test(tc, s21_floor_test_14);
  tcase_add_test(tc, s21_floor_test_15);
  tcase_add_test(tc, s21_floor_test_16);
  tcase_add_test(tc, s21_floor_test_17);
  tcase_add_test(tc, s21_floor_test_18);
  tcase_add_test(tc, s21_floor_test_19);
  tcase_add_test(tc, s21_floor_test_20);
  tcase_add_test(tc, s21_floor_test_21);
  tcase_add_test(tc, s21_floor_test_22);
  tcase_add_test(tc, s21_floor_test_23);
  tcase_add_test(tc, s21_floor_test_24);
  tcase_add_test(tc, s21_floor_test_25);
  tcase_add_test(tc, s21_floor_test_26);
  tcase_add_test(tc, s21_floor_test_27);
  tcase_add_test(tc, s21_floor_test_28);
  tcase_add_test(tc, s21_floor_test_29);
  tcase_add_test(tc, s21_floor_test_30);
  tcase_add_test(tc, s21_floor_test_31);
  tcase_add_test(tc, s21_floor_test_32);
  tcase_add_test(tc, s21_floor_test_33);
  tcase_add_test(tc, s21_floor_test_34);
  tcase_add_test(tc, s21_floor_test_35);
  tcase_add_test(tc, s21_floor_test_36);
  tcase_add_test(tc, s21_floor_test_37);
  tcase_add_test(tc, s21_floor_test_38);
  tcase_add_test(tc, s21_floor_test_39);
  tcase_add_test(tc, s21_floor_test_40);
  tcase_add_test(tc, s21_floor_test_41);
  tcase_add_test(tc, s21_floor_test_42);
  tcase_add_test(tc, s21_floor_test_43);
  tcase_add_test(tc, s21_floor_test_44);
  tcase_add_test(tc, s21_floor_test_45);
  tcase_add_test(tc, s21_floor_test_46);
  tcase_add_test(tc, s21_floor_test_47);
  tcase_add_test(tc, s21_floor_test_48);
  tcase_add_test(tc, s21_floor_test_49);
  tcase_add_test(tc, s21_floor_test_50);
  tcase_add_test(tc, s21_floor_test_51);
  tcase_add_test(tc, s21_floor_test_52);
  tcase_add_test(tc, s21_floor_test_53);
  tcase_add_test(tc, s21_floor_test_54);
  tcase_add_test(tc, s21_floor_test_55);
  suite_add_tcase(s, tc);
}

/***************************************************************/
/*                                                             */
/*                      TRUNCATE TESTS                         */
/*                                                             */
/***************************************************************/
/*                        POSITIVE TESTS                       */
/***************************************************************/

// 30 * 10^(0xFFFFFFFF) = 3 * 10^(0) XXX 10
START_TEST(s21_truncate_test_1) {
  s21_decimal test_value = {.bits[0] = 0x0000001E,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x00000003,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  for (int i = 30; i < 40; i++) {
    test_value.bits[0] = i;
    s21_truncate(test_value, &returned_value);
    ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
  }
}
END_TEST

// 322 *10^(-2) = 3 * 10^(0)
START_TEST(s21_truncate_test_2) {
  s21_decimal test_value = {.bits[0] = 0x00000142,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00020000};
  s21_decimal set_value = {.bits[0] = 0x00000003,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 322 * 10^(-3) = 0 * 10^(0)
START_TEST(s21_truncate_test_3) {
  s21_decimal test_value = {.bits[0] = 0x00000142,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00030000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 2*(31) * 10 ^ (-28) = 0
START_TEST(s21_truncate_test_4) {
  s21_decimal test_value = {.bits[0] = 0x7FFFFFFF,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x001C0000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 2*(96) * 10 ^ (-28) = 7
START_TEST(s21_truncate_test_5) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x001C0000};
  s21_decimal set_value = {.bits[0] = 0x00000007,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2^(96) - 1) * 10^(-28)
START_TEST(s21_truncate_test_6) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x7FFFFFFF,
                            .bits[3] = 0x001C0000};
  s21_decimal set_value = {.bits[0] = 0x00000003,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 2^(33) * 10^(-9) = 8  ||  2**33 / 10 ** 9 = 8.589934592
START_TEST(s21_truncate_test_7) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000001,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00090000};
  s21_decimal set_value = {.bits[0] = 0x00000004,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 2^(34) * 10^(-9) = 17  ||  2**34 / 10 ** 9 = 17.179869184
START_TEST(s21_truncate_test_8) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000002,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00090000};
  s21_decimal set_value = {.bits[0] = 0x00000008,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2^(34) + 2^(35)) * 10^(-9) = 51  ||  (2**34+2**35) / 10 ** 9 = 51.539607552
START_TEST(s21_truncate_test_9) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x0000000C,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00090000};
  s21_decimal set_value = {.bits[0] = 0x00000033,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 0 = 79 228 162 514 264 337 593 543 950 335
START_TEST(s21_truncate_test_10) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00000000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFF,
                           .bits[1] = 0xFFFFFFFF,
                           .bits[2] = 0xFFFFFFFF,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 1 = 7 922 816 251 426 433 759 354 395 033
START_TEST(s21_truncate_test_11) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x99999999,
                           .bits[1] = 0x99999999,
                           .bits[2] = 0x19999999,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 2 = 792 281 625 142 643 375 935 439 503
START_TEST(s21_truncate_test_12) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00020000};
  s21_decimal set_value = {.bits[0] = 0x28F5C28F,
                           .bits[1] = 0xF5C28F5C,
                           .bits[2] = 0x028F5C28,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 3 = 79 228 162 514 264 337 593 543 950
START_TEST(s21_truncate_test_13) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00030000};
  s21_decimal set_value = {.bits[0] = 0x9db22d0e,
                           .bits[1] = 0x4bc6a7ef,
                           .bits[2] = 0x00418937,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 4 = 7 922 816 251 426 433 759 354 395
START_TEST(s21_truncate_test_14) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00040000};
  s21_decimal set_value = {.bits[0] = 0x295E9E1B,
                           .bits[1] = 0xBAC710CB,
                           .bits[2] = 0x00068DB8,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 9 = 79 228 162 514 264 337 593
START_TEST(s21_truncate_test_15) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00090000};
  s21_decimal set_value = {.bits[0] = 0xB5A52CB9,
                           .bits[1] = 0x4B82FA09,
                           .bits[2] = 0x00000004,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 10 = 7 922 816 251 426 433 759
START_TEST(s21_truncate_test_16) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x000A0000};
  s21_decimal set_value = {.bits[0] = 0x5EF6EADF,
                           .bits[1] = 0x6DF37F67,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 11 = 792 281 625 142 643 375
START_TEST(s21_truncate_test_17) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x000B0000};
  s21_decimal set_value = {.bits[0] = 0xBCB24AAF,
                           .bits[1] = 0x0AFEBFF0,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 12 = 79 228 162 514 264 337
START_TEST(s21_truncate_test_18) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x000C0000};
  s21_decimal set_value = {.bits[0] = 0x12DEA111,
                           .bits[1] = 0x01197998,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 18 = 79 228 162 514
START_TEST(s21_truncate_test_19) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00120000};
  s21_decimal set_value = {.bits[0] = 0x725DD1D2,
                           .bits[1] = 0x00000012,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 19 = 7 922 816 251
START_TEST(s21_truncate_test_20) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00130000};
  s21_decimal set_value = {.bits[0] = 0xD83C94FB,
                           .bits[1] = 0x00000001,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 20 = 792 281 625
START_TEST(s21_truncate_test_21) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00140000};
  s21_decimal set_value = {.bits[0] = 0x2F394219,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 27 = 79
START_TEST(s21_truncate_test_22) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x001B0000};
  s21_decimal set_value = {.bits[0] = 0x0000004F,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 28 = 7
START_TEST(s21_truncate_test_23) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x001C0000};
  s21_decimal set_value = {.bits[0] = 0x00000007,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

/***************************************************************/
/*                      POSITIVE EDGE TESTS                    */
/***************************************************************/

// 21474836485 / 10 ** 1 = 2147483648.5s = 2147483648
START_TEST(s21_truncate_test_24) {
  s21_decimal test_value = {.bits[0] = 0x00000005,
                            .bits[1] = 0x00000005,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x80000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 21474836490 / 10 **  1 = 2147483649
START_TEST(s21_truncate_test_25) {
  s21_decimal test_value = {.bits[0] = 0x0000000A,
                            .bits[1] = 0x00000005,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x80000001,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 429496729565 / 10 **  1 = 42949672956
START_TEST(s21_truncate_test_26) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFDD,
                            .bits[1] = 0x00000063,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFC,
                           .bits[1] = 0x00000009,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 42949672956 / 10 **  1 = 4294967295
START_TEST(s21_truncate_test_27) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFC,
                            .bits[1] = 0x00000009,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFF,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 42949672966 / 10 **  1 = 4294967296
START_TEST(s21_truncate_test_28) {
  s21_decimal test_value = {.bits[0] = 0x00000005,
                            .bits[1] = 0x0000000A,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000001,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 184467440737095516161 / 10 **  1 = 18446744073709551616
START_TEST(s21_truncate_test_29) {
  s21_decimal test_value = {.bits[0] = 0x00000001,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x0000000A,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000001,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 184467440737095516151 / 10 **  1 = 18446744073709551615
START_TEST(s21_truncate_test_30) {
  s21_decimal test_value = {.bits[0] = 0x00000009,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x00000009,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0xE6666667,
                           .bits[1] = 0xFFFFFFFF,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 184467440737095516141 / 10 **  1 = -18446744073709551614
START_TEST(s21_truncate_test_31) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFED,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x00000009,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFE,
                           .bits[1] = 0xFFFFFFFF,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

/***************************************************************/
/*                        NEGATIVE TESTS                       */
/***************************************************************/

//- 31 to 40 * 10^(0xFFFFFFFF) = - 3 * 10^(0)
START_TEST(s21_truncate_test_32) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x00000003,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  for (int i = 30; i < 40; i++) {
    test_value.bits[0] = i;
    s21_truncate(test_value, &returned_value);
    ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
  }
}
END_TEST

// 79228162514264337593543950335 / 10 ** 28 = -7.9 = -7
START_TEST(s21_truncate_test_33) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x801C0000};
  s21_decimal set_value = {.bits[0] = 0x00000007,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 79228162514264337593543950335 / 10 ** 27 = -79.2 = -80
START_TEST(s21_truncate_test_34) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x801B0000};
  s21_decimal set_value = {.bits[0] = 0x0000004F,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 79228162514264337593543950335 / 10 ** 26 = -792.2 = -792
START_TEST(s21_truncate_test_35) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x801B0000};
  s21_decimal set_value = {.bits[0] = 0x0000004F,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 792281625 14 264 337 593 543 950 335 / 10 ** 20 = -792 281 625.1 = -792 281
// 625
START_TEST(s21_truncate_test_36) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80140000};
  s21_decimal set_value = {.bits[0] = 0x2F394219,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 7922816251 4 264 337 593 543 950 335 / 10 ** 19 = -7 922 816 251.4 = -7 922
// 816 251
START_TEST(s21_truncate_test_37) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80130000};
  s21_decimal set_value = {.bits[0] = 0xD83C94FB,
                           .bits[1] = 0x00000001,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -79228162514 264 337 593 543 950 335 / 10 ** 18 = -79 228 162 514.2 = -79 228
// 162 514
START_TEST(s21_truncate_test_38) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80120000};
  s21_decimal set_value = {.bits[0] = 0x725DD1D2,
                           .bits[1] = 0x00000012,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -79228162514264337593 543 950 335 / 10 ** 9 = -79228162514264337593.2 =
// -79228162514264337593
START_TEST(s21_truncate_test_39) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80090000};
  s21_decimal set_value = {.bits[0] = 0xB5A52CB9,
                           .bits[1] = 0x4B82FA09,
                           .bits[2] = 0x00000004,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -792281625142643375935 43 950 335 / 10 ** 8 = -792281625142643375935.4 =
// -792281625142643375935
START_TEST(s21_truncate_test_40) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80080000};
  s21_decimal set_value = {.bits[0] = 0x1873BF3F,
                           .bits[1] = 0xF31DC461,
                           .bits[2] = 0x0000002A,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -7922816251426433759354 3 950 335 / 10 ** 7 = -7922816251426433759354.3 =
// -7922816251426433759354
START_TEST(s21_truncate_test_41) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80070000};
  s21_decimal set_value = {.bits[0] = 0xF485787A,
                           .bits[1] = 0x7F29ABCA,
                           .bits[2] = 0x000001AD,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -79228162514264337593543950335 / 10 ** 0 = -79228162514264337593543950335 =
// -79228162514264337593543950335
START_TEST(s21_truncate_test_42) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80000000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFF,
                           .bits[1] = 0xFFFFFFFF,
                           .bits[2] = 0xFFFFFFFF,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

/***************************************************************/
/*                    NEGATIVE EDGE TESTS                      */
/***************************************************************/

// -21474836485 / 10 ** 1 = 0x80000000.5 = 0x80000000
START_TEST(s21_truncate_test_43) {
  s21_decimal test_value = {.bits[0] = 0x00000005,
                            .bits[1] = 0x00000005,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x80000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -21474836470 / 10 **  1 = -2147483647
START_TEST(s21_truncate_test_44) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFF6,
                            .bits[1] = 0x00000004,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x7FFFFFFF,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -429496729565 / 10 **  1 = -42949672956
START_TEST(s21_truncate_test_45) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFDD,
                            .bits[1] = 0x00000063,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFC,
                           .bits[1] = 0x00000009,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -42949672956 / 10 **  1 = -4294967295
START_TEST(s21_truncate_test_46) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFC,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80060000};
  s21_decimal set_value = {.bits[0] = 0xf7a0b5ed,
                           .bits[1] = 0x000010c6,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -42949672946 / 10 **  1 = -4294967294
START_TEST(s21_truncate_test_47) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFF2,
                            .bits[1] = 0x00000009,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFE,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -184467440737095516161 / 10 **  1 = -18446744073709551616
START_TEST(s21_truncate_test_48) {
  s21_decimal test_value = {.bits[0] = 0x00000001,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x0000000A,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000001,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -184467440737095516151 / 10 **  1 = -18446744073709551615
START_TEST(s21_truncate_test_49) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x00000009,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFF,
                           .bits[1] = 0xFFFFFFFF,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -184467440737095516141 / 10 **  1 = -18446744073709551614
START_TEST(s21_truncate_test_50) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFED,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x00000009,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFE,
                           .bits[1] = 0xFFFFFFFF,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -18446744073709551616 / 10 **  1 = -1844674407370955161
START_TEST(s21_truncate_test_51) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000001,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x99999999,
                           .bits[1] = 0x19999999,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_truncate(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

/***************************************************************/
/*                    EXCEPTION EDGE TESTS                     */
/***************************************************************/
START_TEST(s21_truncate_test_52) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000001,
                            .bits[3] = 0x80000001};
  s21_decimal returned_value = {0x00000000};
  ck_assert_int_eq(s21_truncate(test_value, &returned_value), 1);
}
END_TEST

START_TEST(s21_truncate_test_53) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000001,
                            .bits[3] = 0x10000001};
  s21_decimal returned_value = {0x00000000};
  ck_assert_int_eq(s21_truncate(test_value, &returned_value), 1);
}
END_TEST

START_TEST(s21_truncate_test_54) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000001,
                            .bits[3] = 0x50000000};
  s21_decimal returned_value = {0x00000000};
  ck_assert_int_eq(s21_truncate(test_value, &returned_value), 1);
}
END_TEST

START_TEST(s21_truncate_test_55) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000001,
                            .bits[3] = 0x001D0000};
  s21_decimal returned_value = {0x00000000};
  ck_assert_int_eq(s21_truncate(test_value, &returned_value), 1);
}
END_TEST

static void suite_add_s21_truncate(Suite *s) {
  TCase *tc;
  tc = tcase_create("s21_truncate");
  tcase_add_test(tc, s21_truncate_test_1);
  tcase_add_test(tc, s21_truncate_test_2);
  tcase_add_test(tc, s21_truncate_test_3);
  tcase_add_test(tc, s21_truncate_test_4);
  tcase_add_test(tc, s21_truncate_test_5);
  tcase_add_test(tc, s21_truncate_test_6);
  tcase_add_test(tc, s21_truncate_test_7);
  tcase_add_test(tc, s21_truncate_test_8);
  tcase_add_test(tc, s21_truncate_test_9);
  tcase_add_test(tc, s21_truncate_test_10);
  tcase_add_test(tc, s21_truncate_test_11);
  tcase_add_test(tc, s21_truncate_test_12);
  tcase_add_test(tc, s21_truncate_test_13);
  tcase_add_test(tc, s21_truncate_test_14);
  tcase_add_test(tc, s21_truncate_test_15);
  tcase_add_test(tc, s21_truncate_test_16);
  tcase_add_test(tc, s21_truncate_test_17);
  tcase_add_test(tc, s21_truncate_test_18);
  tcase_add_test(tc, s21_truncate_test_19);
  tcase_add_test(tc, s21_truncate_test_20);
  tcase_add_test(tc, s21_truncate_test_21);
  tcase_add_test(tc, s21_truncate_test_22);
  tcase_add_test(tc, s21_truncate_test_23);
  tcase_add_test(tc, s21_truncate_test_24);
  tcase_add_test(tc, s21_truncate_test_25);
  tcase_add_test(tc, s21_truncate_test_26);
  tcase_add_test(tc, s21_truncate_test_27);
  tcase_add_test(tc, s21_truncate_test_28);
  tcase_add_test(tc, s21_truncate_test_29);
  tcase_add_test(tc, s21_truncate_test_30);
  tcase_add_test(tc, s21_truncate_test_31);
  tcase_add_test(tc, s21_truncate_test_32);
  tcase_add_test(tc, s21_truncate_test_33);
  tcase_add_test(tc, s21_truncate_test_34);
  tcase_add_test(tc, s21_truncate_test_35);
  tcase_add_test(tc, s21_truncate_test_36);
  tcase_add_test(tc, s21_truncate_test_37);
  tcase_add_test(tc, s21_truncate_test_38);
  tcase_add_test(tc, s21_truncate_test_39);
  tcase_add_test(tc, s21_truncate_test_40);
  tcase_add_test(tc, s21_truncate_test_41);
  tcase_add_test(tc, s21_truncate_test_42);
  tcase_add_test(tc, s21_truncate_test_43);
  tcase_add_test(tc, s21_truncate_test_44);
  tcase_add_test(tc, s21_truncate_test_45);
  tcase_add_test(tc, s21_truncate_test_46);
  tcase_add_test(tc, s21_truncate_test_47);
  tcase_add_test(tc, s21_truncate_test_48);
  tcase_add_test(tc, s21_truncate_test_49);
  tcase_add_test(tc, s21_truncate_test_50);
  tcase_add_test(tc, s21_truncate_test_51);
  tcase_add_test(tc, s21_truncate_test_52);
  tcase_add_test(tc, s21_truncate_test_53);
  tcase_add_test(tc, s21_truncate_test_54);
  tcase_add_test(tc, s21_truncate_test_55);
  suite_add_tcase(s, tc);
}

/***************************************************************/
/*                                                             */
/*                         ROUND TESTS                         */
/*     … You spin me right 'round, baby, right 'round          */
/*     Like a record, baby, right 'round, 'round, 'round       */
/***************************************************************/
/*                        POSITIVE TESTS                       */
/***************************************************************/

// 30 * 10^(0xFFFFFFFF) = 3 * 10^(0) XXX 10
START_TEST(s21_round_test_1) {
  s21_decimal test_value = {.bits[0] = 0x0000001E,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x00000002,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  for (int i = 15; i < 26; i++) {
    test_value.bits[0] = i;
    s21_round(test_value, &returned_value);
    ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
  }
}
END_TEST

// 322 *10^(-2) = 3 * 10^(0)
START_TEST(s21_round_test_2) {
  s21_decimal test_value = {.bits[0] = 0x00000142,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00020000};
  s21_decimal set_value = {.bits[0] = 0x00000003,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 322 * 10^(-3) = 0 * 10^(0)
START_TEST(s21_round_test_3) {
  s21_decimal test_value = {.bits[0] = 0x00000142,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00030000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 2*(31) * 10 ^ (-28) = 0
START_TEST(s21_round_test_4) {
  s21_decimal test_value = {.bits[0] = 0x7FFFFFFF,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x001C0000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 2*(96) * 10 ^ (-28) = 7
START_TEST(s21_round_test_5) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x001C0000};
  s21_decimal set_value = {.bits[0] = 0x00000008,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2^(96) - 1) * 10^(-28)
START_TEST(s21_round_test_6) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x7FFFFFFF,
                            .bits[3] = 0x001C0000};
  s21_decimal set_value = {.bits[0] = 0x00000004,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 2^(33) * 10^(-9) = 8  ||  2**33 / 10 ** 9 = 8.589934592
START_TEST(s21_round_test_7) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000001,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00090000};
  s21_decimal set_value = {.bits[0] = 0x00000004,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 2^(34) * 10^(-9) = 17  ||  2**34 / 10 ** 9 = 17.179869184
START_TEST(s21_round_test_8) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000002,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00090000};
  s21_decimal set_value = {.bits[0] = 0x00000009,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2^(34) + 2^(35)) * 10^(-9) = 51  ||  (2**34+2**35) / 10 ** 9 = 51.539607552
START_TEST(s21_round_test_9) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x0000000C,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00090000};
  s21_decimal set_value = {.bits[0] = 0x00000034,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 0 = 79 228 162 514 264 337 593 543 950 335
START_TEST(s21_round_test_10) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00000000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFF,
                           .bits[1] = 0xFFFFFFFF,
                           .bits[2] = 0xFFFFFFFF,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 1 = 7 922 816 251 426 433 759 354 395 033
START_TEST(s21_round_test_11) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x99999999,
                           .bits[1] = 0x99999999,
                           .bits[2] = 0x19999999,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 2 = 792 281 625 142 643 375 935 439 503
START_TEST(s21_round_test_12) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00020000};
  s21_decimal set_value = {.bits[0] = 0x28F5C28F,
                           .bits[1] = 0xF5C28F5C,
                           .bits[2] = 0x028F5C28,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 3 = 79 228 162 514 264 337 593 543 950
START_TEST(s21_round_test_13) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00030000};
  s21_decimal set_value = {.bits[0] = 0x9db22d0e,
                           .bits[1] = 0x4bc6a7ef,
                           .bits[2] = 0x00418937,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 4 = 7 922 816 251 426 433 759 354 395
START_TEST(s21_round_test_14) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00040000};
  s21_decimal set_value = {.bits[0] = 0x295E9E1B,
                           .bits[1] = 0xBAC710CB,
                           .bits[2] = 0x00068DB8,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 9 = 79 228 162 514 264 337 593
START_TEST(s21_round_test_15) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00090000};
  s21_decimal set_value = {.bits[0] = 0xB5A52CBA,
                           .bits[1] = 0x4B82FA09,
                           .bits[2] = 0x00000004,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 10 = 7 922 816 251 426 433 759
START_TEST(s21_round_test_16) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x000A0000};
  s21_decimal set_value = {.bits[0] = 0x5EF6EADF,
                           .bits[1] = 0x6DF37F67,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 11 = 792 281 625 142 643 375
START_TEST(s21_round_test_17) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x000B0000};
  s21_decimal set_value = {.bits[0] = 0xBCB24AB0,
                           .bits[1] = 0x0AFEBFF0,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 12 = 79 228 162 514 264 337
START_TEST(s21_round_test_18) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x000C0000};
  s21_decimal set_value = {.bits[0] = 0x12DEA112,
                           .bits[1] = 0x01197998,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 18 = 79 228 162 514
START_TEST(s21_round_test_19) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00120000};
  s21_decimal set_value = {.bits[0] = 0x725DD1D2,
                           .bits[1] = 0x00000012,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 19 = 7 922 816 251
START_TEST(s21_round_test_20) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00130000};
  s21_decimal set_value = {.bits[0] = 0xD83C94FB,
                           .bits[1] = 0x00000001,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 20 = 792 281 625
START_TEST(s21_round_test_21) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x00140000};
  s21_decimal set_value = {.bits[0] = 0x2F394219,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 27 = 79
START_TEST(s21_round_test_22) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x001B0000};
  s21_decimal set_value = {.bits[0] = 0x0000004F,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// (2**96 - 1) / 10 ** 28 = 7
START_TEST(s21_round_test_23) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x001C0000};
  s21_decimal set_value = {.bits[0] = 0x00000008,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

/***************************************************************/
/*                      POSITIVE EDGE TESTS                    */
/***************************************************************/

// 21474836485 / 10 ** 1 = 2147483648.5s = 2147483648 !BANK ROUND!
START_TEST(s21_round_test_24) {
  s21_decimal test_value = {.bits[0] = 0x00000005,
                            .bits[1] = 0x00000005,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x80000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 21474836490 / 10 **  1 = 2147483649
START_TEST(s21_round_test_25) {
  s21_decimal test_value = {.bits[0] = 0x0000000A,
                            .bits[1] = 0x00000005,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x80000001,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 429496729565 / 10 **  1 = 42949672956
START_TEST(s21_round_test_26) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFDD,
                            .bits[1] = 0x00000063,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFC,
                           .bits[1] = 0x00000009,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 42949672956 / 10 **  1 = 4294967295
START_TEST(s21_round_test_27) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFC,
                            .bits[1] = 0x00000009,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000001,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 42949672966 / 10 **  1 = 4294967296
START_TEST(s21_round_test_28) {
  s21_decimal test_value = {.bits[0] = 0x00000005,
                            .bits[1] = 0x0000000A,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000001,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 184467440737095516161 / 10 **  1 = 18446744073709551616
START_TEST(s21_round_test_29) {
  s21_decimal test_value = {.bits[0] = 0x00000001,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x0000000A,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000001,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 184467440737095516151 / 10 **  1 = 18446744073709551615
START_TEST(s21_round_test_30) {
  s21_decimal test_value = {.bits[0] = 0x00000009,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x00000009,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0xE6666667,
                           .bits[1] = 0xFFFFFFFF,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 184467440737095516141 / 10 **  1 = -18446744073709551614
START_TEST(s21_round_test_31) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFED,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x00000009,
                            .bits[3] = 0x00010000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFE,
                           .bits[1] = 0xFFFFFFFF,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x00000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

/***************************************************************/
/*                        NEGATIVE TESTS                       */
/***************************************************************/

//- 31 to 40 * 10^(0xFFFFFFFF) = - 3 * 10^(0)
START_TEST(s21_round_test_32) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x00000003,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  for (int i = 26; i < 35; i++) {
    test_value.bits[0] = i;
    s21_round(test_value, &returned_value);
    ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
  }
}
END_TEST

// 79228162514264337593543950335 / 10 ** 28 = -7.9 = -7
START_TEST(s21_round_test_33) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x801C0000};
  s21_decimal set_value = {.bits[0] = 0x00000008,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 79228162514264337593543950335 / 10 ** 27 = -79.2 = -80
START_TEST(s21_round_test_34) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x801B0000};
  s21_decimal set_value = {.bits[0] = 0x0000004F,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 79228162514264337593543950335 / 10 ** 26 = -79.22 = -79
START_TEST(s21_round_test_35) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x801B0000};
  s21_decimal set_value = {.bits[0] = 0x0000004F,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 792281625 14 264 337 593 543 950 335 / 10 ** 20 = -792 281 625.1 = -792 281
// 625
START_TEST(s21_round_test_36) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80140000};
  s21_decimal set_value = {.bits[0] = 0x2F394219,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// 7922816251 4 264 337 593 543 950 335 / 10 ** 19 = -7 922 816 251.4 = -7 922
// 816 251
START_TEST(s21_round_test_37) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80130000};
  s21_decimal set_value = {.bits[0] = 0xD83C94FB,
                           .bits[1] = 0x00000001,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -79228162514 264 337 593 543 950 335 / 10 ** 18 = -79 228 162 514.2 = -79 228
// 162 514
START_TEST(s21_round_test_38) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80120000};
  s21_decimal set_value = {.bits[0] = 0x725DD1D2,
                           .bits[1] = 0x00000012,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -79228162514264337593 543 950 335 / 10 ** 9 = -79228162514264337593.2 =
// -79228162514264337593
START_TEST(s21_round_test_39) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80090000};
  s21_decimal set_value = {.bits[0] = 0xB5A52CBA,
                           .bits[1] = 0x4B82FA09,
                           .bits[2] = 0x00000004,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -792281625142643375935 43 950 335 / 10 ** 8 = -792281625142643375935.4 =
// -792281625142643375935
START_TEST(s21_round_test_40) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80080000};
  s21_decimal set_value = {.bits[0] = 0x1873BF3F,
                           .bits[1] = 0xF31DC461,
                           .bits[2] = 0x0000002A,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -7922816251426433759354 3 950 335 / 10 ** 7 = -7922816251426433759354.3 =
// -7922816251426433759354
START_TEST(s21_round_test_41) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80070000};
  s21_decimal set_value = {.bits[0] = 0xF485787A,
                           .bits[1] = 0x7F29ABCA,
                           .bits[2] = 0x000001AD,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -79228162514264337593543950335 / 10 ** 0 = -79228162514264337593543950335 =
// -79228162514264337593543950335
START_TEST(s21_round_test_42) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0xFFFFFFFF,
                            .bits[3] = 0x80000000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFF,
                           .bits[1] = 0xFFFFFFFF,
                           .bits[2] = 0xFFFFFFFF,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

/***************************************************************/
/*                    NEGATIVE EDGE TESTS                      */
/***************************************************************/

// -21474836485 / 10 ** 1 = 0x80000000.5 = 0x80000000
START_TEST(s21_round_test_43) {
  s21_decimal test_value = {.bits[0] = 0x00000005,
                            .bits[1] = 0x00000005,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x80000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -21474836470 / 10 **  1 = -2147483647
START_TEST(s21_round_test_44) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFF6,
                            .bits[1] = 0x00000004,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x7FFFFFFF,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -429496729565 / 10 **  1 = -42949672956
START_TEST(s21_round_test_45) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFD,
                            .bits[1] = 0x00000063,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x0000000A,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -18446744073709551612 / 10 **  6 = -18446744073709.551612
START_TEST(s21_round_test_46) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFC,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80060000};
  s21_decimal set_value = {.bits[0] = 0xf7a0b5ee,
                           .bits[1] = 0x000010c6,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -42949672946 / 10 **  1 = -4294967294
START_TEST(s21_round_test_47) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFF2,
                            .bits[1] = 0x00000009,
                            .bits[2] = 0x00000000,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFF,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -184467440737095516161 / 10 **  1 = -18446744073709551616
START_TEST(s21_round_test_48) {
  s21_decimal test_value = {.bits[0] = 0x00000001,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x0000000A,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000001,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -184467440737095516151 / 10 **  1 = -18446744073709551615
START_TEST(s21_round_test_49) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFFF,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x00000009,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x00000000,
                           .bits[1] = 0x00000000,
                           .bits[2] = 0x00000001,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -184467440737095516141 / 10 **  1 = -18446744073709551614
START_TEST(s21_round_test_50) {
  s21_decimal test_value = {.bits[0] = 0xFFFFFFED,
                            .bits[1] = 0xFFFFFFFF,
                            .bits[2] = 0x00000009,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0xFFFFFFFE,
                           .bits[1] = 0xFFFFFFFF,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

// -18446744073709551616 / 10 **  1 = -1844674407370955161
START_TEST(s21_round_test_51) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000001,
                            .bits[3] = 0x80010000};
  s21_decimal set_value = {.bits[0] = 0x9999999A,
                           .bits[1] = 0x19999999,
                           .bits[2] = 0x00000000,
                           .bits[3] = 0x80000000};
  s21_decimal returned_value = {0x00000000};
  s21_round(test_value, &returned_value);
  ck_assert_mem_eq(&set_value, &returned_value, sizeof(s21_decimal));
}
END_TEST

/***************************************************************/
/*                    EXCEPTION EDGE TESTS                     */
/***************************************************************/
START_TEST(s21_round_test_52) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000001,
                            .bits[3] = 0x80000001};
  s21_decimal returned_value = {0x00000000};
  ck_assert_int_eq(s21_round(test_value, &returned_value), 1);
}
END_TEST

START_TEST(s21_round_test_53) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000001,
                            .bits[3] = 0x10000001};
  s21_decimal returned_value = {0x00000000};
  ck_assert_int_eq(s21_round(test_value, &returned_value), 1);
}
END_TEST

START_TEST(s21_round_test_54) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000001,
                            .bits[3] = 0x50000000};
  s21_decimal returned_value = {0x00000000};
  ck_assert_int_eq(s21_round(test_value, &returned_value), 1);
}
END_TEST

START_TEST(s21_round_test_55) {
  s21_decimal test_value = {.bits[0] = 0x00000000,
                            .bits[1] = 0x00000000,
                            .bits[2] = 0x00000001,
                            .bits[3] = 0x001D0000};
  s21_decimal returned_value = {0x00000000};
  ck_assert_int_eq(s21_round(test_value, &returned_value), 1);
}
END_TEST

static void suite_add_s21_round(Suite *s) {
  TCase *tc;
  tc = tcase_create("s21_round");
  tcase_add_test(tc, s21_round_test_1);
  tcase_add_test(tc, s21_round_test_2);
  tcase_add_test(tc, s21_round_test_3);
  tcase_add_test(tc, s21_round_test_4);
  tcase_add_test(tc, s21_round_test_5);
  tcase_add_test(tc, s21_round_test_6);
  tcase_add_test(tc, s21_round_test_7);
  tcase_add_test(tc, s21_round_test_8);
  tcase_add_test(tc, s21_round_test_9);
  tcase_add_test(tc, s21_round_test_10);
  tcase_add_test(tc, s21_round_test_11);
  tcase_add_test(tc, s21_round_test_12);
  tcase_add_test(tc, s21_round_test_13);
  tcase_add_test(tc, s21_round_test_14);
  tcase_add_test(tc, s21_round_test_15);
  tcase_add_test(tc, s21_round_test_16);
  tcase_add_test(tc, s21_round_test_17);
  tcase_add_test(tc, s21_round_test_18);
  tcase_add_test(tc, s21_round_test_19);
  tcase_add_test(tc, s21_round_test_20);
  tcase_add_test(tc, s21_round_test_21);
  tcase_add_test(tc, s21_round_test_22);
  tcase_add_test(tc, s21_round_test_23);
  tcase_add_test(tc, s21_round_test_24);
  tcase_add_test(tc, s21_round_test_25);
  tcase_add_test(tc, s21_round_test_26);
  tcase_add_test(tc, s21_round_test_27);
  tcase_add_test(tc, s21_round_test_28);
  tcase_add_test(tc, s21_round_test_29);
  tcase_add_test(tc, s21_round_test_30);
  tcase_add_test(tc, s21_round_test_31);
  tcase_add_test(tc, s21_round_test_32);
  tcase_add_test(tc, s21_round_test_33);
  tcase_add_test(tc, s21_round_test_34);
  tcase_add_test(tc, s21_round_test_35);
  tcase_add_test(tc, s21_round_test_36);
  tcase_add_test(tc, s21_round_test_37);
  tcase_add_test(tc, s21_round_test_38);
  tcase_add_test(tc, s21_round_test_39);
  tcase_add_test(tc, s21_round_test_40);
  tcase_add_test(tc, s21_round_test_41);
  tcase_add_test(tc, s21_round_test_42);
  tcase_add_test(tc, s21_round_test_43);
  tcase_add_test(tc, s21_round_test_44);
  tcase_add_test(tc, s21_round_test_45);
  tcase_add_test(tc, s21_round_test_46);
  tcase_add_test(tc, s21_round_test_47);
  tcase_add_test(tc, s21_round_test_48);
  tcase_add_test(tc, s21_round_test_49);
  tcase_add_test(tc, s21_round_test_50);
  tcase_add_test(tc, s21_round_test_51);
  tcase_add_test(tc, s21_round_test_52);
  tcase_add_test(tc, s21_round_test_53);
  tcase_add_test(tc, s21_round_test_54);
  tcase_add_test(tc, s21_round_test_55);

  suite_add_tcase(s, tc);
}

void suite_add_rounding(Suite *s) {
  suite_add_s21_floor(s);
  suite_add_s21_round(s);
  suite_add_s21_truncate(s);
}
