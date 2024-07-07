#include "s21_calculator.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* s21_parse_expression(char* str) {
  char* processing = (char*)calloc(strlen(str), sizeof(char));
  strcpy(processing, str);
  char* process_str = s21_processing(processing);

  char* answer = (char*)malloc(50 + 1);
  if (answer == NULL) {
    return NULL;
  }
  if (process_str) {
    char* polish_str = s21_parser(process_str);
    snprintf(answer, 50 + 1, "%lf", s21_calculate(polish_str));
    free(polish_str);
  } else {
    strcpy(answer, "ERROR");
  }
  free(process_str);
  return answer;
}

char* replace_x_with_value(const char* str, double x) {
  char* processing = (char*)calloc(strlen(str), sizeof(char));
  strcpy(processing, str);

  char* process_str = s21_processing(processing);

  setlocale(LC_NUMERIC, "C");

  int max_new_len = strlen(process_str) * 20;
  char* new_str = (char*)malloc(max_new_len + 1);
  if (new_str == NULL) {
    perror("Unable to allocate memory");
    exit(EXIT_FAILURE);
  }

  int new_str_index = 0;

  for (int i = 0; process_str[i] != '\0'; i++) {
    if (process_str[i] == 'x') {
      new_str_index += sprintf(new_str + new_str_index, "%g", x);
    } else {
      new_str[new_str_index++] = process_str[i];
    }
  }
  new_str[new_str_index] = '\0';
  free(process_str);

  new_str = (char*)realloc(new_str, strlen(new_str) + 1);
  if (new_str == NULL) {
    perror("Unable to reallocate memory");
    exit(EXIT_FAILURE);
  }

  return new_str;
}
