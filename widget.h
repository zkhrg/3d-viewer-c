#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QPushButton>
#include <QWidget>

class glView : public QOpenGLWidget {
 public:
  glView() { setFixedSize(650, 650); };
  ~glView() {};

  void initializeGL() override;
  void paintGL() override;
};

#endif  // WIDGET_H
