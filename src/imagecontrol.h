#ifndef IMAGECONTROL_H
#define IMAGECONTROL_H

#include <QWidget>
#include "customgraphicspixmapitem.h"
#include "customview.h"

namespace Ui
{
class ImageControl;
}

class ImageControl : public QWidget
{
  Q_OBJECT

public:
  explicit ImageControl(CustomGraphicsView *viewer, QString file_name, QWidget *parent = nullptr);
  ~ImageControl();

public slots:

  void valueChanged(QString value);

private slots:
  void on_comboBox_currentIndexChanged(int index);

private slots:
  void on_checkBox_clicked(bool checked);

private:
  Ui::ImageControl *ui;
  CustomGraphicsView *viewer_;
  CustomGraphicsPixmapItem *item_;
  QString file_name_;
  QGraphicsRectItem *item_rect_;
};

#endif  // IMAGECONTROL_H
