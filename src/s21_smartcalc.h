#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_additional.h"

enum error_list { OK, MAL_EXP };
typedef struct s21_Stack s21_Stack;

struct s21_Stack {
  char data;
  double data_num;
  s21_Stack* previous_list;
};

/*реализация стека*/
void s21_push(char new_data, double new_data_num, s21_Stack** list);
char s21_pop(s21_Stack** stack);
int s21_is_empty(s21_Stack* stack);

/*реализация smartcalc*/
char* smartcalc_f(char* arr_input, int* error);
int is_number(char simb);
int is_point(char simb);
int is_operator(char simb);
int is_func(char simb);
void character_processing(char* arr, char* arr_output);
s21_Stack* operations_processing(char simb, char* arr_output, int* j,
                                 s21_Stack* stack);
int priority(char simb);
int func_adapter(char* arr, int i);

double smartcalc_calculation(char* arr_output, double x_value, int* error);
s21_Stack* number_converter(char* arr_output, int* i, s21_Stack* stack);
s21_Stack* unary_converter(char* arr_output, int* i, s21_Stack* stack);
s21_Stack* operator_calculation(char simb, s21_Stack* stack);
s21_Stack* func_calculation(char simb, s21_Stack* stack);

double s21_atof(char* arr);
/*проверка на все виды ошибок*/

int error_check(char* arr_input);
int error_point_operation(char* arr_input, int i);
int repeat_operation(char* simb, int i);
int num_around_operation(char* simb, int i);
int simbols_error_check(char* arr_input);
int brackets_errors(char* arr_input, int i, int* brackets_open,
                    int* brackets_close);
int is_true_func(char* arr_input, int* i);
int plus_minus_errors(char* arr_input, int i);