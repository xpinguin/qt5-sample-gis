#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QtSql>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);

  QSqlDatabase m_db;

private slots:
  void on_btnExecSQL_clicked();
};

#endif // MAINWINDOW_H
