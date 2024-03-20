#include "mainmenu.h"

#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainMenu) {
  ui->setupUi(this);
}

MainMenu::~MainMenu() { delete ui; }

void MainMenu::on_actionSmartCalc_triggered() {
  ui->stackedWidget->setCurrentIndex(0);
}

void MainMenu::on_actionFinances_triggered() {
  ui->stackedWidget->setCurrentIndex(1);
}

void MainMenu::on_actionFinances_Deposit_triggered() {
  ui->stackedWidget->setCurrentIndex(2);
}
