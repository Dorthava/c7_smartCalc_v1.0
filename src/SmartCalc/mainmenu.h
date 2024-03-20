#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainMenu;
}
QT_END_NAMESPACE

class MainMenu : public QMainWindow {
  Q_OBJECT

 public:
  MainMenu(QWidget *parent = nullptr);
  ~MainMenu();

 private slots:
  void on_actionSmartCalc_triggered();
  void on_actionFinances_triggered();

  void on_actionFinances_Deposit_triggered();

 private:
  Ui::MainMenu *ui;
};
#endif  // MAINMENU_H
