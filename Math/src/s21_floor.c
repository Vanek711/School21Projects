//
// Created by maksim on 12.11.23.
//
long double s21_floor(double x) {
  if (x >= 0 || x == (int)x)
    x = (int)x;
  else
    x = (int)x - 1;
  return x;
}
