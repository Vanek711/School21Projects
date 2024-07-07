#include "mainwindow.h"

#include "qcustomplot.h"
#include "s21_calculator.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  customPlot =
      new QCustomPlot(ui->plotWidget_2);  // Use the plotWidget_2 from the UI
  QVBoxLayout* layout = new QVBoxLayout(ui->plotWidget_2);
  layout->addWidget(customPlot);
  ui->plotWidget_2->setLayout(layout);

  connect(ui->plotButton, &QPushButton::released, this,
          &MainWindow::plot_graphic);
  connect(ui->clearButton, &QPushButton::released, ui->lineEdit,
          &QLineEdit::clear);
  connect(ui->equalButton, &QPushButton::released, this,
          &MainWindow::on_equal_pressed);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::plot_graphic() {
  customPlot->clearGraphs();

  QVector<double> x(101), y(101);

  QString expression = ui->lineEdit->text();
  char* c_expression = strdup(expression.toStdString().c_str());

  for (int i = 0; i < 101; ++i) {
    x[i] = i / 5.0 - 10;
    char* c_result = replace_x_with_value(c_expression, x[i]);
    char* result_str = s21_parse_expression(c_result);
    y[i] = strtod(result_str, NULL);
    free(c_result);
    free(result_str);
  }

  free(c_expression);

  customPlot->addGraph();
  customPlot->graph(0)->setData(x, y);
  customPlot->xAxis->setLabel("x");
  customPlot->yAxis->setLabel("y");
  customPlot->xAxis->setRange(-2, 2);
  customPlot->yAxis->setRange(-2, 2);
  customPlot->replot();
}

void MainWindow::on_equal_pressed() {
  QString expression = ui->lineEdit->text();
  char* c_expression = strdup(expression.toStdString().c_str());

  char* c_result = s21_parse_expression(c_expression);

  QString result = QString(c_result);
  free(c_expression);
  free(c_result);

  ui->lineEdit->setText(result);
}