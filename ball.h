#ifndef BALL_H
#define BALL_H

#include <QVector3D>

#include "entity.h"
class Brick;

// A ball that collides with the walls, the paddle and the bricks (destroying them).
class Ball : public Entity {
public:
    Ball();
    void update(double dt);
    void render();

    // A special function to render the ball as an icon.
    void render(bool icon);

    // Reset the ball position and stick it to the paddle.
    void spawn();

    // Launch the ball off the paddle.
    void launch();

    // Returns true if the segments [ab] and [pq] intersect. (4 dot products)
    bool segmentIntersection(QVector2D a, QVector2D b, QVector2D p, QVector2D q);

    double getRadius() const {return radius;};

    // Increase the ball speed by 4, called after each level is won.
    void increaseSpeed();

private:
    double speed = 12;
    double radius = .8;
    double angle = 0;
    bool stuck;
    static GLuint texture;
    static QImage image;
};

#endif // BALL_H
