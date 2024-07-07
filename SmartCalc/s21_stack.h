#ifndef S21_STACK_H
#define S21_STACK_H

typedef struct s21_stack_operations {
  char value;
  struct s21_stack_operations* next;
} s21_stack_operations;

typedef struct s21_stack_numbers {
  double value;
  struct s21_stack_numbers* next;
} s21_stack_numbers;

void s21_stack_operations_push(s21_stack_operations** stack, const char value);
void s21_stack_operations_pop(s21_stack_operations** stack, char* value);
void s21_stack_operations_clean(s21_stack_operations* stack);
void s21_stack_check_operation(s21_stack_operations* stack, char* value);
int s21_stack_operations_is_null(const s21_stack_operations* stack);

void s21_stack_numbers_push(s21_stack_numbers** stack, const double value);
void s21_stack_numbers_pop(s21_stack_numbers** stack, double* value);
void s21_stack_numbers_clean(s21_stack_numbers* stack);

#endif