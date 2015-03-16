#-------------------------------------------------
#
# Project created by QtCreator 2015-03-13T10:47:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Contour2D
TEMPLATE = app

CONFIG += c++11


INCLUDEPATH += D:/VTK-6.1.0/MinGW/include/vtk-6.1

LIBS += -LD:/VTK-6.1.0/MinGW/lib/ \
        -lvtkCommonCore-6.1 \
        -lvtkRenderingOpenGL-6.1 \
        -lvtkInteractionStyle-6.1 \
        -lvtkGUISupportQt-6.1 \
        -lvtkCommonDataModel-6.1 \
        -lvtkFiltersSources-6.1 \
        -lvtkRenderingCore-6.1 \
        -lvtkCommonExecutionModel-6.1 \
        -lvtkFiltersCore-6.1 \
        -lvtkCommonMisc-6.1


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
