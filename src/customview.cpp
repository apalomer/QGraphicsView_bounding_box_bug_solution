#include "customview.h"

#include <QPainter>
#include <QWheelEvent>

CustomGraphicsView::CustomGraphicsView(QWidget* parent) : QGraphicsView(parent)
{
  // Set up new scene
  setScene(new QGraphicsScene);

  // Do not show scroll bars
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // Connect scene update to autoresize
  connect(scene(), &QGraphicsScene::changed, this, &CustomGraphicsView::autocomputeSceneSize);
}

void CustomGraphicsView::wheelEvent(QWheelEvent* event)
{
  // if ctrl pressed, use original functionality
  if (event->modifiers() & Qt::ControlModifier)
    QGraphicsView::wheelEvent(event);
  // Rotate scene
  else if (event->modifiers() & Qt::ShiftModifier)
  {
    if (event->delta() > 0)
    {
      rotate(1);
    }
    else
    {
      rotate(-1);
    }
  }
  // Zoom
  else
  {
    ViewportAnchor previous_anchor = transformationAnchor();
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    if (event->delta() > 0)
    {
      scale(1.1, 1.1);
    }
    else
    {
      scale(0.9, 0.9);
    }
    setTransformationAnchor(previous_anchor);
  }
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
  QGraphicsView::mouseMoveEvent(event);
  if (event->buttons() & Qt::LeftButton)
    // If we are moveing with the left button down, update the scene to trigger autocompute
    scene()->update(mapToScene(rect()).boundingRect());
}

void CustomGraphicsView::mousePressEvent(QMouseEvent* event)
{
  if (event->buttons() & Qt::LeftButton)
    // Set drag mode when left button is pressed
    setDragMode(QGraphicsView::ScrollHandDrag);
  QGraphicsView::mousePressEvent(event);
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
  if (dragMode() & QGraphicsView::ScrollHandDrag)
    // Unset drag mode when left button is released
    setDragMode(QGraphicsView::NoDrag);
  QGraphicsView::mouseReleaseEvent(event);
}

void CustomGraphicsView::autocomputeSceneSize(const QList<QRectF>& region)
{
  Q_UNUSED(region);

  // Widget viewport recangle
  QRectF widget_rect_in_scene(mapToScene(-20, -20), mapToScene(rect().bottomRight() + QPoint(20, 20)));

  // Copy the new size from the old one
  QPointF new_top_left(sceneRect().topLeft());
  QPointF new_bottom_right(sceneRect().bottomRight());

  // Check that the scene has a bigger limit in the top side
  if (sceneRect().top() > widget_rect_in_scene.top())
    new_top_left.setY(widget_rect_in_scene.top());

  // Check that the scene has a bigger limit in the bottom side
  if (sceneRect().bottom() < widget_rect_in_scene.bottom())
    new_bottom_right.setY(widget_rect_in_scene.bottom());

  // Check that the scene has a bigger limit in the left side
  if (sceneRect().left() > widget_rect_in_scene.left())
    new_top_left.setX(widget_rect_in_scene.left());

  // Check that the scene has a bigger limit in the right side
  if (sceneRect().right() < widget_rect_in_scene.right())
    new_bottom_right.setX(widget_rect_in_scene.right());

  // Set new scene size
  setSceneRect(QRectF(new_top_left, new_bottom_right));
}

void CustomGraphicsView::drawForeground(QPainter* painter, const QRectF& rect_orig)
{
  // Create shape
  QPolygonF arrow;
  arrow.push_back(QPointF(0, 0.5));
  arrow.push_back(QPointF(10.5, 0.5));
  arrow.push_back(QPointF(9.5, 2.5));
  arrow.push_back(QPointF(16.5, 0));
  arrow.push_back(QPointF(9.5, -2.5));
  arrow.push_back(QPointF(10.5, -0.5));
  arrow.push_back(QPointF(0, -0.5));
  QPainterPath arrow_path;
  arrow_path.addPolygon(arrow);
  QTransform t;
  t.rotate(90);
  arrow_path.addPolygon(t.map(arrow));

  // Paint it
  painter->save();
  t = painter->transform();
  painter->resetTransform();
  painter->translate(mapFromScene(0, 0));
  painter->scale(1, 1);
  painter->rotate(0);
  painter->fillPath(arrow_path, QBrush(Qt::black));
  painter->restore();
}
