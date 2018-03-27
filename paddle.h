#ifndef PADDLE_H
#define PADDLE_H

#include "entity.h"

class Paddle : public Entity
{
public:
    Paddle();
    void update(double dt);
    void render();
};

#endif // PADDLE_H
