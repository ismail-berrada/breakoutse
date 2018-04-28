#ifndef BALL_H
#define BALL_H

#include <QVector3D>

#include "entity.h"
class Brick;

class Ball : public Entity {
public:
    Ball();
    void update(double dt);
    void render();
    void spawn();
    void launch();
    bool segmentIntersection(QVector2D a, QVector2D b, QVector2D p, QVector2D q);
    double getRadius() const {return radius;};

private:
    QVector3D acceleration;
    double speed = .01;
    double radius = .5;
    bool stuck;
};

#endif // BALL_H
