#include "dialog_x.h"

#include "ui_dialog_x.h"

Dialog_x::Dialog_x(QWidget* parent) : QDialog(parent), ui(new Ui::Dialog_x) {
  ui->setupUi(this);
  QDoubleValidator* doubler = new QDoubleValidator(0);
  ui->x_edit->setValidator(doubler);
}

Dialog_x::~Dialog_x() { delete ui; }

QString Dialog_x::getX() { return ui->x_edit->text(); }

void Dialog_x::on_Enter_button_clicked() { close(); }
