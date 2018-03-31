#ifndef LEVEL_H
#define LEVEL_H

#include <QImage>
#include <GL/gl.h>
#include <GL/glu.h>

class Level {
public:
    Level();
    void render();
    const double side = 30;

private:
    QImage wall;
    QImage ground;
    GLuint wallTexture;
    GLuint groundTexture;
};

#endif // LEVEL_H
