#include "widget.h"

#include <QMatrix4x4>
#include <QTimerEvent>
#include <QVector3D>
#include <iostream>

glView::glView()
    : vertexBuffer(QOpenGLBuffer::VertexBuffer),
      indexBuffer(QOpenGLBuffer::IndexBuffer) {
  setFixedSize(650, 650);
}

void glView::initializeGL() {
  initializeOpenGLFunctions();

  FillVertices(vertices, &dod);
  FillIndices(indices, &dod);

  v_count = dod.v_count;
  f_count = dod.f_count;

  qWarning() << v_count;

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

  // Задание матрицы проекции и вида
  QMatrix4x4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(mvpMatrix.constData());

  vao.bind();
  glDrawElements(GL_LINES, f_count, GL_UNSIGNED_INT, nullptr);
  glDrawArrays(GL_POINTS, 0, v_count);
  update();
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

void glView::FillVertices(QVector<QVector3D>& vertices, dot_obj_data* dod) {
  vertices.clear();
  vertices.reserve((int)dod->v_count);

  for (int i = 0; i < (int)dod->v_count * 3; i += 3) {
    vertices.append(QVector3D(dod->vertices[i], dod->vertices[i + 1],
                              dod->vertices[i + 2]));
  }
}

void glView::FillIndices(QVector<GLuint>& indices, dot_obj_data* dod) {
  indices.clear();
  indices.reserve((int)dod->f_count);

  for (int i = 0; i < (int)dod->f_count; i++) {
    indices.append(static_cast<GLuint>(dod->faces[i]));
  }
}

void glView::updateVertexCoordinates(const QVector<QVector3D>& vertices) {
  // Проверяем, что количество вершин совпадает
  if (vertices.size() != v_count) {
    qWarning() << "Количество вершин не совпадает!";
    return;
  }

  vertexBuffer.bind();
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(QVector3D),
                  vertices.constData());
  vertexBuffer.release();

  update();
}

void glView::cleanupGL() {
  vao.destroy();
  vertexBuffer.destroy();
  indexBuffer.destroy();
}

void glView::reinitializeOpenGL() {
  makeCurrent();   // Сделать контекст текущим
  cleanupGL();     // Очистка старых ресурсов
  initializeGL();  // Переинициализация ресурсов
  doneCurrent();  // Завершение использования текущего контекста
  update();       // Перерисовка виджета
}

glView::~glView() {
  makeCurrent();
  vertexBuffer.destroy();
  indexBuffer.destroy();
  doneCurrent();
}
