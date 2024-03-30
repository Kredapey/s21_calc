#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_min, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_bracket_open, SIGNAL(clicked()), this,
          SLOT(operations()));
  connect(ui->pushButton_bracket_close, SIGNAL(clicked()), this,
          SLOT(operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(funcs()));
  op_bracket = 0;
  cl_bracket = 0;
  dot_counter = 0;
  QDoubleValidator *doubler = new QDoubleValidator(0);
  QIntValidator *inter = new QIntValidator(0);
  ui->x_max->setValidator(doubler);
  ui->x_min->setValidator(doubler);
  ui->y_max->setValidator(doubler);
  ui->x_min->setValidator(doubler);
  ui->time_edit->setValidator(inter);
  ui->full_sum_edit->setValidator(doubler);
  ui->perc_edit->setValidator(doubler);
  setlocale(LC_NUMERIC, "C");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  check_new_res();
  QPushButton *button = (QPushButton *)sender();
  QString new_res = ui->result->text() + button->text();
  ui->result->setText(new_res);
}

void MainWindow::operations() {
  dot_counter = 0;
  check_new_res();
  QPushButton *button = (QPushButton *)sender();
  QString new_res;
  new_res = ui->result->text();
  if (button->text() == "+") {
    if (!(ui->result->text().endsWith("+")) &&
        !(ui->result->text().endsWith("-")) &&
        !(ui->result->text().endsWith("*")) &&
        !(ui->result->text().endsWith("/")) &&
        !(ui->result->text().endsWith("d")) &&
        !(ui->result->text().endsWith("^")))
      if (!(ui->result->text().isEmpty())) new_res += "+";
  } else if (button->text() == "-") {
    if (!(ui->result->text().endsWith("+")) &&
        !(ui->result->text().endsWith("-")) &&
        !(ui->result->text().endsWith("*")) &&
        !(ui->result->text().endsWith("/")) &&
        !(ui->result->text().endsWith("d")) &&
        !(ui->result->text().endsWith("^")))
      new_res += "-";
  } else if (button->text() == "*") {
    if (!(ui->result->text().endsWith("+")) &&
        !(ui->result->text().endsWith("-")) &&
        !(ui->result->text().endsWith("*")) &&
        !(ui->result->text().endsWith("/")) &&
        !(ui->result->text().endsWith("(")) &&
        !(ui->result->text().endsWith("d")) &&
        !(ui->result->text().endsWith("^")))
      if (!(ui->result->text().isEmpty())) new_res += "*";
  } else if (button->text() == "/") {
    if (!(ui->result->text().endsWith("+")) &&
        !(ui->result->text().endsWith("-")) &&
        !(ui->result->text().endsWith("*")) &&
        !(ui->result->text().endsWith("/")) &&
        !(ui->result->text().endsWith("(")) &&
        !(ui->result->text().endsWith("d")) &&
        !(ui->result->text().endsWith("^")))
      if (!(ui->result->text().isEmpty())) new_res += "/";
  } else if (button->text() == "mod") {
    if (!(ui->result->text().endsWith("+")) &&
        !(ui->result->text().endsWith("-")) &&
        !(ui->result->text().endsWith("*")) &&
        !(ui->result->text().endsWith("/")) &&
        !(ui->result->text().endsWith("(")) &&
        !(ui->result->text().endsWith("d")) &&
        !(ui->result->text().endsWith("^")))
      if (!(ui->result->text().isEmpty())) new_res += "mod";
  } else if (button->text() == "(") {
    if (!(ui->result->text().endsWith(")")) &&
        !(ui->result->text().endsWith("x")) &&
        !(ui->result->text().endsWith("0")) &&
        !(ui->result->text().endsWith("1")) &&
        !(ui->result->text().endsWith("2") &&
          !(ui->result->text().endsWith("3"))) &&
        !(ui->result->text().endsWith("4")) &&
        !(ui->result->text().endsWith("5")) &&
        !(ui->result->text().endsWith("6")) &&
        !(ui->result->text().endsWith("7")) &&
        !(ui->result->text().endsWith("8")) &&
        !(ui->result->text().endsWith("9"))) {
      op_bracket++;
      new_res += "(";
    }
  } else if (button->text() == ")") {
    if (!(ui->result->text().endsWith("+")) &&
        !(ui->result->text().endsWith("-")) &&
        !(ui->result->text().endsWith("*")) &&
        !(ui->result->text().endsWith("/")) &&
        !(ui->result->text().endsWith("(")) &&
        !(ui->result->text().endsWith("d")) &&
        !(ui->result->text().endsWith("^")))
      if (!(ui->result->text().isEmpty()))
        if (cl_bracket < op_bracket) {
          new_res += ")";
          cl_bracket++;
        }
  } else if (button->text() == "^") {
    if (!(ui->result->text().endsWith("+")) &&
        !(ui->result->text().endsWith("-")) &&
        !(ui->result->text().endsWith("*")) &&
        !(ui->result->text().endsWith("/")) &&
        !(ui->result->text().endsWith("(")) &&
        !(ui->result->text().endsWith("d")) &&
        !(ui->result->text().endsWith("^")))
      if (!(ui->result->text().isEmpty())) new_res += "^";
  }
  ui->result->setText(new_res);
}

