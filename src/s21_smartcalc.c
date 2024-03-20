#include "s21_smartcalc.h"

char* smartcalc_f(char* arr_input, int* error) {
  char* arr_output = malloc(512 * sizeof(char));
  if (arr_input[0] != '\0') {
    *error = strlen(arr_input) > 255 && arr_input != NULL ? MAL_EXP : OK;
    space_converter(arr_input);
    *error = error_check(arr_input);
  } else {
    *error = MAL_EXP;
  }
  if (*error != MAL_EXP) {
    if (arr_output != NULL) {
      character_processing(arr_input, arr_output);
    }
  } else if (arr_output != NULL) {
    free(arr_output);
    arr_output = NULL;
  }
  return arr_output;
}

void character_processing(char* arr, char* arr_output) {
  int i = 0;
  int j = 0;
  s21_Stack* stack = NULL;
  for (; arr[i] != '\0'; i += 1) {
    if (arr[i] == '+' && (i == 0 || (i > 0 && arr[i - 1] == '('))) {
      s21_push('P', 0, &stack);
    } else if (arr[i] == '-' && (i == 0 || (i > 0 && arr[i - 1] == '('))) {
      s21_push('M', 0, &stack);
    } else if (arr[i] == '(') {
      s21_push('(', 0, &stack);
    } else if (arr[i] == ')') {
      for (; s21_is_empty(stack) == 0 && stack->data != '(';) {
        arr_output[j++] = s21_pop(&stack);
        arr_output[j++] = ' ';
      }
      if (stack->data == '(') {
        s21_pop(&stack);
      }
    } else if (is_number(arr[i]) || arr[i] == 'x' || arr[i] == '.') {
      arr_output[j++] = arr[i];
      if ((is_number(arr[i + 1]) == 1 || arr[i + 1] == '.') != 1) {
        arr_output[j++] = ' ';
      }
    } else if (is_operator(arr[i])) {
      stack = operations_processing(arr[i], arr_output, &j, stack);
    } else if (is_func(arr[i])) {
      int skip = func_adapter(arr, i);
      stack = operations_processing(arr[i], arr_output, &j, stack);
      i += skip;
    }
  }
  for (; s21_is_empty(stack) == 0;) {
    arr_output[j++] = s21_pop(&stack);
    arr_output[j++] = ' ';
    if (s21_is_empty(stack)) {
      j -= 1;
      arr_output[j] = '\0';
    }
  }
}

int func_adapter(char* arr, int i) {
  int k = 0;
  if (arr[i] == 'a' && arr[i + 1] == 'c') {
    arr[i] = 'C';
    k = 3;
  } else if (arr[i] == 'a' && arr[i + 1] == 's') {
    arr[i] = 'S';
    k = 3;
  } else if (arr[i] == 'a' && arr[i + 1] == 't') {
    arr[i] = 'T';
    k = 3;
  } else if (arr[i] == 'l' && arr[i + 1] == 'o') {
    arr[i] = 'L';
    k = 2;
  } else if (arr[i] == 'l' && arr[i + 1] == 'n') {
    arr[i] = 'l';
    k = 1;
  } else if (arr[i] == 's' && arr[i + 1] == 'q') {
    arr[i] = 'q';
    k = 3;
  } else {
    k = 2;
  }
  return k;
}

s21_Stack* operations_processing(char simb, char* arr_output, int* j,
                                 s21_Stack* stack) {
  int priority_operation = priority(simb);
  if (s21_is_empty(stack) ||
      (priority_operation == 6 && priority(stack->data) == 6)) {
    s21_push(simb, 0, &stack);
  } else if (s21_is_empty(stack) == 0) {
    if (priority_operation > priority(stack->data)) {
      s21_push(simb, 0, &stack);
    } else {
      while (s21_is_empty(stack) == 0 &&
             priority_operation <= priority(stack->data)) {
        arr_output[*j] = stack->data;
        *j += 1;
        arr_output[*j] = ' ';
        *j += 1;
        s21_pop(&stack);
      }
      s21_push(simb, 0, &stack);
    }
  }
  return stack;
}

int priority(char simb) {
  int result = 1;
  if (simb == '*' || simb == '/') {
    result = 2;
  } else if (simb == '%') {
    result = 3;
  } else if (simb == '^') {
    result = 4;
  } else if (simb == 'P' || simb == 'M') {
    result = 5;
  } else if (is_func(simb)) {
    result = 6;
  } else if (simb == '(') {
    result = -1;
  }
  return result;
}

