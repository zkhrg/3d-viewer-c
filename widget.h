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

extern "C" {
#include "dot_obj_parser.h"
#include "transformations.h"
#include "types.h"
}

class glView : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  glView();
  ~glView();

  void initializeGL() override;
  void paintGL() override;

 public:
  void setupVertexAttribs();

  QMatrix4x4 projectionMatrix;
  QMatrix4x4 viewMatrix;
  QMatrix4x4 modelMatrix;
  // Вершины куба
  QVector<QVector3D> vertices;
  QVector<GLuint> indices;

  QOpenGLBuffer vertexBuffer;
  QOpenGLVertexArrayObject vao;
  QOpenGLBuffer indexBuffer;
  void FillVertices(QVector<QVector3D>& vertices, dot_obj_data* dod);
  void FillIndices(QVector<GLuint>& indices, dot_obj_data* dod);

 public:
  void updateVertexCoordinates(const QVector<QVector3D>& vertices);

  float rotationAngleX;
  float rotationAngleY;

 private slots:
  void openFileDialog();  // Слот для открытия диалога выбора файла
 private:
  QString filePath;  // Поле для хранения пути к файлу

  int v_count;
  int f_count;

  void updateRotation();

 public:
  dot_obj_data dod;
};

#endif  // WIDGET_H
