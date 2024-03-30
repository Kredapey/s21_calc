#include "warning_calc.h"

#include "ui_warning_calc.h"

Warning_calc::Warning_calc(QWidget *parent)
    : QDialog(parent), ui(new Ui::Warning_calc) {
  ui->setupUi(this);
}

Warning_calc::~Warning_calc() { delete ui; }

void Warning_calc::on_pushButton_clicked() { close(); }
