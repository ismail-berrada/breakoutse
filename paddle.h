#ifndef PADDLE_H
#define PADDLE_H

#include "entity.h"

class Ball;

class Paddle : public Entity
{
public:
    Paddle();
    void update(double dt);
    void render();
    double getCollision(const Ball& ball);

private:
    const double length = 6;
    const double thickness = 1;
    const double friction = 4;
};

#endif // PADDLE_H
