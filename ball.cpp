#include "ball.h"
#include "game.h"
#include "level.h"
#include "paddle.h"
#include <iostream>

Ball::Ball() {
    spawn();
}

void Ball::update(double dt) {
    if(stuck) {
        position.setX(Game::instance()->getPaddle()->getPosition().x());
        position.setZ(Game::instance()->getPaddle()->getPosition().z() - radius);
    } else {
        bool hit = false;
        double side = Game::instance()->getLevel()->side;
        if(position.x() - radius < -side * .5) {
            position.setX(-side * .5 + radius);
            velocity.setX(-velocity.x());
            hit = true;
        } else if(position.x() + radius > side * .5) {
            position.setX(side * .5 - radius);
            velocity.setX(-velocity.x());
            hit = true;
        }
        if(position.z() - radius < -side * .5) {
            position.setZ(-side * .5 + radius);
            velocity.setZ(-velocity.z());
            hit = true;
        } else if(position.z() + radius > side * .5) {
            double collision = Game::instance()->getPaddle()->getCollision(*this);
            if(collision < -1 || collision > 1) {
                visible = false;
                if(Game::instance()->loseBall()) {
                    spawn();
                }
            } else {
                position.setZ(side * .5 - radius);
                velocity.setZ(-velocity.z());
                velocity.setX(2 * abs(velocity.z()) * collision);
                hit = true;
            }
        }
        position += velocity * dt;
    }
}

void Ball::render() {
    if(!visible) return;
    glTranslated(position.x(), position.y(), position.z());
    gluSphere(quadric, radius, 30, 30);
}

void Ball::spawn() {
    position = QVector3D(0, 0, 0);
    velocity = QVector3D(0, 0, 0);
    stuck = true;
    visible = true;
}

void Ball::launch() {
    if(!stuck) {
        return;
    }
    velocity = QVector3D(rand() % 100 / 20., 0, -20);
    stuck = false;
}
