#include "paddle.h"
#include "game.h"
#include "level.h"
#include "ball.h"
#include <iostream>

Paddle::Paddle() {
    position.setZ(Game::instance()->getLevel()->side * .5);
    size = QVector3D(6, 1, 1);
}

void Paddle::update(double dt) {
    if(Game::instance()->keyPressed(Qt::Key_Left)) {
        velocity.setX(-40);
    } else if(Game::instance()->keyPressed(Qt::Key_Right)) {
        velocity.setX(40);
    }
    if(Game::instance()->keyPressed(Qt::Key_Space)) {
        Game::instance()->getBall()->launch();
    }
    double side = Game::instance()->getLevel()->side;
    velocity -= velocity * friction * dt;
    position += dt * velocity;
    if(position.x() - size.x() / 2 < -side / 2) {
        position.setX(-side / 2 + size.x() / 2);
    } else if(position.x() + size.x() / 2 > side / 2) {
        position.setX(side / 2 - size.x() / 2);
    }
}

void Paddle::render() {
    glPopMatrix();
    glTranslated(position.x(), position.y(), position.z());
    drawBox();
}

double Paddle::getCollision(const Ball& ball) {
    double radius = ball.getRadius();
    double ballX = ball.getPosition().x();
    double minX = position.x() - size.x() / 2 - radius;
    double maxX = position.x() + size.x() / 2 + radius;
    return (ballX - minX) / (maxX - minX) * 2 - 1;
}