int error_check(char* arr_input) {
  int error = OK;
  int brackets_open = 0;
  int brackets_close = 0;
  error = arr_input[0] == '\0' ? MAL_EXP : OK;
  if (simbols_error_check(arr_input) == MAL_EXP) {
    error = MAL_EXP;
  }
  for (int i = 0; arr_input[i] != '\0' && error == OK; i += 1) {
    if (arr_input[i] == ' ') {
      continue;
    } else if (repeat_operation(arr_input, i)) {
      error = MAL_EXP;
    } else if ((arr_input[i] == '-' || arr_input[i] == '+') &&
               plus_minus_errors(arr_input, i)) {
      error = MAL_EXP;
    } else if (arr_input[i] == '%' || arr_input[i] == '^' ||
               arr_input[i] == '*' || arr_input[i] == '/') {
      error = num_around_operation(arr_input, i);
    } else if (is_point(arr_input[i])) {
      error = error_point_operation(arr_input, i);
    } else if ((is_number(arr_input[i]) || arr_input[i] == 'x' ||
                arr_input[i] == '.') &&
               is_func(arr_input[i + 1])) {
      error = MAL_EXP;
    } else if (arr_input[i] == 'x' &&
               (is_number(arr_input[i - 1]) || is_number(arr_input[i + 1]))) {
      error = MAL_EXP;
    } else if (arr_input[i] == '(' || arr_input[i] == ')') {
      error = brackets_errors(arr_input, i, &brackets_open, &brackets_close);
    } else if (is_func(arr_input[i])) {
      error = is_true_func(arr_input, &i);
    }
  }
  if ((brackets_open - brackets_close) != 0) {
    error = MAL_EXP;
  }
  return error;
}

int plus_minus_errors(char* arr_input, int i) {
  int error = OK;
  if (arr_input[i + 1] == '\0') {
    error = MAL_EXP;
  }
  if (arr_input[i + 1] != '(' && is_number(arr_input[i + 1]) == 0 &&
      is_func(arr_input[i + 1]) == 0 && arr_input[i + 1] != 'x') {
    error = MAL_EXP;
  }
  return error;
}

int is_true_func(char* arr_input, int* i) {
  int error = MAL_EXP;
  const char* true_func[9] = {"sin",  "cos",  "tan",  "log", "ln",
                              "asin", "acos", "atan", "sqrt"};
  for (int j = 0; j < 9 && error; j += 1) {
    if (strncmp(true_func[j], &arr_input[*i], strlen(true_func[j])) == 0) {
      *i += strlen(true_func[j]) - 1;
      error = OK;
    }
  }
  if (arr_input[*i + 1] != '(') {
    error = MAL_EXP;
  }
  return error;
}

int simbols_error_check(char* arr_input) {
  int error = OK;
  char* simbols = "0123456789. ()+-*/^%acgilnoqrstx";
  for (int i = 0; arr_input[i] != '\0' && error != MAL_EXP; i += 1) {
    if (strchr(simbols, arr_input[i]) == NULL) {
      error = MAL_EXP;
    }
  }
  return error;
}

int error_point_operation(char* arr_input, int i) {
  int error = OK;
  int rep_point = 0;
  if (i == 0) {
    if (is_number(arr_input[i + 1]) == 0) {
      error = MAL_EXP;
    }
  }
  if (arr_input[i + 1] == '\0' && error != MAL_EXP) {
    if (is_number(arr_input[i - 1]) == 0) {
      error = MAL_EXP;
    }
  }
  if (i != 0) {
    if (is_number(arr_input[i - 1]) || is_number(arr_input[i + 1])) {
      error = OK;
    } else {
      error = MAL_EXP;
    }
  }
  for (int j = i + 1; arr_input[j] != '\0' && !rep_point; j += 1) {
    if (is_number(arr_input[j])) {
      error = OK;
    } else if (arr_input[j] == '.') {
      error = MAL_EXP;
      rep_point = 1;
    } else {
      break;
    }
  }
  return error;
}

int is_func(char simb) {
  int result = 0;
  if (simb == 'L' || simb == 'C' || simb == 'S' || simb == 'T' || simb == 'c' ||
      simb == 's' || simb == 't' || simb == 'l' || simb == 'a' || simb == 'q') {
    result = 1;
  }
  return result;
}

int repeat_operation(char* simb, int i) {
  return (is_operator(simb[i]) &&
          is_operator(
              simb[i + 1]));  // ошибка, при которой две операции идут подряд.
}

int num_around_operation(char* simb, int i) {
  int error = OK;
  if (i == 0) {
    return MAL_EXP;
  }
  if (simb[i + 1] == '\0') {
    return MAL_EXP;
  }
  if ((is_number(simb[i - 1]) || is_point(simb[i - 1]) || simb[i - 1] == ')' ||
       simb[i - 1] == 'x') &&
      (is_number(simb[i + 1]) || is_point(simb[i + 1]) || simb[i + 1] == '(' ||
       is_func(simb[i + 1]) || simb[i + 1] == 'x')) {
    error = OK;
  } else {
    error = MAL_EXP;
  }
  return error;
}

int is_number(char simb) {
  int result = 0;
  if (simb >= '0' && simb <= '9') {
    result = 1;
  }
  return result;
}

int is_point(char simb) { return simb == '.'; }

int is_operator(char simb) {
  int result = 0;
  if (simb == '+' || simb == '-' || simb == '*' || simb == '/' || simb == '%' ||
      simb == '^') {
    result = 1;
  }
  return result;
}

