#include "mainwindow.h"

#include <QGroupBox>
#include <QLabel>
#include <QSpacerItem>
#include <QVBoxLayout>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), my_gl(new glView()) {
  but = new QPushButton("Upload model");
  connect(but, &QPushButton::clicked, this, &MainWindow::openFileDialog);
  scale_sub = new QPushButton("-");
  scale_add = new QPushButton("+");
  slrotate_x = new QScrollBar(Qt::Horizontal);
  slrotate_y = new QScrollBar(Qt::Horizontal);
  slrotate_z = new QScrollBar(Qt::Horizontal);
  slrotate_x->setValue(50);
  slrotate_y->setValue(50);
  slrotate_z->setValue(50);

  slmove_x = new QScrollBar(Qt::Horizontal);
  slmove_y = new QScrollBar(Qt::Horizontal);
  slmove_z = new QScrollBar(Qt::Horizontal);
  slmove_x->setValue(50);
  slmove_y->setValue(50);
  slmove_z->setValue(50);
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
  scale_layout->addWidget(scale_sub);
  scale_layout->addWidget(scale_add);
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
}

void MainWindow::openFileDialog() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                  tr("All Files (*.*)"));
  if (!fileName.isEmpty()) {
    filePath = fileName;
    // Вы можете использовать filePath для загрузки или обработки файла
    qDebug() << "Selected file path:" << filePath;
  }
}

MainWindow::~MainWindow() {
  // Деструктор
}
