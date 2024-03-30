#ifndef DIALOG_X_H
#define DIALOG_X_H

#include <QDialog>
#include <QDoubleValidator>

namespace Ui {
class Dialog_x;
}

class Dialog_x : public QDialog {
  Q_OBJECT

 public:
  explicit Dialog_x(QWidget *parent = nullptr);
  ~Dialog_x();

 private:
  Ui::Dialog_x *ui;

 public slots:
  QString getX();

 private slots:
  void on_Enter_button_clicked();
};

#endif  // DIALOG_X_H
