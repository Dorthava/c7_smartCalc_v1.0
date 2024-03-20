#ifndef SMARTCALC_H
#define SMARTCALC_H

#include <QVector>
#include <QWidget>

#include "finances.h"
#include "qcustomplot.h"
#include "ui_smartcalc.h"

extern "C" {
#include "../s21_smartcalc.h"
};

namespace Ui {
class smartcalc;
}

class smartcalc : public QWidget {
  Q_OBJECT

 public:
  explicit smartcalc(QWidget* parent = nullptr);
  ~smartcalc();
  char* type_conversion(int* error);
  void calculation_result(int error);

 private slots:
  void on_pushButton_ln_clicked();

  void on_pushButton_log_clicked();

  void on_pushButton_atan_clicked();

  void on_pushButton_tan_clicked();

  void on_pushButton_cos_clicked();

  void on_pushButton_acos_clicked();

  void on_pushButton_sin_clicked();

  void on_pushButton_asin_clicked();

  void on_button_C_clicked();

  void on_button_back_clicked();

  void on_pushButton_sqrt_clicked();

  void ButtonPress();

  void on_equal_sign_clicked();

  void on_Create_Plot_button_clicked();

  void on_copy_digit_2_clicked();

 private:
  Ui::smartcalc* ui;
  double xBegin, xEnd, h, X;
  int N;
  QVector<double> x, y;
};

#endif  // SMARTCALC_H
