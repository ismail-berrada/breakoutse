#ifndef BALL_H
#define BALL_H

#include <QVector3D>

#include "entity.h"

class Ball : public Entity {
public:
    Ball();
    void update(double dt);
    void render();
    void spawn();
    double getRadius() const {return radius;};

private:
    double speed = .01;
    double radius = .5;
};

#endif // BALL_H
