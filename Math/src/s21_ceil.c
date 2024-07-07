//
// Created by maksim on 12.11.23.
//
#include "s21_math.h"
long double s21_ceil(double x) {
  if (x != s21_floor(x)) x = s21_floor(x) + 1;
  return x;
}