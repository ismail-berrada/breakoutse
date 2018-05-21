#ifndef BRICK_H
#define BRICK_H

#include <QImage>
#include <QRect>
#include "entity.h"

// A rectangular brick that can be destroyed by the ball.
class Brick : public Entity {

  public:
    Brick(QVector3D position);
    ~Brick();
    void update(double dt);
    void render();

  private:
    // A countdown to make the brick appear out of the ground
    double spawnTimer;
    double spawnTime;

    // The brick's texture
    static GLuint texture;
    static QImage image;
};

#endif // BRICK_H
