#include "s21_smartcalc.h"

void s21_push(char new_data, double new_data_num, s21_Stack** list) {
  s21_Stack* new_list = malloc(sizeof(s21_Stack));
  new_list->data = new_data;
  new_list->data_num = new_data_num;
  new_list->previous_list = *list;
  *list = new_list;
}

char s21_pop(s21_Stack** stack) {
  s21_Stack* temp_stack = *stack;
  char data_res = temp_stack->data;
  *stack = temp_stack->previous_list;
  free(temp_stack);
  return data_res;
}

int s21_is_empty(s21_Stack* stack) { return stack == NULL; }