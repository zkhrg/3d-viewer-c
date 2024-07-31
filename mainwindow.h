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
 private slots:
  void openFileDialog();
  void xRotateChanged(int val);
  void yRotateChanged(int val);
  void zRotateChanged(int val);
  void xMoveChanged(int val);
  void yMoveChanged(int val);
  void zMoveChanged(int val);
  void ScaleSub();
  void ScaleAdd();

 private:
  glView *my_gl;
  QPushButton *but, *scale_sub_but, *scale_add_but;
  QScrollBar *slscale, *slrotate_x, *slrotate_y, *slrotate_z, *slmove_x,
      *slmove_y, *slmove_z;
  QGroupBox *groupBox;
  QString filePath;
  int prev_x_rot;
  int prev_y_rot;
  int prev_z_rot;
  int prev_x_move;
  int prev_y_move;
  int prev_z_move;
  int scale_val;
};

#endif  // MAINWINDOW_H
