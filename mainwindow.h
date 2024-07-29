#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGroupBox>
#include <QMainWindow>
#include <QPushButton>
#include <QScrollBar>

#include "widget.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  glView *my_gl;
  QPushButton *but, *scale_sub, *scale_add;
  QScrollBar *slscale, *slrotate_x, *slrotate_y, *slrotate_z, *slmove_x,
      *slmove_y, *slmove_z;
  QGroupBox *groupBox;
};

#endif  // MAINWINDOW_H
