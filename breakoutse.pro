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
    game.cpp
HEADERS += \
    game.h \
    ball.h \
    level.h \
    paddle.h \
    entity.h
