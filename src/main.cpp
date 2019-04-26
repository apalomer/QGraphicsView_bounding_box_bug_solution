#include <QApplication>
//#include <QGraphicsPixmapItem>
//#include "customview.h"
#include "mainwindow.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  //  CustomGraphicsView cgv;
  //  QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("../"
  //                                                                                "clouds-country-daylight-371633.jpg")));
  //  cgv.scene()->addItem(item);
  //  cgv.show();
  MainWindow mw;
  mw.show();
  return app.exec();
}
