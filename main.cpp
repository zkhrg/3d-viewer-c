#include <QApplication>
#define GL_SILENCE_DEPRECATION
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  // exit(0);
  dot_obj_data dod;
  parse_dot_obj_file("/Users/diamondp/Desktop/model/model.obj", &dod);
  print_dod(&dod);
  w.show();
  return a.exec();
}
