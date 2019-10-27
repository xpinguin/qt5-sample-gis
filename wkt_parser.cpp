#include "wkt_parser.h"
#include <QRegularExpression>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

WKT_Parser::~WKT_Parser() {

}

WKT_Parser *WKT_Parser::parse(QString wkt) {
  WKT_Parser *ret;
  {
    WKT_Parser &pp = *(new WKT_MultiPolygon());
    if (nullptr != (ret = pp(wkt))) {
      return ret;
    }
    delete &pp; // FIXME use std::unique_ptr + finalizater
  }
  {
    WKT_Parser &pp = *(new WKT_Polygon());
    if (nullptr != (ret = pp(wkt))) {
      return ret;
    }
    delete &pp; // FIXME use std::unique_ptr + finalizater
  }
  {
    WKT_Parser &pp = *(new WKT_LineString());
    if (nullptr != (ret = pp(wkt))) {
      return ret;
    }
    delete &pp; // FIXME use std::unique_ptr + finalizater
  }
  {
    WKT_Parser &pp = *(new WKT_Line());
    if (nullptr != (ret = pp(wkt))) {
      return ret;
    }
    delete &pp; // FIXME use std::unique_ptr + finalizater
  }
  {
    WKT_Parser &pp = *(new WKT_Point());
    if (nullptr != (ret = pp(wkt))) {
      return ret;
    }
    delete &pp; // FIXME use std::unique_ptr + finalizater
  }
  return nullptr;
}

///////////
// PARSE
///////////
WKT_Parser *WKT_Point::operator()(QString wkt_part)
{
  static QRegularExpression re(R"(POINT\(([0-9\.]+) ([0-9\.]+)\))");
  // --
  auto m = re.match(wkt_part);
  if (!m.hasMatch()) {
    return nullptr;
  }
  // --
  this->lat = m.captured(1).toDouble();
  this->lon = m.captured(2).toDouble();
  return this;
}

WKT_Parser *WKT_Line::operator()(QString wkt_part)
{
  return nullptr; // TODO
}

WKT_Parser *WKT_LineString::operator()(QString wkt_part)
{
  return nullptr; // TODO
}

WKT_Parser *WKT_Polygon::operator()(QString wkt_part)
{
  return nullptr; // TODO
}

WKT_Parser *WKT_MultiPolygon::operator()(QString wkt_part)
{
  return nullptr; // TODO
}

///////////
// DRAW
///////////
void WKT_Point::draw(QGraphicsView *pane) {
  QGraphicsScene *scn = new QGraphicsScene();
  scn->addText(QString::asprintf("(WxH): %.9f x %.9f", this->lat, this->lon))->setPos(0, 0);
  pane->setScene(scn);
}

void WKT_Line::draw(QGraphicsView *pane) {

}

void WKT_LineString::draw(QGraphicsView *pane) {

}

void WKT_Polygon::draw(QGraphicsView *pane) {

}

void WKT_MultiPolygon::draw(QGraphicsView *pane) {

}
