#-------------------------------------------------
#
# Project created by QtCreator 2015-03-15T15:13:47
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = ImageViewer
TEMPLATE = app

INCLUDEPATH += D:/VTK-6.1.0/MinGW/include/vtk-6.1

LIBS += -LD:/VTK-6.1.0/MinGW/lib/ \
        -lvtkGUISupportQt-6.1d \
        -lvtkIOImage-6.1d \
        -lvtkInteractionImage-6.1d \
        -lvtkRenderingCore-6.1d \
        -lvtkCommonExecutionModel-6.1d \
        -lvtkCommonCore-6.1d \
        -lvtkRenderingOpenGL-6.1d \
        -lvtkInteractionStyle-6.1d

SOURCES += main.cpp

HEADERS  +=
