#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_action_fit_triggered();

private slots:
  void on_action_open_image_triggered();

private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
