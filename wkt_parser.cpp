#include "wkt_parser.h"

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

WKT_Parser *WKT_Point::operator()(QString wkt_part)
{
  return nullptr; // TODO
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
