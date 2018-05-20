#ifndef PADDLE_H
#define PADDLE_H

#include "entity.h"

class Ball;

class Paddle : public Entity
{
public:
    Paddle();
    void update(double dt);
    void move(bool right);
    void render();
    double getCollision(const Ball& ball);

private:
    const double thickness = 1;
    const double friction = 4;
    static GLuint texture;
    static QImage image;
};

#endif // PADDLE_H