int brackets_errors(char* arr_input, int i, int* brackets_open,
                    int* brackets_close) {
  int error = 0;
  if (arr_input[i] == '(') {
    *brackets_open += 1;
    if (i != 0) {
      if (arr_input[i - 1] == 'x' || arr_input[i - 1] == '.' ||
          is_number(arr_input[i - 1])) {
        error = MAL_EXP;
      }
    }
  }
  if (arr_input[i] == ')') {
    *brackets_close += 1;
    if (arr_input[i + 1] != '\0') {
      if (arr_input[i + 1] == 'x' || arr_input[i + 1] == '.' ||
          is_number(arr_input[i + 1])) {
        error = MAL_EXP;
      }
    }
  }
  if (*brackets_close > *brackets_open) {
    error = MAL_EXP;
  }
  if (arr_input[i] == '(' && arr_input[i + 1] == ')') {
    error = MAL_EXP;
  }
  return error;
}

double smartcalc_calculation(char* arr_output, double x_value, int* error) {
  double result = 0;
  s21_Stack* stack = NULL;
  for (int i = 0; arr_output[i] != '\0' && *error == OK; i++) {
    if (arr_output[i] == ' ') {
      continue;
    } else if (is_number(arr_output[i])) {
      stack = number_converter(arr_output, &i, stack);
    } else if (arr_output[i] == 'P' || arr_output[i] == 'M') {
      stack = unary_converter(arr_output, &i, stack);
    } else if (is_operator(arr_output[i])) {
      stack = operator_calculation(arr_output[i], stack);
    } else if (is_func(arr_output[i])) {
      stack = func_calculation(arr_output[i], stack);
    } else if (arr_output[i] == 'x') {
      s21_push('\0', x_value, &stack);
    }
    if (stack->data == 'y') {
      *error = 1;
    }
  }
  result = stack->data_num;
  s21_pop(&stack);
  free(stack);
  stack = NULL;
  return result;
}

s21_Stack* number_converter(char* arr_output, int* i, s21_Stack* stack) {
  char* arr_trash = malloc(sizeof(char) * (strlen(arr_output) + 1));
  for (int j = 0; is_number(arr_output[*i]) || is_point(arr_output[*i]);
       *i += 1) {
    arr_trash[j++] = arr_output[*i];
    arr_trash[j] = '\0';
  }
  double new_num = 0.;
  new_num = s21_atof(arr_trash);
  s21_push('\0', new_num, &stack);
  free(arr_trash);
  return stack;
}

double s21_atof(char* arr) {
  double result = 0.;
  int i = 0, point_begunok = 0;
  int check_point = 0;
  while (arr[i] != '\0') {
    if (is_point(arr[i]) == 0) {
      result = (double)(result * 10);
      result += (double)(arr[i] - 48);
    }
    if (is_point(arr[i])) {
      check_point = 1;
    } else if (check_point) {
      point_begunok += 1;
    }
    i += 1;
  }
  if (check_point) {
    result = result / pow(10., (double)point_begunok);
  }
  return result;
}

s21_Stack* unary_converter(char* arr_output, int* i, s21_Stack* stack) {
  double number = 0.;
  if (arr_output[*i] == 'M') {
    number = stack->data_num;
    s21_pop(&stack);
    s21_push('\0', -number, &stack);
  } else {
    number = stack->data_num;
    s21_pop(&stack);
    s21_push('\0', number, &stack);
  }
  return stack;
}

s21_Stack* operator_calculation(char simb, s21_Stack* stack) {
  double result = 0.;
  double number_2 = stack->data_num;
  s21_pop(&stack);
  double number_1 = stack->data_num;
  s21_pop(&stack);
  char error = 'n';
  if (simb == '*') {
    result = number_1 * number_2;
  } else if (simb == '/') {
    result = number_1 / number_2;
  } else if (simb == '+') {
    result = number_1 + number_2;
  } else if (simb == '-') {
    result = number_1 - number_2;
  } else if (simb == '^') {
    result = pow(number_1, number_2);
  } else if (simb == '%') {
    if ((int)number_1 != number_1 || (int)number_2 != number_2) {
      error = 'y';
    }
    result = fmod(number_1, number_2);
  }
  s21_push(error, result, &stack);
  return stack;
}

s21_Stack* func_calculation(char simb, s21_Stack* stack) {
  double result = 0.;
  double number = 0.;
  number = stack->data_num;
  s21_pop(&stack);
  char error = '\0';
  if (simb == 'c') {
    result = cos(number);
  } else if (simb == 's') {
    result = sin(number);
  } else if (simb == 't') {
    result = tan(number);
  } else if (simb == 'C') {
    result = acos(number);
  } else if (simb == 'S') {
    result = asin(number);
  } else if (simb == 'T') {
    result = atan(number);
  } else if (simb == 'l') {
    result = log10(number);
    error = number < 0 ? 'y' : 'n';
  } else if (simb == 'L') {
    result = log(number);
    error = number < 0 ? 'y' : 'n';
  } else if (simb == 'q') {
    result = sqrt(number);
  }
  s21_push(error, result, &stack);
  return stack;
}
