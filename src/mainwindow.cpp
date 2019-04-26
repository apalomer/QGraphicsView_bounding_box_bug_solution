#include "mainwindow.h"
#include "imagecontrol.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->widget->setScene(new QGraphicsScene);
  ui->verticalLayout->addWidget(new ImageControl(ui->widget, "../clouds-country-daylight-371633.jpg", this));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_action_open_image_triggered()
{
  QStringList files = QFileDialog::getOpenFileNames(this, "Select open files", "", tr("Images (*.png *.jpg *.tif)"));
  for (auto f : files)
  {
    ui->verticalLayout->addWidget(new ImageControl(ui->widget, f, this));
  }
}

void MainWindow::on_action_fit_triggered()
{
  QRectF rect = ui->widget->scene()->itemsBoundingRect();
  QPointF center = rect.center();
  QPointF quarter(rect.width() / 2, rect.height() / 2);
  ui->widget->fitInView(QRectF(center - quarter * 1.1, center + quarter * 1.1), Qt::KeepAspectRatio);
}
