#include "paddle.h"
#include "game.h"
#include <iostream>

Paddle::Paddle() {

}

void Paddle::update(double dt) {
    if(Game::instance()->keyPressed(Qt::Key_Left)) {
        velocity.setX(-3);
    } else if(Game::instance()->keyPressed(Qt::Key_Right)) {
        velocity.setX(3);
    } else {
        velocity.setX(0);
    }
    position += dt * velocity;
    std::cout << position.x() << " " << position.y() << " " << position.z() << std::endl;
}

void Paddle::render() {
    glPopMatrix();
    glTranslated(position.x(), position.y(), position.z());
    gluCylinder(quadric, 1, 1, 4, 10, 4);
}
