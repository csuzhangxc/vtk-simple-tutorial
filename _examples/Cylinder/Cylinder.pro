TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += D:/VTK-6.1.0/MinGW/include/vtk-6.1

LIBS += -LD:/VTK-6.1.0/MinGW/lib \
        -lvtkCommonCore-6.1d \
        -lvtkFiltersSources-6.1d \
        -lvtkRenderingCore-6.1d \
        -lvtkCommonExecutionModel-6.1d \
        -lvtkRenderingOpenGL-6.1d \
        -lvtkInteractionStyle-6.1d


SOURCES += main.cpp
