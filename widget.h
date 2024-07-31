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

  void cleanupGL();
  void reinitializeOpenGL();

  GLuint compileShader(GLenum type, const char* source);
  GLuint createShaderProgram(const char* vertexSource,
                             const char* fragmentSource);

 private slots:
  void openFileDialog();  // Слот для открытия диалога выбора файла
 private:
  QString filePath;  // Поле для хранения пути к файлу

  int v_count;
  int f_count;

  float line_size;
  float point_size;
  QColor line_color;
  QColor background_color;

 public:
  static const inline char* vertex_shader_source = R"(
    #version 120
    attribute vec3 aPos;
    uniform mat4 mvpMatrix;
    void main() {
        gl_Position = mvpMatrix * vec4(aPos, 1.0);
    }
  )";
  static const inline char* fragment_shader_source = R"(
    #version 120
    uniform vec3 lineColor;
    void main() {
        gl_FragColor = vec4(lineColor, 1.0);
    }
  )";

  void updateRotation();

 public:
  dot_obj_data dod;
  GLuint shader_program;
};

#endif  // WIDGET_H
