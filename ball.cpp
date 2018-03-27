#include "ball.h"

Ball::Ball() {
    velocity = QVector3D(20, 0, 10);
}

void Ball::update(double dt) {
    const double side = 15;
    if(position.x() - radius < -side) {
        position.setX(-side + radius);
        velocity.setX(-velocity.x());
    } else if(position.x() + radius > side) {
        position.setX(side - radius);
        velocity.setX(-velocity.x());
    }
    if(position.z() - radius < -side) {
        position.setZ(-side + radius);
        velocity.setZ(-velocity.z());
    } else if(position.z() + radius > side) {
        position.setZ(side - radius);
        velocity.setZ(-velocity.z());
    }
    position += velocity * dt;
}

void Ball::render() {
    glTranslated(position.x(), position.y(), position.z());
    gluSphere(quadric, radius, 30, 30);
}
