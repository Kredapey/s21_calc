#include "add_x.h"

#include "ui_add_x.h"

add_x::add_x(QWidget *parent) : QDialog(parent), ui(new Ui::add_x) {
  ui->setupUi(this);
}

add_x::~add_x() { delete ui; }

void add_x::on_Enter_clicked() { close(); }
