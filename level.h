#ifndef LEVEL_H
#define LEVEL_H

#include <QImage>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <brick.h>

class Level {
public:
    Level();
    ~Level();
    void update(double dt);
    void render();
    std::vector<Brick*>& getBricks() {return bricks;};
    const double side = 30;

private:
    QImage wall;
    QImage ground;
    GLuint wallTexture;
    GLuint groundTexture;
    std::vector<Brick*> bricks;
};

#endif // LEVEL_H
