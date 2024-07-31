#include "mainwindow.h"

#include <QGroupBox>
#include <QLabel>
#include <QSpacerItem>
#include <QVBoxLayout>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      my_gl(new glView()),
      prev_x_rot(50),
      prev_y_rot(50),
      prev_z_rot(50),
      prev_x_move(50),
      prev_y_move(50),
      prev_z_move(50),
      scale_val(5) {
  but = new QPushButton("Upload model");
  connect(but, &QPushButton::clicked, this, &MainWindow::openFileDialog);
  scale_sub_but = new QPushButton("-");
  scale_add_but = new QPushButton("+");

  slrotate_x = new QScrollBar(Qt::Horizontal);
  slrotate_y = new QScrollBar(Qt::Horizontal);
  slrotate_z = new QScrollBar(Qt::Horizontal);
  // slrotate_x->setRange(0, 200);
  slrotate_x->setValue(prev_x_rot);
  slrotate_y->setValue(prev_y_rot);
  slrotate_z->setValue(prev_z_rot);

  slmove_x = new QScrollBar(Qt::Horizontal);
  slmove_y = new QScrollBar(Qt::Horizontal);
  slmove_z = new QScrollBar(Qt::Horizontal);
  slmove_x->setValue(prev_x_move);
  slmove_y->setValue(prev_y_move);
  slmove_z->setValue(prev_z_move);
  QLabel *label_x_sub = new QLabel("X-");
  QLabel *label_y_sub = new QLabel("Y-");
  QLabel *label_z_sub = new QLabel("Z-");
  QLabel *label_x_add = new QLabel("X+");
  QLabel *label_y_add = new QLabel("Y+");
  QLabel *label_z_add = new QLabel("Z+");

  QLabel *label_x_sub1 = new QLabel("X-");
  QLabel *label_y_sub1 = new QLabel("Y-");
  QLabel *label_z_sub1 = new QLabel("Z-");
  QLabel *label_x_add1 = new QLabel("X+");
  QLabel *label_y_add1 = new QLabel("Y+");
  QLabel *label_z_add1 = new QLabel("Z+");

  QWidget *centralWidget = new QWidget(this);
  QVBoxLayout *main_layout = new QVBoxLayout(centralWidget);
  main_layout->setSpacing(25);

  QHBoxLayout *rot_x_layout = new QHBoxLayout();
  QHBoxLayout *rot_y_layout = new QHBoxLayout();
  QHBoxLayout *rot_z_layout = new QHBoxLayout();

  QHBoxLayout *move_x_layout = new QHBoxLayout();
  QHBoxLayout *move_y_layout = new QHBoxLayout();
  QHBoxLayout *move_z_layout = new QHBoxLayout();

  QHBoxLayout *scale_layout = new QHBoxLayout();
  QVBoxLayout *rotate_layout = new QVBoxLayout();
  QVBoxLayout *move_layout = new QVBoxLayout();

  QGroupBox *scale_group = new QGroupBox("Scale", this);
  QGroupBox *rotate_group = new QGroupBox("Rotate", this);
  QGroupBox *move_group = new QGroupBox("Move", this);

  QSpacerItem *leftSpacer =
      new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  QSpacerItem *rightSpacer =
      new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

  /*************************************/
  scale_layout->addSpacerItem(leftSpacer);
  scale_layout->addWidget(scale_sub_but);
  scale_layout->addWidget(scale_add_but);
  scale_layout->addSpacerItem(rightSpacer);
  scale_group->setLayout(scale_layout);
  /*************************************/

  /*************************************/
  rot_x_layout->addWidget(label_x_sub);
  rot_x_layout->addWidget(slrotate_x, 1);
  rot_x_layout->addWidget(label_x_add);
  rotate_layout->addLayout(rot_x_layout);

  rot_y_layout->addWidget(label_y_sub);
  rot_y_layout->addWidget(slrotate_y, 1);
  rot_y_layout->addWidget(label_y_add);
  rotate_layout->addLayout(rot_y_layout);

  rot_z_layout->addWidget(label_z_sub);
  rot_z_layout->addWidget(slrotate_z, 1);
  rot_z_layout->addWidget(label_z_add);
  rotate_layout->addLayout(rot_z_layout);

  rotate_group->setLayout(rotate_layout);
  /*************************************/

  /*************************************/
  move_x_layout->addWidget(label_x_sub1);
  move_x_layout->addWidget(slmove_x, 1);
  move_x_layout->addWidget(label_x_add1);
  move_layout->addLayout(move_x_layout);

  move_y_layout->addWidget(label_y_sub1);
  move_y_layout->addWidget(slmove_y, 1);
  move_y_layout->addWidget(label_y_add1);
  move_layout->addLayout(move_y_layout);

  move_z_layout->addWidget(label_z_sub1);
  move_z_layout->addWidget(slmove_z, 1);
  move_z_layout->addWidget(label_z_add1);
  move_layout->addLayout(move_z_layout);

  move_group->setLayout(move_layout);
  /*************************************/

  main_layout->addWidget(my_gl);
  main_layout->addWidget(but);
  main_layout->addWidget(scale_group);
  main_layout->addWidget(rotate_group);
  main_layout->addWidget(move_group);
  setCentralWidget(centralWidget);

  connect(scale_sub_but, &QPushButton::pressed, this, &MainWindow::ScaleSub);
  connect(scale_add_but, &QPushButton::pressed, this, &MainWindow::ScaleAdd);

  connect(slrotate_x, &QScrollBar::valueChanged, this,
          &MainWindow::xRotateChanged);
  connect(slrotate_y, &QScrollBar::valueChanged, this,
          &MainWindow::yRotateChanged);
  connect(slrotate_z, &QScrollBar::valueChanged, this,
          &MainWindow::zRotateChanged);

  connect(slmove_x, &QScrollBar::valueChanged, this, &MainWindow::xMoveChanged);
  connect(slmove_y, &QScrollBar::valueChanged, this, &MainWindow::yMoveChanged);
  connect(slmove_z, &QScrollBar::valueChanged, this, &MainWindow::zMoveChanged);
}

