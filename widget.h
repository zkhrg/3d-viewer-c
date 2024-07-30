#ifndef WIDGET_H
#define WIDGET_H

#include <QFileDialog>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QWidget>

class glView : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  glView();
  ~glView();

  void initializeGL() override;
  void paintGL() override;

 private:
  void setupVertexAttribs();

  QMatrix4x4 projectionMatrix;
  QMatrix4x4 viewMatrix;
  QMatrix4x4 modelMatrix;

  QOpenGLBuffer vertexBuffer;
  QOpenGLVertexArrayObject vao;
  QOpenGLBuffer indexBuffer;

  float rotationAngleX;
  float rotationAngleY;

 private slots:
  void openFileDialog();  // Слот для открытия диалога выбора файла

  QString filePath;  // Поле для хранения пути к файлу

  void updateRotation();
};

#endif  // WIDGET_H
