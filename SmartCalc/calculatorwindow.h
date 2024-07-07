#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QWidget>

#include "ui_calculatorwindow.h"

namespace Ui {
class CalculatorWindow;
}

class CalculatorWindow : public QWidget {
  Q_OBJECT

 public:
  explicit CalculatorWindow(QWidget *parent = nullptr);
  ~CalculatorWindow();

 private:
  Ui::CalculatorWindow *ui;
};

#endif  // CALCULATORWINDOW_H
