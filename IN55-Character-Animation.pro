#-------------------------------------------------
#
# Project created by QtCreator 2014-05-12T22:00:23
#
#-------------------------------------------------
CONFIG += console release
QT       += core gui opengl

TARGET = IN55-Character-Animation

TEMPLATE = app

unix:!macx: LIBS += -L$$PWD/../../../../../usr/lib/ -lGLEW

INCLUDEPATH += $$PWD/../../../../../usr/include/GL
DEPENDPATH += $$PWD/../../../../../usr/include/GL

SOURCES += src/main/MyWindow.cpp \
    src/main/main.cpp \
    src/common/RandomNumberGenerator.cpp \
    src/common/Object3D.cpp \
    src/common/LF_String.cpp \
    src/common/GlWindow.cpp \
    src/common/GlFramework.cpp \
    src/shapes/Basis.cpp \
    src/camera/Quaternion.cpp \
    src/camera/Camera.cpp

HEADERS += \
    src/main/MyWindow.h \
    src/common/Vectors.h \
    src/common/Types.h \
    src/common/RandomNumberGenerator.h \
    src/common/Object3D.h \
    src/common/MemDefns.h \
    src/common/LF_String.h \
    src/common/GlWindow.h \
    src/common/GlFramework.h \
    src/common/AbstractFramework.h \
    src/shapes/Basis.h \
    src/camera/Quaternion.h \
    src/camera/Camera.h