void MainWindow::on_pushButton_dot_clicked() {
  check_new_res();
  if (dot_counter == 0) {
    if (ui->result->text().endsWith("0") || ui->result->text().endsWith("1") ||
        ui->result->text().endsWith("2") || ui->result->text().endsWith("3") ||
        ui->result->text().endsWith("4") || ui->result->text().endsWith("5") ||
        ui->result->text().endsWith("6") || ui->result->text().endsWith("7") ||
        ui->result->text().endsWith("8") || ui->result->text().endsWith("9")) {
      ui->result->setText(ui->result->text() + '.');
      dot_counter++;
    }
  }
}

void MainWindow::on_pushButton_clear_clicked() {
  dot_counter = 0;
  ui->result->clear();
}

void MainWindow::on_pushButton_equal_clicked() {
  if (op_bracket != cl_bracket) {
    ui->result->setText("INVALID INPUT");
    op_bracket = 0;
    cl_bracket = 0;
    res_count++;
  } else {
    dot_counter = 0;
    if (ui->result->text().contains("x")) {
      QString new_string = ui->result->text();
      Dialog_x x;
      x.setModal(true);
      x.exec();
      QString dest = x.getX();
      new_string.replace("x", dest);
      ui->result->setText(new_string);
    }
    char *str = new char(ui->result->text().length());
    QByteArray arr = ui->result->text().toLatin1();
    strlcpy(str, arr, ui->result->text().length() + 1);
    double res = main_func(str, str);
    QString new_res = QString::number(res);
    ui->result->clear();
    ui->result->setText(new_res);
    res_count++;
    delete (str);
  }
}

void MainWindow::funcs() {
  dot_counter = 0;
  check_new_res();
  QPushButton *button = (QPushButton *)sender();
  QString new_res = ui->result->text();
  new_res += button->text() + "(";
  op_bracket++;
  ui->result->setText(new_res);
}

void MainWindow::check_new_res() {
  if (res_count > 0) {
    res_count = 0;
    on_pushButton_clear_clicked();
  }
}

void MainWindow::on_pushButton_Graph_clicked() {
  if (op_bracket != cl_bracket) {
    ui->result->setText("INVALID INPUT");
    op_bracket = 0;
    cl_bracket = 0;
    res_count++;
  } else {
    ui->widget->clearGraphs();
    h = 0.1;
    double y_temp = 0.0;
    x_begin = ui->x_min->text().toDouble();
    x_end = ui->x_max->text().toDouble();
    double y_min = ui->y_min->text().toDouble();
    double y_max = ui->y_max->text().toDouble();
    ui->widget->xAxis->setRange(x_begin, x_end);
    ui->widget->yAxis->setRange(y_min, y_max);
    char *str = new char(ui->result->text().length());
    QByteArray arr = ui->result->text().toLatin1();
    strlcpy(str, arr, ui->result->text().length() + 1);
    for (X = x_begin; X < x_end + h; X += h) {
      if (X > -0.1 && X < 0.1) {
        X = 0;
      }
      QString x_str = QString::number(X);
      char *str_for_x = new char(x_str.length());
      QByteArray arr_x = x_str.toLatin1();
      strlcpy(str_for_x, arr_x, x_str.length() + 1);
      x.push_back(X);
      y_temp = main_func(str, str_for_x);
      y.push_back(y_temp);
    }
    delete (str);
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    x.clear();
    y.clear();
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
    res_count++;
  }
}

void MainWindow::on_pushButton_x_clicked() {
  QString new_res = ui->result->text();
  if (!(ui->result->text().endsWith("x"))) new_res += "x";
  ui->result->setText(new_res);
}

void MainWindow::on_pushButton_clear_one_clicked() {
  QString new_result = ui->result->text();
  if (ui->result->text().endsWith(".")) dot_counter = 0;
  if (ui->result->text().endsWith("(")) op_bracket--;
  if (ui->result->text().endsWith(")")) cl_bracket--;
  new_result.chop(1);
  ui->result->setText(new_result);
}

void MainWindow::on_calc_credit_button_clicked() {
  if ((!ui->time_edit->text().isEmpty()) &&
      !(ui->full_sum_edit->text().isEmpty()) &&
      !(ui->perc_edit->text().isEmpty())) {
    if (ui->time_edit->text().toDouble() <= 0 ||
        ui->full_sum_edit->text().toDouble() <= 0 ||
        ui->perc_edit->text().toDouble() < 0) {
      Warning_calc *warning = new Warning_calc();
      warning->exec();
    } else {
      double full_sum = 0;
      int time = 0;
      double perc = 0;
      double over_payment = 0;
      double overall = 0;
      full_sum = ui->full_sum_edit->text().toDouble();
      time = ui->time_edit->text().toDouble();
      perc = ui->perc_edit->text().toDouble();
      if (ui->annuit_diff_box->currentText() == "Аннуитентный") {
        double month_payment = 0;
        annuitent_credit_calc(full_sum, time, perc, &month_payment,
                              &over_payment, &overall);
        ui->sum_month_payment->setText(QString::number(month_payment));
        ui->sum_overall_payment->setText(QString::number(overall));
        ui->sum_overpayment->setText(QString::number(over_payment));
      } else if (ui->annuit_diff_box->currentText() == "Дифференцированный") {
        double first_mon_pay = 0;
        double last_mon_pay = 0;
        different_credit_calc(full_sum, time, perc, &first_mon_pay,
                              &last_mon_pay, &over_payment, &overall);
        QString first = QString::number(first_mon_pay);
        QString last = QString::number(last_mon_pay);
        ui->sum_month_payment->setText(first + " - " + last);
        ui->sum_overall_payment->setText(QString::number(overall));
        ui->sum_overpayment->setText(QString::number(over_payment));
      }
    }
  } else {
    Warning_calc *warning = new Warning_calc();
    warning->exec();
  }
}
