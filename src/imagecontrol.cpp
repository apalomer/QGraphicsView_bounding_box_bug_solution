#include "imagecontrol.h"
#include "ui_imagecontrol.h"

#include <QGraphicsRectItem>
#include <QImage>
#include <QSpinBox>

ImageControl::ImageControl(CustomGraphicsView *viewer, QString file_name, QWidget *parent)
  : QWidget(parent), ui(new Ui::ImageControl), viewer_(viewer), file_name_(file_name)
{
  ui->setupUi(this);

  item_ = new CustomGraphicsPixmapItem;
  item_rect_ = new QGraphicsRectItem;
  item_rect_->setVisible(ui->bounding_box->isChecked());
  viewer_->scene()->addItem(item_);
  viewer_->scene()->addItem(item_rect_);
  valueChanged(file_name);

  connect(ui->x_value, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this,
          &ImageControl::valueChanged);
  connect(ui->y_value, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this,
          &ImageControl::valueChanged);
  connect(ui->z_value, QOverload<const QString &>::of(&QSpinBox::valueChanged), this, &ImageControl::valueChanged);
  connect(ui->px_scale_value, QOverload<const QString &>::of(&QDoubleSpinBox::valueChanged), this,
          &ImageControl::valueChanged);
}

ImageControl::~ImageControl()
{
  delete ui;
}

void ImageControl::valueChanged(QString value)
{
  Q_UNUSED(value);
  QPixmap p = QPixmap::fromImage(QImage(file_name_));
  p.setDevicePixelRatio(ui->px_scale_value->value());
  item_->setPixmap(p);
  item_->setZValue(ui->z_value->value());
  QTransform t;
  t.translate(-p.width() / (2 * ui->px_scale_value->value()), -p.height() / (2 * ui->px_scale_value->value()));
  item_->setTransform(t);
  item_->setPos(ui->x_value->value(), ui->y_value->value());
  item_rect_->setRect(item_->boundingRect());
  item_rect_->setZValue(ui->z_value->value());
  item_rect_->setTransform(t);
  item_rect_->setPos(ui->x_value->value(), ui->y_value->value());
  item_rect_->setPen(QPen(Qt::black, 10 / ui->px_scale_value->value(), Qt::DashLine, Qt::RoundCap));
}

void ImageControl::on_checkBox_clicked(bool checked)
{
  item_rect_->setVisible(checked);
}

void ImageControl::on_comboBox_currentIndexChanged(int index)
{
  item_->setBoundingBoxComputationMethod(index == 0 ? CustomGraphicsPixmapItem::BB_TYPE_QT :
                                                      CustomGraphicsPixmapItem::BB_TYPE_CUSTOM);
  valueChanged(file_name_);
}
