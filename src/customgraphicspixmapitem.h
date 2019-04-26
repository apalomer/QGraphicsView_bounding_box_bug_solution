#ifndef CUSTOMGRAPHICSPIXMAPITEM_H
#define CUSTOMGRAPHICSPIXMAPITEM_H

#include <QGraphicsPixmapItem>

class CustomGraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
  enum BB_TYPE
  {
    BB_TYPE_QT = 1,
    BB_TYPE_CUSTOM = 2
  };

  CustomGraphicsPixmapItem(BB_TYPE bb_type = BB_TYPE_QT, QGraphicsItem* parent = 0);
  CustomGraphicsPixmapItem(const QPixmap& pixmap, BB_TYPE bb_type = BB_TYPE_QT, QGraphicsItem* parent = 0);

  virtual QRectF boundingRect() const;

  void setBoundingBoxComputationMethod(BB_TYPE bb_type);

private:
  BB_TYPE bb_type_;
};

#endif  // CUSTOMGRAPHICSPIXMAPITEM_H
