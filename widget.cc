#include "widget.h"

#include <QMatrix4x4>
#include <QTimerEvent>
#include <QVector3D>

glView::glView()
    : vertexBuffer(QOpenGLBuffer::VertexBuffer),
      indexBuffer(QOpenGLBuffer::IndexBuffer),
      line_size(1.0f),
      point_size(10.0f),
      line_color(Qt::blue),
      background_color(Qt::white) {
  setFixedSize(650, 650);
}

void glView::initializeGL() {
  initializeOpenGLFunctions();
  shader_program =
      createShaderProgram(vertex_shader_source, fragment_shader_source);

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

  glClearColor(background_color.redF(), background_color.greenF(),
               background_color.blueF(), 0.0f);
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
  glUseProgram(shader_program);

  // Задание матрицы проекции и вида
  QMatrix4x4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

  GLuint mvpMatrixLoc = glGetUniformLocation(shader_program, "mvpMatrix");
  glUniformMatrix4fv(mvpMatrixLoc, 1, GL_FALSE, mvpMatrix.constData());

  // Передача цвета в шейдер
  GLuint colorLoc = glGetUniformLocation(shader_program, "lineColor");
  glUniform3f(colorLoc, line_color.redF(), line_color.greenF(),
              line_color.blueF());

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(mvpMatrix.constData());

  glLineWidth(line_size);
  glPointSize(point_size);

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
  makeCurrent();
  cleanupGL();
  initializeGL();
  doneCurrent();
  update();
}

GLuint glView::compileShader(GLenum type, const char* source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  return shader;
}

// Функция для создания шейдерной программы
GLuint glView::createShaderProgram(const char* vertexSource,
                                   const char* fragmentSource) {
  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
  GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // удаляем шейдеры после линковки тк они больше не нужны
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}

glView::~glView() {
  makeCurrent();
  vertexBuffer.destroy();
  indexBuffer.destroy();
  doneCurrent();
}
