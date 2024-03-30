#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDoubleValidator>
#include <QIntValidator>
#include <QMainWindow>
#include <QMessageBox>
#include <QVector>

#include "dialog_x.h"
#include "warning_calc.h"

extern "C" {
#include "../smartCalc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  double x_begin, x_end, h, X;
  double N;
  QVector<double> x, y;
  int op_bracket;
  int cl_bracket;
  int dot_counter;
  int res_count = 0;

 private slots:
  void digits_numbers();
  void operations();
  void on_pushButton_dot_clicked();
  void on_pushButton_clear_clicked();
  void on_pushButton_equal_clicked();
  void funcs();
  void check_new_res();
  void on_pushButton_Graph_clicked();
  void on_pushButton_x_clicked();
  void on_pushButton_clear_one_clicked();
  void on_calc_credit_button_clicked();
};
#endif  // MAINWINDOW_H
