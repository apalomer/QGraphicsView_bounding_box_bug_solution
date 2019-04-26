#include "customgraphicspixmapitem.h"

CustomGraphicsPixmapItem::CustomGraphicsPixmapItem(BB_TYPE bb_type, QGraphicsItem* parent)
  : QGraphicsPixmapItem(parent), bb_type_(bb_type)
{
}
CustomGraphicsPixmapItem::CustomGraphicsPixmapItem(const QPixmap& pixmap, BB_TYPE bb_type, QGraphicsItem* parent)
  : QGraphicsPixmapItem(pixmap, parent), bb_type_(bb_type)
{
}

QRectF CustomGraphicsPixmapItem::boundingRect() const
{
  if (bb_type_ & BB_TYPE_QT)
  {
    return QGraphicsPixmapItem::boundingRect();
  }
  else if (bb_type_ & BB_TYPE_CUSTOM)
  {
    if (QGraphicsPixmapItem::pixmap().isNull())
      return QRectF();
    QSizeF szf(QGraphicsPixmapItem::pixmap().size().width(), QGraphicsPixmapItem::pixmap().size().height());
    if (QGraphicsPixmapItem::flags() & ItemIsSelectable)
    {
      qreal pw = 1.0;
      return QRectF(QGraphicsPixmapItem::offset(), szf / QGraphicsPixmapItem::pixmap().devicePixelRatio())
          .adjusted(-pw / 2, -pw / 2, pw / 2, pw / 2);
    }
    else
    {
      return QRectF(QGraphicsPixmapItem::offset(), szf / QGraphicsPixmapItem::pixmap().devicePixelRatio());
    }
  }
}

void CustomGraphicsPixmapItem::setBoundingBoxComputationMethod(BB_TYPE bb_type)
{
  bb_type_ = bb_type;
  update();
}
