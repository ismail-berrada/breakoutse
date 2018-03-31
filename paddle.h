#ifndef PADDLE_H
#define PADDLE_H

#include "entity.h"

class Paddle : public Entity
{
public:
    Paddle();
    void update(double dt);
    void render();

private:
    const double length = 4;
    const double thickness = 1;
};

#endif // PADDLE_H
