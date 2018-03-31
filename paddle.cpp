#include "paddle.h"
#include "game.h"
#include "level.h"
#include "ball.h"
#include <iostream>

Paddle::Paddle() {
    position.setZ(Game::instance()->getLevel()->side * .5);
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
    if(position.x() - length / 2 < -side / 2) {
        position.setX(-side / 2 + length / 2);
    } else if(position.x() + length / 2 > side / 2) {
        position.setX(side / 2 - length / 2);
    }
}

void Paddle::render() {
    glPopMatrix();
    glTranslated(position.x(), position.y(), position.z());
    glBegin(GL_QUADS);

    glColor3f(1, 0, 0);
    glVertex3d(-length/2, -thickness/2, -thickness/2);
    glVertex3d(length/2, -thickness/2, -thickness/2);
    glVertex3d(length/2, thickness/2, -thickness/2);
    glVertex3d(-length/2, thickness/2, -thickness/2);

    glColor3f(1, 1, 0);
    glVertex3d(-length/2, -thickness/2, -thickness/2);
    glVertex3d(length/2, -thickness/2, -thickness/2);
    glVertex3d(length/2, -thickness/2, thickness/2);
    glVertex3d(-length/2, -thickness/2, thickness/2);

    glColor3f(1, 0, 1);
    glVertex3d(-length/2, -thickness/2, -thickness/2);
    glVertex3d(-length/2, thickness/2, -thickness/2);
    glVertex3d(-length/2, thickness/2, thickness/2);
    glVertex3d(-length/2, -thickness/2, thickness/2);

    glColor3f(0, 1, 1);
    glVertex3d(-length/2, -thickness/2, thickness/2);
    glVertex3d(length/2, -thickness/2, thickness/2);
    glVertex3d(length/2, thickness/2, thickness/2);
    glVertex3d(-length/2, thickness/2, thickness/2);

    glColor3f(0, 1, 0);
    glVertex3d(-length/2, thickness/2, -thickness/2);
    glVertex3d(length/2, thickness/2, -thickness/2);
    glVertex3d(length/2, thickness/2, thickness/2);
    glVertex3d(-length/2, thickness/2, thickness/2);

    glColor3f(0, 0, 1);
    glVertex3d(length/2, -thickness/2, -thickness/2);
    glVertex3d(length/2, thickness/2, -thickness/2);
    glVertex3d(length/2, thickness/2, thickness/2);
    glVertex3d(length/2, -thickness/2, thickness/2);

    glEnd();
}

double Paddle::getCollision(const Ball& ball) {
    double radius = ball.getRadius();
    double ballX = ball.getPosition().x();
    double minX = position.x() - length / 2 - radius;
    double maxX = position.x() + length / 2 + radius;
    return (ballX - minX) / (maxX - minX) * 2 - 1;
}
