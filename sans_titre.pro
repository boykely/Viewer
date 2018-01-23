#-------------------------------------------------
#
# Project created by QtCreator 2018-01-16T21:18:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sans_titre
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH+=Lib/glm/glm/

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    glwidget.cpp \
    GlShader/GLSLShader.cpp \
    Object/triangle.cpp

HEADERS += \
        mainwindow.h \
    glwidget.h \
    mainwindow.h \
    GlShader/GLSLShader.h \
    Object/triangle.h

win32: LIBS += -L$$PWD/Lib/soil/lib/ -llibSOIL

INCLUDEPATH += $$PWD/Lib/soil/src
DEPENDPATH += $$PWD/Lib/soil/src

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/Lib/soil/lib/libSOIL.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/Lib/soil/lib/liblibSOIL.a

DISTFILES += \
    Resources/Shaders/shader.frag \
    Resources/Shaders/shader.vert
