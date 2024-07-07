#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_calculator.h"

bool s21_is_binary_operation(const char c) {
  return c == '/' || c == '*' || c == '+' || c == '-';
}

bool is_left_associative(char c) { return c == '*' || c == '/' || c == '%'; }

bool s21_is_number(char c) {
  return ((c > 47 && c < 58) || c == '.' || c == 'x') ? true : false;
}

int s21_is_number_case(char* output_str, const char* str, int i,
                       bool* point_flag) {
  if (*str == '.') {
    *point_flag = true;
    output_str[i++] = *str;
  } else {
    output_str[i++] = *str;
  }

  return i;
}

int s21_left_bracket_case(s21_stack_operations** stack_operations,
                          const char* str, int bracket_counter) {
  s21_stack_operations_push(stack_operations, *str);
  return bracket_counter + 1;
}

int s21_right_bracket_case(s21_stack_operations** stack_operations,
                           int* bracket_counter, char* output_str, int i) {
  char temp_up_operation;
  do {
    if (s21_stack_operations_is_null(*stack_operations)) {
      *bracket_counter = -1000;  // if error return bracket fault
      break;
    }
    s21_stack_operations_pop(stack_operations, &temp_up_operation);
    if (temp_up_operation != '(') {
      output_str[i++] = temp_up_operation;  // WTF!!!!
      output_str[i++] = ' ';
    }
  } while (temp_up_operation != '(');
  *bracket_counter -= 1;
  return i;
}

char* s21_trim(char* str) {
  char* return_str = (char*)calloc(strlen(str), sizeof(char));
  if (!return_str) {
    free(str);
    return NULL;
  }
  for (size_t i = 0, j = 0; str[i] != '\0'; i++, j++) {
    if ((i < strlen(str) - 1) && (str[i + 1] == '.' && str[i] == ' ')) {
      i++;
      return_str[j] = str[i];
    } else
      return_str[j] = str[i];
  }
  free(str);
  return return_str;
}

char* s21_parser(const char* str) {
  s21_stack_operations* stack_operations = NULL;
  char* output_str =
      (char*)calloc(2 * strlen(str), sizeof(char));  // str and spaces
  int i = 0, bracket_counter = 0;
  bool bracket_error = false, point_flag = false;
  while (*str != '\0') {
    if (s21_is_number(*str)) {
      while (s21_is_number(*str)) {
        i = s21_is_number_case(output_str, str, i, &point_flag);
        str++;
      }
      str--;
      if (!point_flag) output_str[i++] = ' ';
    } else if (s21_is_operation(*str)) {
      if (point_flag) output_str[i++] = ' ';
      point_flag = false;
      if (*str == '(') {
        bracket_counter =
            s21_left_bracket_case(&stack_operations, str, bracket_counter);
      } else if (*str == ')') {
        i = s21_right_bracket_case(&stack_operations, &bracket_counter,
                                   output_str, i);
      } else {
        if (s21_stack_operations_is_null(stack_operations)) {
          s21_stack_operations_push(&stack_operations, *str);
        } else {
          if (s21_stack_operations_is_null(stack_operations)) break;
          char stack_up_operation;
          s21_stack_check_operation(stack_operations, &stack_up_operation);
          while (s21_priority_of_operations(stack_up_operation) >=
                 s21_priority_of_operations(*str)) {
            s21_stack_operations_pop(&stack_operations, &stack_up_operation);
            output_str[i++] = stack_up_operation;
            output_str[i++] = ' ';
            if (s21_stack_operations_is_null(stack_operations)) break;
            s21_stack_check_operation(stack_operations, &stack_up_operation);
          }
          s21_stack_operations_push(&stack_operations, *str);
        }
      }
    }
    str++;
  }
  while (!s21_stack_operations_is_null(stack_operations)) {
    s21_stack_operations_pop(&stack_operations, &output_str[i++]);
    output_str[i++] = ' ';
  }
  output_str[i] = '\0';
  char* return_str = s21_trim(output_str);
  return (return_str && bracket_counter == 0 && !bracket_error) ? return_str
                                                                : NULL;
}

double s21_calculate(const char* str) {
  s21_stack_numbers* stack_numbers = NULL;
  double calculate_value = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (s21_is_number(str[i])) {
      double temp_number = 0;
      int point_counter = 1;
      bool point_flag = false;
      while (s21_is_number(str[i])) {
        if (str[i] == '.') {
          point_flag = true;
          i++;
          continue;
        }
        if (point_flag) {
          temp_number += (double)(str[i] - '0') / (10 * point_counter);
          point_counter++;
        } else
          temp_number = (str[i] - '0') + (temp_number * 10);
        i++;
      }
      i--;
      s21_stack_numbers_push(&stack_numbers, temp_number);
    } else if (s21_is_operation(str[i])) {
      if (s21_is_binary_operation(str[i])) {
        double pop_number1, pop_number2, push_number = 0.0;
        s21_stack_numbers_pop(&stack_numbers, &pop_number1);
        s21_stack_numbers_pop(&stack_numbers, &pop_number2);
        switch (str[i]) {
          case '^':
            push_number = pow(pop_number2, pop_number1);
            break;
          case '%':
            push_number = (int)pop_number2 % (int)pop_number1;
            break;
          case '/':
            push_number = pop_number2 / pop_number1;
            break;
          case '*':
            push_number = pop_number2 * pop_number1;
            break;
          case '-':
            push_number = pop_number2 - pop_number1;
            break;
          case '+':
            push_number = pop_number2 + pop_number1;
            break;
          default:
            break;
        }
        s21_stack_numbers_push(&stack_numbers, push_number);
      } else {
        double pop_number, push_number = 0.0;
        s21_stack_numbers_pop(&stack_numbers, &pop_number);
        switch (str[i]) {
          case SQRT:
            push_number = pow(pop_number, 0.5);
            break;
          case COS:
            push_number = cos(pop_number);
            break;
          case SIN:
            push_number = sin(pop_number);
            break;
          case TAN:
            push_number = tan(pop_number);
            break;
          case ACOS:
            push_number = acos(pop_number);
            break;
          case ASIN:
            push_number = asin(pop_number);
            break;
          case ATAN:
            push_number = atan(pop_number);
            break;
          case UMINUS:
            push_number = -1 * pop_number;
            break;
          case UPLUS:
            push_number = pop_number;
            break;
          case LN:
            push_number = log(pop_number);
            break;
          case LOG:
            push_number = log10(pop_number);
            break;
          default:
            break;
        }
        s21_stack_numbers_push(&stack_numbers, push_number);
      }
    } else
      continue;
  }
  s21_stack_numbers_pop(&stack_numbers, &calculate_value);
  return calculate_value;
}
