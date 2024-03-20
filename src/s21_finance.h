#ifndef SRC_FINANCE_CALC_H
#define SRC_FINANCE_CALC_H

#include <math.h>
#include <stdio.h>

#include "s21_additional.h"

typedef struct {
  double amount;
  int term;
  double rate;
} InputStruct;

typedef struct {
  double monthly_payment;
  double overpayment;
  double totalpayment;
} OutputStruct;

typedef struct {
  double deposit_amount;
  int term;
  double interest_rate;
  double key_rate;
  double tax_rate;
  int replenish_type;
  double replenish;
  int periodicity_of_payment;
  int capitalization;  // 1 - месяц, 2 - четверть, 3 - годик, 0 - нет

} InputDepositStruct;

typedef struct {
  double accrued_interest;
  double tax_amount;
  double deposit_amount;
} OutputDepositStruct;

void calculate_annuity(InputStruct InputCredit, OutputStruct* OutputCredit);
void month_payment(InputStruct InputCredit, OutputStruct* OutputCredit,
                   double i);
void calculate_diff(InputStruct InputCredit, OutputStruct* OutputCredit);

/*Дополнительные функции*/

void round_me(double* value);

/*Депозит*/
void deposit_calc(InputDepositStruct InputDeposit,
                  OutputDepositStruct* OutputDeposit);
void deposit_calc_capitalization(InputDepositStruct InputDeposit,
                                 OutputDepositStruct* OutputDeposit);
void deposit_calc_nocapitalization(InputDepositStruct InputDeposit,
                                   OutputDepositStruct* OutputDeposit);
void dep_noCap_replen(InputDepositStruct InputDeposit,
                      OutputDepositStruct* OutputDeposit);

double percentage_increase(double deposit_amount, double interest_rate,
                           int term);
#endif  // SRC_FINANCE_CALC_H
