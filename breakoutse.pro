# configuration Qt
QT       += core gui opengl widgets
TEMPLATE  = app

# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
else {
	LIBS     += -lGL -lGLU
}

# nom de l'exe genere
TARGET 	  = TD2

# fichiers sources/headers
SOURCES	+= main.cpp \
    ball.cpp \
    level.cpp \
    paddle.cpp \
    entity.cpp \
    game.cpp \
    brick.cpp \
    text3d.cpp \
    ui.cpp \
    motiondetector.cpp
HEADERS += \
    game.h \
    ball.h \
    level.h \
    paddle.h \
    entity.h \
    brick.h \
    text3d.h \
    ui.h \
    motiondetector.h

RESOURCES += \
    resources.qrc

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS += -L$$(OPENCV_DIR)\lib \
        -lopencv_core2413 \
        -lopencv_highgui2413 \
        -lopencv_imgproc2413 \
        -lopencv_video2413 \
        -lopencv_features2d2413 \
        -lopencv_calib3d2413
