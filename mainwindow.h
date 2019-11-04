#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "graphicspane.h"
#include "wkt_parser.h"

#include <QtSql>

struct GeoNative {
  QString _wkt_raw;
  int _row_id;

  WKT_Parser *wkt;
};

class MainWindow : public QMainWindow, private Ui::MainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

  QSqlDatabase m_db;
  GraphicsPane *m_pane;

signals:
  void geoWKT(GeoNative);

private slots:
  void on_btnExecSQL_clicked();
  void on_MainWindow_geoWKT(GeoNative geo); // TODO: place into the GraphicalArea subclass
};

#endif // MAINWINDOW_H
