QT += core gui widgets opengl
TEMPLATE = app

SOURCES += \
    main.cpp \
    OpenGLWidget.cpp \
    toyview.cpp

HEADERS  += \
    OpenGLWidget.h \
    toyview.h

DISTFILES += \
    shader.f.glsl \
    shader.v.glsl

RESOURCES += \
    sketchapp.qrc
