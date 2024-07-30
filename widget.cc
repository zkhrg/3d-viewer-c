#include "widget.h"

#include <QMatrix4x4>
#include <QTimerEvent>
#include <QVector3D>

glView::glView()
    : vertexBuffer(QOpenGLBuffer::VertexBuffer),
      indexBuffer(QOpenGLBuffer::IndexBuffer),
      rotationAngleX(25.0f),
      rotationAngleY(25.0f) {
  setFixedSize(650, 650);
}

void glView::initializeGL() {
  initializeOpenGLFunctions();

  // Вершины куба
  QVector<QVector3D> vertices = {
      {-0.5f, -0.5f, 0.5f},  // 0
      {0.5f, -0.5f, 0.5f},   // 1
      {0.5f, 0.5f, 0.5f},    // 2
      {-0.5f, 0.5f, 0.5f},   // 3
      {-0.5f, -0.5f, -.5f},  // 4
      {0.5f, -0.5f, -.5f},   // 5
      {0.5f, 0.5f, -.5f},    // 6
      {-0.5f, 0.5f, -.5f}    // 7
  };

  QVector<GLuint> indices = {
      0, 1, 1, 2, 2, 3, 3, 0,  // Передняя грань
      4, 5, 5, 6, 6, 7, 7, 4,  // Задняя грань
      0, 4, 1, 5, 2, 6, 3, 7   // Соединяющие линии
  };

  vertexBuffer.create();
  vertexBuffer.bind();
  vertexBuffer.allocate(vertices.constData(),
                        vertices.size() * sizeof(QVector3D));

  indexBuffer.create();
  indexBuffer.bind();
  indexBuffer.allocate(indices.constData(), indices.size() * sizeof(GLuint));

  vao.create();
  vao.bind();
  setupVertexAttribs();

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);

  // Установка матрицы проекции
  projectionMatrix.setToIdentity();
  projectionMatrix.perspective(45.0f, 3.0f / 3.0f, 0.1f, 100.0f);

  // Установка матрицы вида
  viewMatrix.setToIdentity();
  viewMatrix.translate(0, 0, -3);
}

void glView::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Обновляем матрицу модели
  updateRotation();

  // Задание матрицы проекции и вида
  QMatrix4x4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(mvpMatrix.constData());

  vao.bind();
  glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, nullptr);  // Отрисовка линий
  glDrawArrays(GL_POINTS, 0, 8);  // Отрисовка вершин
}

void glView::setupVertexAttribs() {
  vertexBuffer.bind();
  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
  f->glEnableVertexAttribArray(0);
  f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D),
                           nullptr);
  vertexBuffer.release();

  indexBuffer.bind();
  vao.release();
}

void glView::updateRotation() {
  modelMatrix.setToIdentity();
  modelMatrix.rotate(rotationAngleX, 1.0f, 0.0f, 0.0f);  // Поворот по оси X
  modelMatrix.rotate(rotationAngleY, 0.0f, 1.0f, 0.0f);  // Поворот по оси Y
}

glView::~glView() {
  makeCurrent();
  vertexBuffer.destroy();
  indexBuffer.destroy();
  doneCurrent();
}
