#include "smartcalc.h"

smartcalc::smartcalc(QWidget* parent) : QWidget(parent), ui(new Ui::smartcalc) {
  ui->setupUi(this);
  connect(ui->point, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->digit_0, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->digit_1, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->digit_2, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->digit_3, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->digit_4, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->digit_5, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->digit_6, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->digit_7, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->digit_8, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->digit_9, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->left_bracket, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->right_bracket, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->button_C, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->pushButton_plu, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->pushButton_min, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->pushButton_mul, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->pushButton_div, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->pushButton_sqr, SIGNAL(released()), this, SLOT(ButtonPress()));
  connect(ui->pushButton_percent, SIGNAL(released()), this,
          SLOT(ButtonPress()));
}

smartcalc::~smartcalc() { delete ui; }

void smartcalc::ButtonPress() {
  QPushButton* ButtonInform = (QPushButton*)sender();
  ui->LineEdit->setText(ui->LineEdit->text() + ButtonInform->text());
}

void smartcalc::on_pushButton_ln_clicked() {
  ui->LineEdit->setText(ui->LineEdit->text() + "ln()");
}

void smartcalc::on_pushButton_log_clicked() {
  ui->LineEdit->setText(ui->LineEdit->text() + "log()");
}

void smartcalc::on_pushButton_tan_clicked() {
  ui->LineEdit->setText(ui->LineEdit->text() + "tan()");
}

void smartcalc::on_pushButton_atan_clicked() {
  ui->LineEdit->setText(ui->LineEdit->text() + "atan()");
}

void smartcalc::on_pushButton_cos_clicked() {
  ui->LineEdit->setText(ui->LineEdit->text() + "cos()");
}

void smartcalc::on_pushButton_acos_clicked() {
  ui->LineEdit->setText(ui->LineEdit->text() + "acos()");
}

void smartcalc::on_pushButton_sin_clicked() {
  ui->LineEdit->setText(ui->LineEdit->text() + "sin()");
}

void smartcalc::on_pushButton_asin_clicked() {
  ui->LineEdit->setText(ui->LineEdit->text() + "asin()");
}

void smartcalc::on_pushButton_sqrt_clicked() {
  ui->LineEdit->setText(ui->LineEdit->text() + "sqrt()");
}

void smartcalc::on_button_C_clicked() {
  ui->LineEdit->clear();
  ui->LineEdit_2->clear();
}

void smartcalc::on_button_back_clicked() {
  QString StringInLineEdit = ui->LineEdit->text();
  StringInLineEdit.chop(1);
  ui->LineEdit->setText(StringInLineEdit);
}

char* smartcalc::type_conversion(int* error) {
  QString StringInLineEdit =
      check_pointers(ui->LineEdit->text()).toUtf8().constData();
  QByteArray invStringBite = StringInLineEdit.toUtf8();
  const char* WorkConstStr = invStringBite.constData();
  char* WorkStr = (char*)WorkConstStr;
  char* post_notation = smartcalc_f(WorkStr, error);
  return post_notation;
}

void smartcalc::on_equal_sign_clicked() {
  int error = OK;
  double result = 0.;
  char* post_notation = type_conversion(&error);
  double X = check_pointers(ui->LineEdit_2->text()).toDouble();
  if (error != MAL_EXP) {
    result = smartcalc_calculation(post_notation, X, &error);
  }
  calculation_result(error);
  if (error == OK) {
    ui->LineEdit->setText(QString::fromStdString(std::to_string(result)));
  }
  free(post_notation);
}

void smartcalc::calculation_result(int error) {
  if (error == MAL_EXP) {
    ui->LineEdit->setText("Malformed Expression");
  }
}

void smartcalc::on_Create_Plot_button_clicked() {
  int error = OK;
  char* post_notation = type_conversion(&error);

  if (error != MAL_EXP) {
    double xMin = check_pointers(ui->lineEdit_Xmin->text()).toDouble();
    double xMax = check_pointers(ui->lineEdit_Xmax->text()).toDouble();

    double yMin = check_pointers(ui->lineEdit_Ymin->text()).toDouble();
    double yMax = check_pointers(ui->lineEdit_Ymax->text()).toDouble();

    xBegin = xMin <= -1000000 ? -1000000 : xMin;
    xEnd = xMax >= 1000000 ? 1000000 : xMax;

    h = 0.1;

    for (X = xBegin; X < xEnd; X += h) {
      x.push_back(X);
      y.push_back(smartcalc_calculation(post_notation, X, &error));
    }

    ui->graph_widget->xAxis->setRange(xMin, xMax);
    ui->graph_widget->yAxis->setRange(yMin, yMax);

    ui->graph_widget->addGraph();
    ui->graph_widget->graph(0)->setData(x, y);
    ui->graph_widget->replot();

    x.clear();
    y.clear();
  }
  calculation_result(error);
  free(post_notation);
}

void smartcalc::on_copy_digit_2_clicked() {
  ui->LineEdit->setText(ui->LineEdit->text() + "x");
}
