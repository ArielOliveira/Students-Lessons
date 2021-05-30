TEMPLATE += app
QT += core gui opengl widgets
LIBS += -lglew32 -lopengl32 -lgdi32

HEADERS += *.h

SOURCES += *.cpp

TARGET = openglProject

DISTFILES += \
    shader/scenebasic2.dat \
    shader/basic.frag \
    shader/basic.vert