#ifndef WKT_PARSER_H
#define WKT_PARSER_H

#include <QString>
#include <QGraphicsView>


// Base class
class WKT_Parser
{
public:
  WKT_Parser *m_parent;

public:
  WKT_Parser() : m_parent(nullptr) { }
  WKT_Parser(WKT_Parser *parent) : m_parent(parent) { }

  virtual ~WKT_Parser();

  static WKT_Parser *parse(QString wkt);

  virtual WKT_Parser *operator()(QString wkt_part) = 0;
  virtual void draw(QGraphicsView *pane) = 0;
};

// POINT(x y)
class WKT_Point : public WKT_Parser {
public:
  WKT_Point() = default;
  WKT_Point(WKT_Parser *parent) : WKT_Parser(parent) { }

  virtual WKT_Parser *operator()(QString wkt_part);
  virtual void draw(QGraphicsView *pane);
};

// LINE
class WKT_Line : public WKT_Parser {
public:
  WKT_Line() = default;
  WKT_Line(WKT_Parser *parent) : WKT_Parser(parent) { }

  virtual WKT_Parser *operator()(QString wkt_part);
  virtual void draw(QGraphicsView *pane);
};

// LINESTRING
class WKT_LineString : public WKT_Parser {
public:
  WKT_LineString() = default;
  WKT_LineString(WKT_Parser *parent) : WKT_Parser(parent) { }

  virtual WKT_Parser *operator()(QString wkt_part);
  virtual void draw(QGraphicsView *pane);
};

// POLYGON
class WKT_Polygon : public WKT_Parser {
public:
  WKT_Polygon() = default;
  WKT_Polygon(WKT_Parser *parent) : WKT_Parser(parent) { }

  virtual WKT_Parser *operator()(QString wkt_part);
  virtual void draw(QGraphicsView *pane);
};

// MULTIPOLYGON
class WKT_MultiPolygon : public WKT_Parser {
public:
  WKT_MultiPolygon() = default;
  WKT_MultiPolygon(WKT_Parser *parent) : WKT_Parser(parent) { }

  virtual WKT_Parser *operator()(QString wkt_part);
  virtual void draw(QGraphicsView *pane);
};


#endif // WKT_PARSER_H
