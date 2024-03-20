#ifndef FIN_DEPOSIT_H
#define FIN_DEPOSIT_H

#include <QWidget>

#include "finances.h"

extern "C" {
#include "../s21_finance.h"
};

namespace Ui {
class Fin_Deposit;
}

class Fin_Deposit : public QWidget {
  Q_OBJECT

 public:
  explicit Fin_Deposit(QWidget *parent = nullptr);
  ~Fin_Deposit();

 private slots:
  void on_Calculate_clicked();

  void on_box_capitalisation_currentTextChanged(const QString &arg1);

  void on_box_replenishment_currentTextChanged(const QString &arg1);

  void on_Clear_clicked();

 private:
  Ui::Fin_Deposit *ui;
};

#endif  // FIN_DEPOSIT_H
