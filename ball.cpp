#include "ball.h"
#include "game.h"
#include "level.h"

Ball::Ball() {
    velocity = QVector3D(20, 0, 10);
}

void Ball::update(double dt) {
    double side = Game::instance()->getLevel()->side;
    if(position.x() - radius < -side * .5) {
        position.setX(-side * .5 + radius);
        velocity.setX(-velocity.x());
    } else if(position.x() + radius > side * .5) {
        position.setX(side * .5 - radius);
        velocity.setX(-velocity.x());
    }
    if(position.z() - radius < -side * .5) {
        position.setZ(-side * .5 + radius);
        velocity.setZ(-velocity.z());
    } else if(position.z() + radius > side * .5) {
        position.setZ(side * .5 - radius);
        velocity.setZ(-velocity.z());
    }
    position += velocity * dt;
}

void Ball::render() {
    glTranslated(position.x(), position.y(), position.z());
    gluSphere(quadric, radius, 30, 30);
}
