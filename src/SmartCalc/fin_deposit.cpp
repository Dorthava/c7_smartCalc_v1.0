#include "fin_deposit.h"

#include "ui_fin_deposit.h"

Fin_Deposit::Fin_Deposit(QWidget *parent)
    : QWidget(parent), ui(new Ui::Fin_Deposit) {
  ui->setupUi(this);
  ui->radioButton->hide();
  ui->radioButton_2->hide();
  ui->radioButton_3->hide();
  ui->radioButton_4->hide();
  ui->radioButton_5->hide();
  ui->radioButton_6->hide();
  ui->lineEdit_repl->hide();
}

Fin_Deposit::~Fin_Deposit() { delete ui; }

void Fin_Deposit::on_Calculate_clicked() {
  InputDepositStruct DepositInfo;
  OutputDepositStruct OutputInfo;
  DepositInfo.deposit_amount = check_pointers(ui->lineEdit_dep->text()).toInt();
  DepositInfo.term = check_pointers(ui->lineEdit_period->text()).toInt();
  DepositInfo.interest_rate =
      check_pointers(ui->lineEdit_rate->text()).toDouble();
  DepositInfo.tax_rate =
      check_pointers(ui->lineEdit_tax_kind->text()).toDouble();
  DepositInfo.capitalization = 0;
  if (ui->radioButton_4->isVisible()) {
    if (ui->radioButton_4->isChecked()) {
      DepositInfo.capitalization = 1;
    } else if (ui->radioButton_5->isChecked()) {
      DepositInfo.capitalization = 3;
    } else {
      DepositInfo.capitalization = 12;
    }
  }
  DepositInfo.replenish_type = 0;
  if (ui->radioButton->isVisible()) {
    if (ui->radioButton->isChecked()) {
      DepositInfo.replenish_type = 1;
    } else if (ui->radioButton_2->isChecked()) {
      DepositInfo.replenish_type = 3;
    } else {
      DepositInfo.replenish_type = 12;
    }
    DepositInfo.replenish =
        check_pointers(ui->lineEdit_repl->text()).toDouble();
  }
  DepositInfo.periodicity_of_payment =
      check_pointers(ui->box_payout->currentText()).toInt();
  deposit_calc(DepositInfo, &OutputInfo);
  ui->lineEdit_am_money->setText(QString::number(OutputInfo.deposit_amount));
  ui->lineEdit_am_rate->setText(QString::number(OutputInfo.accrued_interest));
  ui->lineEdit_am_tax->setText(QString::number(OutputInfo.tax_amount));
}

void Fin_Deposit::on_box_capitalisation_currentTextChanged(
    const QString &arg1) {
  if (arg1 == "Yes") {
    ui->radioButton_4->show();
    ui->radioButton_5->show();
    ui->radioButton_6->show();
  } else {
    ui->radioButton_4->hide();
    ui->radioButton_5->hide();
    ui->radioButton_6->hide();
  }
}

void Fin_Deposit::on_box_replenishment_currentTextChanged(const QString &arg1) {
  if (arg1 == "Yes") {
    ui->radioButton->show();
    ui->radioButton_2->show();
    ui->radioButton_3->show();
    ui->lineEdit_repl->show();
  } else {
    ui->radioButton->hide();
    ui->radioButton_2->hide();
    ui->radioButton_3->hide();
    ui->lineEdit_repl->hide();
  }
}

void Fin_Deposit::on_Clear_clicked() {
  ui->lineEdit_dep->setText("");
  ui->lineEdit_period->setText("");
  ui->lineEdit_repl->setText("");
  ui->lineEdit_tax_kind->setText("");
  ui->lineEdit_rate->setText("");
  if (ui->lineEdit_repl->isVisible()) {
    ui->lineEdit_repl->setText("");
  }
  ui->lineEdit_am_rate->setText("");
  ui->lineEdit_am_money->setText("");
  ui->lineEdit_am_tax->setText("");
}
