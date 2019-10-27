#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QtSql>

struct GeoNative {
  QString _wkt;
  int _row_id;
};

class MainWindow : public QMainWindow, private Ui::MainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);

  QSqlDatabase m_db;

signals:
  void geoWKT(GeoNative);

private slots:
  void on_btnExecSQL_clicked();
  void on_MainWindow_geoWKT(GeoNative geo); // TODO: place into the GraphicalArea subclass
};

#endif // MAINWINDOW_H
