#include "s21_stack.h"

#include <stdio.h>
#include <stdlib.h>

void s21_stack_operations_push(s21_stack_operations** stack, const char value) {
  s21_stack_operations* tmp = malloc(sizeof(*tmp));
  tmp->value = value;
  tmp->next = *stack;
  *stack = tmp;
}

void s21_stack_operations_pop(s21_stack_operations** stack, char* value) {
  if (*stack != NULL) {
    *value = (*stack)->value;
    s21_stack_operations* temp = *stack;
    *stack = (*stack)->next;
    free(temp);
  }
}

void s21_stack_check_operation(s21_stack_operations* stack, char* value) {
  if (stack) {
    *value = (stack)->value;
  }
}

int s21_stack_operations_is_null(const s21_stack_operations* stack) {
  return stack == NULL;
}

void s21_stack_numbers_push(s21_stack_numbers** stack, const double value) {
  s21_stack_numbers* tmp = malloc(sizeof(*tmp));
  tmp->value = value;
  tmp->next = *stack;
  *stack = tmp;
}

void s21_stack_numbers_pop(s21_stack_numbers** stack, double* value) {
  if (*stack) {
    s21_stack_numbers* temp = *stack;
    *value = (*stack)->value;
    (*stack) = (*stack)->next;
    free(temp);
  }
}
