#include "ball.h"
#include "game.h"
#include "level.h"
#include "paddle.h"
#include <iostream>

Ball::Ball() {
    spawn();
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
        double collision = Game::instance()->getPaddle()->getCollision(*this);
        if(collision < -1 || collision > 1) {
            //todo: lose a ball, game over, etc
            spawn();
        } else {
            position.setZ(side * .5 - radius);
            velocity.setZ(-velocity.z());
            velocity.setX(2 * abs(velocity.z()) * collision);
        }
    }
    position += velocity * dt;
}

void Ball::render() {
    glTranslated(position.x(), position.y(), position.z());
    gluSphere(quadric, radius, 30, 30);
}

void Ball::spawn() {
    position = QVector3D(0, 0, 0);
    velocity = QVector3D(20, 0, 20);
}
