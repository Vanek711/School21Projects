#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_calculator.h"

int s21_priority_of_operations(char c) {
  int priority_value = 0;
  switch (c) {
    case '(':
    case ')':
      priority_value = 1;
      break;
    case '^':
      priority_value = 6;  // By experimental method found that ^ priority equal
                           // priority of trigonometric operations
      break;
    case '/':
    case '*':
    case '%':
      priority_value = 5;
      break;
    case COS:
    case SIN:
    case TAN:
    case ACOS:
    case ASIN:
    case ATAN:
    case SQRT:
    case LN:
    case LOG:
      priority_value = 6;
      break;
    case '+':
    case '-':
      priority_value = 4;
      break;
    case UPLUS:
    case UMINUS:
      priority_value = 2;
      break;
    default:
      break;
  }
  return priority_value;
}

bool s21_is_operation(char c) {
  return ((c > 39 && c < 48) || c == '^' || c == MOD || c == COS || c == SIN ||
          c == UMINUS || c == UPLUS || c == TAN || c == ACOS || c == ASIN ||
          c == ATAN || c == SQRT || c == LN || c == LOG)
             ? true
             : false;
}

bool s21_if_number_or_simple_operation(char c) {
  return ((c > 39 && c < 58) || c == '^' || c == MOD || c == 'x') ? true
                                                                  : false;
}

char* s21_replace_unary(char* str) {
  bool no_error_flag = false;
  if (str != NULL) {
    if (s21_is_operation(str[0])) {
      if (str[0] == '+')
        str[0] = UPLUS;
      else if (str[0] == '-')
        str[0] = UMINUS;
    } else
      no_error_flag = true;

    if (strlen(str) > 1) no_error_flag = true;
  }
  return (str && no_error_flag) ? str : NULL;
}

char* s21_replace_ln(char* str) {
  char* return_str = (char*)calloc(strlen(str), sizeof(char));
  if (!return_str) {
    free(str);
    return NULL;
  }
  if (strlen(str) > 2) {
    for (size_t i = 0, j = 0; i < strlen(str); i++) {
      if ((i < strlen(str) - 1) && str[i] == 'l' && str[i + 1] == 'n') {
        return_str[j++] = LN;
        i += 1;
      } else
        return_str[j++] = str[i];
    }
  } else
    strcpy(return_str, str);
  free(str);
  return return_str;
}

char* s21_replace_trigonometric(char* str) {
  char* return_str = (char*)calloc(strlen(str), sizeof(char));
  if (!return_str) {
    free(str);
    return NULL;
  }
  if (strlen(str) > 3) {
    for (size_t i = 0, j = 0; i < strlen(str); i++) {
      if ((i < strlen(str) - 2) && str[i] == 'c' && str[i + 1] == 'o' &&
          str[i + 2] == 's') {
        return_str[j++] = COS;
        i += 2;
      } else if ((i < strlen(str) - 2) && str[i] == 's' && str[i + 1] == 'i' &&
                 str[i + 2] == 'n') {
        return_str[j++] = SIN;
        i += 2;
      } else if ((i < strlen(str) - 2) && str[i] == 't' && str[i + 1] == 'a' &&
                 str[i + 2] == 'n') {
        return_str[j++] = TAN;
        i += 2;
      } else if ((i < strlen(str) - 2) && str[i] == 'l' && str[i + 1] == 'o' &&
                 str[i + 2] == 'g') {
        return_str[j++] = LOG;
        i += 2;
      } else
        return_str[j++] = str[i];
    }
  } else
    strcpy(return_str, str);
  free(str);
  return return_str;
}

char* s21_replace_atrigonometric(char* str) {
  char* return_str = (char*)calloc(strlen(str), sizeof(char));
  if (!return_str) {
    free(str);
    return NULL;
  }
  if (strlen(str) > 4) {
    for (size_t i = 0, j = 0; i < strlen(str); i++) {
      if ((i < strlen(str) - 3) && str[i] == 'a' && str[i + 1] == 'c' &&
          str[i + 2] == 'o' && str[i + 3] == 's') {
        return_str[j++] = ACOS;
        i += 3;
      } else if ((i < strlen(str) - 3) && str[i] == 'a' && str[i + 1] == 's' &&
                 str[i + 2] == 'i' && str[i + 3] == 'n') {
        return_str[j++] = ASIN;
        i += 3;
      } else if ((i < strlen(str) - 3) && str[i] == 'a' && str[i + 1] == 't' &&
                 str[i + 2] == 'a' && str[i + 3] == 'n') {
        return_str[j++] = ATAN;
        i += 3;
      } else if ((i < strlen(str) - 3) && str[i] == 's' && str[i + 1] == 'q' &&
                 str[i + 2] == 'r' && str[i + 3] == 't') {
        return_str[j++] = SQRT;
        i += 3;
      } else
        return_str[j++] = str[i];
    }
  } else
    strcpy(return_str, str);
  free(str);
  return return_str;
}

bool s21_test_input_string(const char* str) {  // add . test
  if (!str) return false;
  bool flag = true;
  for (size_t i = 0; i < strlen(str); i++) {
    if ((i < strlen(str) - 3) && str[i] == 'a' && str[i + 1] == 'c' &&
        str[i + 2] == 'o' && str[i + 3] == 's') {
      i += 3;
    } else if ((i < strlen(str) - 3) && str[i] == 'a' && str[i + 1] == 's' &&
               str[i + 2] == 'i' && str[i + 3] == 'n') {
      i += 3;
    } else if ((i < strlen(str) - 3) && str[i] == 'a' && str[i + 1] == 't' &&
               str[i + 2] == 'a' && str[i + 3] == 'n') {
      i += 3;
    } else if ((i < strlen(str) - 3) && str[i] == 's' && str[i + 1] == 'q' &&
               str[i + 2] == 'r' && str[i + 3] == 't') {
      i += 3;
    } else if ((i < strlen(str) - 2) && str[i] == 'c' && str[i + 1] == 'o' &&
               str[i + 2] == 's') {
      i += 2;
    } else if ((i < strlen(str) - 2) && str[i] == 's' && str[i + 1] == 'i' &&
               str[i + 2] == 'n') {
      i += 2;
    } else if ((i < strlen(str) - 2) && str[i] == 't' && str[i + 1] == 'a' &&
               str[i + 2] == 'n') {
      i += 2;
    } else if ((i < strlen(str) - 2) && str[i] == 'l' && str[i + 1] == 'o' &&
               str[i + 2] == 'g') {
      i += 2;
    } else if ((i < strlen(str) - 1) && str[i] == 'l' && str[i + 1] == 'n') {
      i += 1;
    } else if (s21_if_number_or_simple_operation(str[i])) {
      continue;
    } else
      flag = false;
  }
  bool point_counter = false;

  for (size_t i = 0; i < strlen(str); i++) {
    if (point_counter && str[i] == '.') flag = false;
    if (point_counter && !(str[i] > 47 && str[i] < 58)) point_counter = false;
    if (str[i] == '.') {
      if (i == 0 || i == strlen(str))
        flag = false;
      else if (!(str[i - 1] > 47 && str[i - 1] < 58))
        flag = false;
      point_counter = true;
    }
  }
  return flag;
}

char* s21_processing(char* str) {
  char* process_atrigonometric = s21_replace_atrigonometric(str);
  char* process_trigonometric =
      s21_replace_trigonometric(process_atrigonometric);
  char* process_ln = s21_replace_ln(process_trigonometric);
  char* process_unary = s21_replace_unary(process_ln);
  return process_unary;
}
