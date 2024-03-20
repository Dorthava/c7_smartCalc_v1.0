#include "finances.h"

#include "ui_finances.h"

finances::finances(QWidget *parent) : QWidget(parent), ui(new Ui::finances) {
  ui->setupUi(this);
}

finances::~finances() { delete ui; }

QString check_pointers(QString arr_input) {
  for (int i = 0; i < arr_input.length(); i++) {
    if (arr_input[i] == ',') {
      arr_input[i] = '.';
    }
  }
  return arr_input;
}

void finances::on_calculate_clicked() {
  InputStruct InputCredit;
  OutputStruct OutputCredit;
  InputCredit.amount = check_pointers(ui->loan->text()).toDouble();
  InputCredit.rate = check_pointers(ui->rate->text()).toDouble();
  InputCredit.term = check_pointers(ui->month->text()).toInt();
  if (ui->type_of_credit->currentText() == "Annuity") {
    calculate_annuity(InputCredit, &OutputCredit);
  } else if (ui->type_of_credit->currentText() == "Differentiated") {
    calculate_diff(InputCredit, &OutputCredit);
  }
  ui->monthlypayment->setText(
      QString::fromStdString(std::to_string(OutputCredit.monthly_payment)));
  ui->overpayment->setText(
      QString::fromStdString(std::to_string(OutputCredit.overpayment)));
  ui->totalpayment->setText(
      QString::fromStdString(std::to_string(OutputCredit.totalpayment)));
}

void finances::on_clear_clicked() {
  ui->loan->setText("");
  ui->month->setText("");
  ui->monthlypayment->setText("");

  ui->overpayment->setText("");
  ui->rate->setText("");
  ui->totalpayment->setText("");
}
