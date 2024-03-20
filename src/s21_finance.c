#include "s21_finance.h"

void calculate_annuity(InputStruct InputCredit, OutputStruct* OutputCredit) {
  double i = InputCredit.rate / 12 / 100.0;
  month_payment(InputCredit, OutputCredit, i);
  OutputCredit->totalpayment = OutputCredit->monthly_payment * InputCredit.term;
  OutputCredit->overpayment = OutputCredit->totalpayment - InputCredit.amount;
  round_me(&OutputCredit->monthly_payment);
  round_me(&OutputCredit->totalpayment);
  round_me(&OutputCredit->overpayment);
}

void month_payment(InputStruct InputCredit, OutputStruct* OutputCredit,
                   double i) {
  OutputCredit->monthly_payment =
      (i * pow(i + 1, InputCredit.term) / (pow(1 + i, InputCredit.term) - 1)) *
      InputCredit.amount;
}

void calculate_diff(InputStruct InputCredit, OutputStruct* OutputCredit) {
  double how_much = InputCredit.amount;
  for (int i = 0; i < (int)InputCredit.term; i++) {
    OutputCredit->totalpayment += InputCredit.amount / InputCredit.term +
                                  how_much * InputCredit.rate / 100.;
    how_much -= InputCredit.amount / InputCredit.term;
  }
  OutputCredit->monthly_payment = OutputCredit->totalpayment / InputCredit.term;
  OutputCredit->overpayment = OutputCredit->totalpayment - InputCredit.amount;
  round_me(&OutputCredit->monthly_payment);
  round_me(&OutputCredit->totalpayment);
  round_me(&OutputCredit->overpayment);
}

/*DEPOSIT*/

void deposit_calc(InputDepositStruct InputDeposit,
                  OutputDepositStruct* OutputDeposit) {
  if (InputDeposit.capitalization == 0) {
    deposit_calc_nocapitalization(InputDeposit, OutputDeposit);
  } else {
    deposit_calc_capitalization(InputDeposit, OutputDeposit);
  }
}

void deposit_calc_nocapitalization(InputDepositStruct InputDeposit,
                                   OutputDepositStruct* OutputDeposit) {
  OutputDeposit->accrued_interest =
      percentage_increase(InputDeposit.deposit_amount,
                          InputDeposit.interest_rate, InputDeposit.term);
  OutputDeposit->deposit_amount =
      InputDeposit.deposit_amount + OutputDeposit->accrued_interest;
  if (InputDeposit.replenish_type != 0) {
    dep_noCap_replen(InputDeposit, OutputDeposit);
  }
  OutputDeposit->tax_amount =
      InputDeposit.tax_rate / 100.0 * OutputDeposit->accrued_interest;
  OutputDeposit->accrued_interest -= OutputDeposit->tax_amount;
  OutputDeposit->deposit_amount -= OutputDeposit->tax_amount;
}

void dep_noCap_replen(InputDepositStruct InputDeposit,
                      OutputDepositStruct* OutputDeposit) {
  for (int push_freq = InputDeposit.replenish_type;
       push_freq < InputDeposit.term;
       push_freq += InputDeposit.replenish_type) {
    OutputDeposit->accrued_interest += percentage_increase(
        InputDeposit.replenish, InputDeposit.interest_rate, push_freq);
    OutputDeposit->deposit_amount +=
        percentage_increase(InputDeposit.replenish, InputDeposit.interest_rate,
                            push_freq) +
        InputDeposit.replenish;
  }
}

void deposit_calc_capitalization(InputDepositStruct InputDeposit,
                                 OutputDepositStruct* OutputDeposit) {
  int const_cap = InputDeposit.capitalization;
  OutputDeposit->accrued_interest = 0.;
  double accrued = 0.;
  int replenishment_plus = 0.;
  double doest_fit = 0.;
  for (; InputDeposit.capitalization <= InputDeposit.term;
       InputDeposit.capitalization += const_cap) {
    if (InputDeposit.replenish_type <= const_cap + replenishment_plus &&
        InputDeposit.replenish_type != 0) {
      for (int push_freq = InputDeposit.replenish_type;
           push_freq <= const_cap + replenishment_plus;
           push_freq += InputDeposit.replenish_type) {
        InputDeposit.deposit_amount += InputDeposit.replenish;
        doest_fit += InputDeposit.replenish;
      }
      replenishment_plus = 0;
    } else if (InputDeposit.replenish_type != 0 &&
               InputDeposit.replenish_type > const_cap + replenishment_plus) {
      replenishment_plus += const_cap;
    }
    accrued = percentage_increase(InputDeposit.deposit_amount,
                                  InputDeposit.interest_rate, const_cap);
    InputDeposit.deposit_amount += accrued;
    OutputDeposit->accrued_interest += accrued;
  }
  doest_fit = InputDeposit.replenish * InputDeposit.term - doest_fit;
  OutputDeposit->deposit_amount += InputDeposit.deposit_amount + doest_fit;
  OutputDeposit->tax_amount =
      InputDeposit.tax_rate / 100.0 * OutputDeposit->accrued_interest;
  OutputDeposit->accrued_interest -= OutputDeposit->tax_amount;
  OutputDeposit->deposit_amount -= OutputDeposit->tax_amount;
}

double percentage_increase(double deposit_amount, double interest_rate,
                           int term) {
  const int mounth_arr[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int mounth_days = 0;
  for (int i = 0, j = 0; i < term; i++) {
    if (j == 12) {
      j = 0;
    }
    mounth_days += mounth_arr[j++];
  }
  return deposit_amount * interest_rate * ((double)mounth_days / 365) / 100.0;
}
void round_me(double* value) { *value = round(*value * 100.0) / 100.0; }
