#include <check.h>

#include "../s21_smartcalc.h"

START_TEST(test_sum) {
  char arr_input[] = "2+8";
  double result_real = 2. + 8.;
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me;
  if (error == OK) {
    result_me = smartcalc_calculation(arr_output, 0., &error);
  }
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_min) {
  char arr_input[] = "2-8";
  double result_real = 2. - 8.;
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me;
  if (error == OK) {
    result_me = smartcalc_calculation(arr_output, 0., &error);
  }
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_mul) {
  char arr_input[] = "2*8";
  double result_real = 2. * 8.;
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me;
  if (error == OK) {
    result_me = smartcalc_calculation(arr_output, 0., &error);
  }
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_div) {
  char arr_input[] = "2/8";
  double result_real = 2. / 8.;
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me;
  if (error == OK) {
    result_me = smartcalc_calculation(arr_output, 0., &error);
  }
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_M) {
  char arr_input[] = "-8";
  double result_real = -8;
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me;
  if (error == OK) {
    result_me = smartcalc_calculation(arr_output, 0., &error);
  }
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_P) {
  char arr_input[] = "+8";
  double result_real = +8;
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me;
  if (error == OK) {
    result_me = smartcalc_calculation(arr_output, 0., &error);
  }
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_P_2) {  // error
  char arr_input[] = "+5+6";
  double result_real = +5 + 6;
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me;
  if (error == OK) {
    result_me = smartcalc_calculation(arr_output, 0., &error);
  }
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_unreal_1) {
  char arr_input[] = "-5+45.8-22.1*4+11^2*(-1+2-1*4)";
  double result_real = -5 + 45.8 - 22.1 * 4 + pow(11, 2) * (-1 + 2 - 1 * 4);
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me = smartcalc_calculation(arr_output, 0., &error);
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_unreal_2) {
  char arr_input[] = "-57.234+18*3-0.0001";
  double result_real = -57.234 + 18 * 3 - 0.0001;
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me = smartcalc_calculation(arr_output, 0., &error);
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_unreal_3) {
  char arr_input[] = "999.99999+15-3.000001-0.0001*4";
  double result_real = 999.99999 + 15 - 3.000001 - 0.0001 * 4;
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me = smartcalc_calculation(arr_output, 0., &error);
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_unreal_4) {  // error
  char input[] = "0.99-1+0.999";
  double result_real = 0.99 - 1 + 0.999;
  int error = OK;
  char *arr_output = smartcalc_f(input, &error);
  double result_me = smartcalc_calculation(arr_output, 0., &error);
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_mod) {
  char arr_input[] = "89%5";
  double result_real = fmod(89, 5);
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me = smartcalc_calculation(arr_output, 0., &error);
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_sqr) {
  char arr_input[] = "89^5";
  double result_real = pow(89, 5);
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me = smartcalc_calculation(arr_output, 0., &error);
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_func_1) {
  char arr_input[] = "ln(32)";
  double result_real = log10(32);
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me = smartcalc_calculation(arr_output, 0., &error);
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_func_2) {
  char arr_input[] =
      "tan(atan(0.5))     +acos(0.05-0.003)-cos(3^(2))-"
      "ln(107-cos(sin(3.14)))";
  double result_real = tan(atan(0.5)) + acos(0.05 - 0.003) - cos(pow(3, 2)) -
                       log10(107 - cos(sin(3.14)));
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me = smartcalc_calculation(arr_output, 0., &error);
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_func_3) {
  char arr_input[] = "tan(0.2)";
  double result_real = tan(0.2);
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me = smartcalc_calculation(arr_output, 0., &error);
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_func_4) {
  char arr_input[] = "-sin(0.3)";
  double result_real = -sin(0.3);
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me = smartcalc_calculation(arr_output, 0., &error);
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_func_5) {
  char arr_input[] = "cos(sin(0.3))";
  double result_real = cos(sin(0.3));
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  double result_me = smartcalc_calculation(arr_output, 0., &error);
  free(arr_output);
  ck_assert_float_eq(result_real, result_me);
}
END_TEST

START_TEST(test_error_1) {  // error
  char arr_input[] = "-8..";
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  free(arr_output);
  ck_assert_int_eq(error, MAL_EXP);
}
END_TEST

START_TEST(test_error_2) {  // error
  char arr_input[] = "--8.";
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  ck_assert_int_eq(error, MAL_EXP);
  free(arr_output);
}
END_TEST

START_TEST(test_error_3) {  // error
  char arr_input[] = "log(-8)";
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  smartcalc_calculation(arr_output, 0., &error);
  free(arr_output);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(test_error_4) {  // error
  char arr_input[] = ".";
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  ck_assert_int_eq(error, MAL_EXP);
  free(arr_output);
}
END_TEST

START_TEST(test_error_5) {  // error
  char arr_input[] = "adel";
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  ck_assert_int_eq(error, MAL_EXP);
  free(arr_output);
}
END_TEST

START_TEST(test_error_6) {  // error
  char arr_input[] = "";
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  ck_assert_int_eq(error, MAL_EXP);
  free(arr_output);
}
END_TEST

START_TEST(test_error_7) {  // error
  char arr_input[] = "(56+67";
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  free(arr_output);
  ck_assert_int_eq(error, MAL_EXP);
}
END_TEST

START_TEST(test_error_8) {  // error
  char arr_input[] = "taan(243)";
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  free(arr_output);
  ck_assert_int_eq(error, MAL_EXP);
}
END_TEST

START_TEST(test_error_9) {  // error
  char arr_input[] = "cs(2423)";
  int error = OK;
  char *arr_output = smartcalc_f(arr_input, &error);
  free(arr_output);
  ck_assert_int_eq(error, MAL_EXP);
}
END_TEST

void calculation_tests(TCase *tc1_1) {
  tcase_add_test(tc1_1, test_sum);
  tcase_add_test(tc1_1, test_min);
  tcase_add_test(tc1_1, test_mul);
  tcase_add_test(tc1_1, test_div);
  tcase_add_test(tc1_1, test_P);
  tcase_add_test(tc1_1, test_P_2);
  tcase_add_test(tc1_1, test_M);
  tcase_add_test(tc1_1, test_unreal_1);
  tcase_add_test(tc1_1, test_unreal_2);
  tcase_add_test(tc1_1, test_unreal_3);
  tcase_add_test(tc1_1, test_unreal_4);
  tcase_add_test(tc1_1, test_mod);
  tcase_add_test(tc1_1, test_sqr);
  tcase_add_test(tc1_1, test_func_1);
  tcase_add_test(tc1_1, test_func_2);
  tcase_add_test(tc1_1, test_func_3);
  tcase_add_test(tc1_1, test_func_4);
  tcase_add_test(tc1_1, test_func_5);
  tcase_add_test(tc1_1, test_error_1);
  tcase_add_test(tc1_1, test_error_2);
  tcase_add_test(tc1_1, test_error_3);
  tcase_add_test(tc1_1, test_error_4);
  tcase_add_test(tc1_1, test_error_5);
  tcase_add_test(tc1_1, test_error_6);
  tcase_add_test(tc1_1, test_error_7);
  tcase_add_test(tc1_1, test_error_8);
  tcase_add_test(tc1_1, test_error_9);
}
int main() {
  Suite *s1 = suite_create("s21_smartcalc: ");
  TCase *tc1_1 = tcase_create("s21_smartcalc: ");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc1_1);
  calculation_tests(tc1_1);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}