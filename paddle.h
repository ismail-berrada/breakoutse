#ifndef PADDLE_H
#define PADDLE_H

#include "entity.h"

class Ball;

// A paddle that scrolls left and right and catches the ball.
class Paddle : public Entity
{
public:
    Paddle();
    void update(double dt);
    void move(bool right);
    void stop();
    void render();
    double getCollision(const Ball& ball);
    void reset();

private:
    const double friction = 4;
    static GLuint texture;
    static QImage image;
};

#endif // PADDLE_H
