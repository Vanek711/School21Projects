#ifndef S21_CALCULATOR_H
#define S21_CALCULATOR_H

#include <stdbool.h>

#include "s21_stack.h"

#define COS 'c'
#define SIN 's'
#define TAN 't'
#define ACOS 'a'
#define ASIN 'i'
#define ATAN 'n'
#define SQRT 'q'
#define LN 'l'
#define LOG 'g'
#define UPLUS 'p'
#define UMINUS 'm'
#define MOD '%'

#define MAX_LEN 255

#ifdef __cplusplus
extern "C" {
#endif

// Help functions
bool s21_is_number(char c);
bool s21_is_operation(char c);
bool s21_if_number_or_simple_operation(char c);
bool is_left_associative(char c);
int s21_priority_of_operations(char c);
double s21_calculate(const char* str);
char* s21_parser(const char* str);

// Process input str
char* s21_replace_ln(char* str);
char* s21_replace_trigonometric(char* str);
char* s21_replace_atrigonometric(char* str);
char* s21_processing(char* str);
bool s21_test_input_string(const char* str);

// main functions
char* s21_parse_expression(char* str);
char* replace_x_with_value(const char* str, double x);

#ifdef __cplusplus
}
#endif

#endif