void MainWindow::openFileDialog() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                  tr("All Files (*.*)"));
  if (!fileName.isEmpty()) {
    filePath = fileName;
    // Вы можете использовать filePath для загрузки или обработки файла
    qDebug() << "Selected file path:" << filePath;
  }
  parse_dot_obj_file(filePath.toStdString().c_str(), &(my_gl->dod));
  my_gl->reinitializeOpenGL();
}

void MainWindow::xRotateChanged(int val) {
  int delta = val - prev_x_rot;
  qDebug() << "xRotateChanged delta:" << delta;
  prev_x_rot = val;
  rotate_x(&(my_gl->dod), delta * 4);
  my_gl->FillVertices(my_gl->vertices, &(my_gl->dod));
  my_gl->updateVertexCoordinates(my_gl->vertices);
}

void MainWindow::yRotateChanged(int val) {
  int delta = val - prev_y_rot;
  qDebug() << "yRotateChanged delta:" << delta;
  prev_y_rot = val;
  rotate_y(&(my_gl->dod), delta * 4);
  my_gl->FillVertices(my_gl->vertices, &(my_gl->dod));
  my_gl->updateVertexCoordinates(my_gl->vertices);
}

void MainWindow::zRotateChanged(int val) {
  int delta = val - prev_z_rot;
  qDebug() << "zRotateChanged delta:" << delta;
  prev_z_rot = val;
  rotate_z(&(my_gl->dod), delta * 4);
  my_gl->FillVertices(my_gl->vertices, &(my_gl->dod));
  my_gl->updateVertexCoordinates(my_gl->vertices);
}

void MainWindow::xMoveChanged(int val) {
  int delta = val - prev_x_move;
  qDebug() << "xMoveChanged delta:" << delta;
  prev_x_move = val;
  move_vertices(&(my_gl->dod), delta, MOVE_X);
  my_gl->FillVertices(my_gl->vertices, &(my_gl->dod));
  my_gl->updateVertexCoordinates(my_gl->vertices);
}

void MainWindow::yMoveChanged(int val) {
  int delta = val - prev_y_move;
  qDebug() << "yMoveChanged delta:" << delta;
  prev_y_move = val;
  move_vertices(&(my_gl->dod), delta, MOVE_Y);
  my_gl->FillVertices(my_gl->vertices, &(my_gl->dod));
  my_gl->updateVertexCoordinates(my_gl->vertices);
}

void MainWindow::zMoveChanged(int val) {
  int delta = val - prev_z_move;
  qDebug() << "zMoveChanged delta:" << delta;
  prev_z_move = val;
  move_vertices(&(my_gl->dod), delta, MOVE_Z);
  my_gl->FillVertices(my_gl->vertices, &(my_gl->dod));
  my_gl->updateVertexCoordinates(my_gl->vertices);
}

void MainWindow::ScaleSub() {
  scale_vertices(&(my_gl->dod), -scale_val);
  my_gl->FillVertices(my_gl->vertices, &(my_gl->dod));
  my_gl->updateVertexCoordinates(my_gl->vertices);
}

void MainWindow::ScaleAdd() {
  scale_vertices(&(my_gl->dod), scale_val);
  my_gl->FillVertices(my_gl->vertices, &(my_gl->dod));
  my_gl->updateVertexCoordinates(my_gl->vertices);
}

MainWindow::~MainWindow() {
  // Деструктор
}
