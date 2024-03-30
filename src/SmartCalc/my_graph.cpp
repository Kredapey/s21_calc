#include "my_graph.h"

#include "ui_my_graph.h"

my_graph::my_graph(QWidget *parent) : QDialog(parent), ui(new Ui::my_graph) {
  ui->setupUi(this);
}

my_graph::~my_graph() { delete ui; }
