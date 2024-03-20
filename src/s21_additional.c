#include "s21_additional.h"

void space_converter(char* arr_input) {
  int arr_size = strlen(arr_input) + 1;
  char* arr_trash = malloc(arr_size * sizeof(char));
  for (int i = 0, j = 0; arr_input[i] != '\0'; i++) {
    if (arr_input[i] != ' ') {
      arr_trash[j++] = arr_input[i];
      arr_trash[j] = '\0';
    }
  }
  memset(arr_input, '\0', strlen(arr_input));
  memcpy(arr_input, arr_trash, strlen(arr_trash));
  free(arr_trash);
}
