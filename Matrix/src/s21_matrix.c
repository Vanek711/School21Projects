#include "s21_matrix.h"

#define SUCCESS 0
#define MATRIX_FAILURE 1
#define CALCULATE_FAILURE 2

#define EQ_SUCCESS 1
#define EQ_FAILURE 0

#define Accuracy 1e-7

#define is_Valid_size(rows, columns) \
  (rows * columns > 0 ? SUCCESS : MATRIX_FAILURE)

int is_valid_matrix(matrix_t *A) {
  return (!A || !A->matrix || is_Valid_size(A->rows, A->columns))
             ? MATRIX_FAILURE
             : SUCCESS;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int memory_flag = is_Valid_size(rows, columns);
  result->rows = rows;
  result->columns = columns;
  if (memory_flag != MATRIX_FAILURE) {
    result->matrix = (double **)calloc(result->rows, sizeof(double *));
    if (!result->matrix) memory_flag = MATRIX_FAILURE;
    for (int i = 0; i < result->rows; i++) {
      result->matrix[i] = (double *)calloc(result->columns, sizeof(double));
      if (!result->matrix[i]) memory_flag = MATRIX_FAILURE;
    }
  }
  return memory_flag;
}

void s21_remove_matrix(matrix_t *A) {
  if (!is_valid_matrix(A)) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (is_valid_matrix(A) == MATRIX_FAILURE || !B) return EQ_FAILURE;
  int accuracy_flag = EQ_SUCCESS;
  if (A->columns == B->columns && A->rows == B->rows){
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > Accuracy)
          accuracy_flag = EQ_FAILURE;
      }
    }
  } else accuracy_flag = EQ_FAILURE;
  return accuracy_flag;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (is_valid_matrix(A) == MATRIX_FAILURE ||
      is_valid_matrix(B) == MATRIX_FAILURE || !result)
    return MATRIX_FAILURE;
  int success_flag = SUCCESS;
  if (A->columns == B->columns && A->rows == B->rows) {
    success_flag = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  } else
    success_flag = CALCULATE_FAILURE;
  return success_flag;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (is_valid_matrix(A) == MATRIX_FAILURE ||
      is_valid_matrix(B) == MATRIX_FAILURE || !result)
    return MATRIX_FAILURE;
  int success_flag = SUCCESS;
  if (A->columns == B->columns && A->rows == B->rows) {
    success_flag = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  } else
    success_flag = CALCULATE_FAILURE;
  return success_flag;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (is_valid_matrix(A) == MATRIX_FAILURE || result == NULL)
    return MATRIX_FAILURE;
  int success_flag = s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return success_flag;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (is_valid_matrix(A) == MATRIX_FAILURE ||
      is_valid_matrix(B) == MATRIX_FAILURE || !result)
    return MATRIX_FAILURE;
  int success_flag = SUCCESS;
  if (A->columns == B->rows) {
    success_flag = s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int k = 0; k < B->columns; k++) {
        result->matrix[i][k] = 0;
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][k] =
              A->matrix[i][j] * B->matrix[j][k] + result->matrix[i][k];
        }
      }
    }
  } else
    success_flag = CALCULATE_FAILURE;
  return success_flag;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (is_valid_matrix(A) == MATRIX_FAILURE || !result) return MATRIX_FAILURE;
  int success_flag = s21_create_matrix(A->columns, A->rows, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }
  return success_flag;
}

void set_new_matrix(matrix_t *A, int rows, int columns, matrix_t *result) {
  int i_flag = 0, j_flag = 0;
  for (int i = 0; i < result->rows; i++) {
    if (i == rows) i_flag = 1;
    for (int j = 0; j < result->columns; j++) {
      if (j == columns) j_flag = 1;
      result->matrix[i][j] = A->matrix[i + i_flag][j + j_flag];
    }
    j_flag = 0;
  }
}

double sebastou_determinant(matrix_t *A) {
  double determinant = 0;
  if (A->rows == 1) return A->matrix[0][0];
  if (A->rows == 2)
    return A->matrix[0][0] * A->matrix[1][1] -
           A->matrix[0][1] * A->matrix[1][0];
  else {
    matrix_t temp;
    s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
    int sign = 1;
    for (int i = 0; i < A->rows; i++) {
      set_new_matrix(A, i, 0, &temp);
      determinant += sign * A->matrix[i][0] * sebastou_determinant(&temp);
      sign = -sign;
    }
    s21_remove_matrix(&temp);
  }
  return determinant;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (is_valid_matrix(A) == MATRIX_FAILURE || !result) return MATRIX_FAILURE;
  int dimensions_flag = SUCCESS;
  if (A->columns == A->rows && A->rows != 1) {
    dimensions_flag = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t temp;
        int sign = pow(-1, i + j);
        s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
        set_new_matrix(A, i, j, &temp);
        result->matrix[i][j] = sign * sebastou_determinant(&temp);
        s21_remove_matrix(&temp);
      }
    }
  } else if (A->rows == 1 && A->columns == 1) {
    dimensions_flag = s21_create_matrix(A->rows, A->columns, result);
    result->matrix[0][0] = A->matrix[0][0];
  } else
    dimensions_flag = CALCULATE_FAILURE;
  return dimensions_flag;
}

int s21_determinant(matrix_t *A, double *result) {
  int flag = is_Valid_size(A->rows, A->columns);
  if (A->columns == A->rows && flag == SUCCESS) {
    *result = sebastou_determinant(A);
  } else
    flag = MATRIX_FAILURE;
  return flag;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (is_valid_matrix(A) == MATRIX_FAILURE || !result) return MATRIX_FAILURE;
  int dimensions_flag = SUCCESS;
  double determinant = sebastou_determinant(A);
  if (A->columns == A->rows && determinant != 0) {
    matrix_t temp_complements_matrix, temp_transpose_matrix;
    s21_calc_complements(A, &temp_complements_matrix);
    s21_transpose(&temp_complements_matrix, &temp_transpose_matrix);
    double temp_det = 1 / determinant;
    dimensions_flag = s21_mult_number(&temp_transpose_matrix, temp_det, result);
    s21_remove_matrix(&temp_complements_matrix);
    s21_remove_matrix(&temp_transpose_matrix);
  } else
    dimensions_flag = CALCULATE_FAILURE;
  return dimensions_flag;
}
