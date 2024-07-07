QT += core gui widgets printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = s21_calculator
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        calculatorwindow.cpp \
        s21_calculator.c \
        s21_polish_notation.c \
        s21_stack.c \
        s21_string_scanner.c \
        qcustomplot.cpp

HEADERS += mainwindow.h \
    calculatorwindow.h \
    s21_calculator.h \
    s21_stack.h \
    qcustomplot.h

FORMS += mainwindow.ui \
    calculatorwindow.ui

INCLUDEPATH += ./qcustomplot
