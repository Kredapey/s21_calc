#ifndef MY_GRAPH_H
#define MY_GRAPH_H

#include <QDialog>
#include <QVector>

namespace Ui {
class my_graph;
}

class my_graph : public QDialog {
  Q_OBJECT

 public:
  explicit my_graph(QWidget *parent = nullptr);
  ~my_graph();

 private slots:
  void on_Enter_button_clicked();

 private:
  Ui::my_graph *ui;
  double x_begin, x_end, h, X;
  int N;
  QVector<double> x, y;
};

#endif  // MY_GRAPH_H
