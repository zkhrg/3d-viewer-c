QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = 3d_viewer_c
DESTDIR = ../../build

SOURCES += \
    ../c_core/transformations.c \
    ../c_core/dot_obj_parser.c \
    mainwindow.cc \
    widget.cc \
    main.cc 

HEADERS += \
    ../c_core/transformations.h \
    ../c_core/dot_obj_parser.h \
    ../common/types.h \
    mainwindow.h \
    widget.h 

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
