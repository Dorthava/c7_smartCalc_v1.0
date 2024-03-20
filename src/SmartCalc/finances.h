#ifndef FINANCES_H
#define FINANCES_H

#include <QWidget>

extern "C" {
#include "../s21_finance.h"
};

QString check_pointers(QString arr_input);

namespace Ui {
class finances;
}

class finances : public QWidget {
  Q_OBJECT

 public:
  explicit finances(QWidget *parent = nullptr);
  ~finances();

 private slots:
  void on_calculate_clicked();

  void on_clear_clicked();

 private:
  Ui::finances *ui;
};

#endif  // FINANCES_H
