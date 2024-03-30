#ifndef WARNING_CALC_H
#define WARNING_CALC_H

#include <QDialog>

namespace Ui {
class Warning_calc;
}

class Warning_calc : public QDialog {
  Q_OBJECT

 public:
  explicit Warning_calc(QWidget *parent = nullptr);
  ~Warning_calc();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::Warning_calc *ui;
};

#endif  // WARNING_CALC_H
