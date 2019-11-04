#include "mainwindow.h"
#include <QMessageBox>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{
  setupUi(this);

  m_db = QSqlDatabase::addDatabase("QPSQL");
  m_db.setHostName("127.0.0.1");
  m_db.setDatabaseName("mosoblmap");
  m_db.setUserName("mosoblmap");
  m_db.setPassword("oblmos");

  m_pane = new GraphicsPane();
  mapView->setScene(m_pane);
  mapView->setAlignment(Qt::AlignCenter/*Qt::AlignTop|Qt::AlignLeft*/);
}

void MainWindow::on_btnExecSQL_clicked()
{
  if (!m_db.open()) {
    auto err = m_db.lastError();
    QMessageBox::critical(this, "ОШИБКА ПОДКЛЮЧЕНИЯ", err.text());
  }
  ////
  //QMessageBox::information(this, "Текст запроса", txtSQL->toPlainText());
  ////
  auto res = m_db.exec(txtSQL->toPlainText());
  {
    auto err = res.lastError();
    if (err.type() != QSqlError::NoError) {
      QMessageBox::critical(this, "ОШИБКА ВЫПОЛНЕНИЯ ЗАПРОСА", err.text());
      return;
    }
  }
  ////
  if (!res.isSelect()) {
    QMessageBox::warning(this, "", "Тип запроса не SELECT");
    return;
  }
  ////
  int rowNo = 0;
  while (res.next()) {
    rowNo++;
    // --
    auto row = res.record();
    QString rowStr;
    for (int i = 0; i < row.count(); ++i) {
      auto fld = row.field(i);
      QString fldName = row.fieldName(i);
      rowStr += QString::asprintf(
                 "[%s]: %s\n",
                 fldName.toStdString().c_str(),
                 fld.value().toString().toStdString().c_str());
    }
    // --
    {
      GeoNative geo;
      geo._row_id = rowNo;
      ///
      int geoFieldId = row.indexOf("locStr");
      if (geoFieldId >= 0) {
        geo._wkt_raw = row.field(geoFieldId).value().toString();
      } else {
        geo._wkt_raw = rowStr;
      }
      ///
      geo.wkt = WKT_Parser::parse(geo._wkt_raw);
      ///
      this->geoWKT(geo); // FIXME the whole upper scope is to be called from the ancillary widget
    }
  }
}

void MainWindow::on_MainWindow_geoWKT(GeoNative geo) {
  QMessageBox::information(this, QString::asprintf("СТРОКА: %d", geo._row_id), geo._wkt_raw);
  // --
  if (nullptr != geo.wkt) {
    geo.wkt->draw(m_pane);
  }
}
