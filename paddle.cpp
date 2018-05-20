#include "paddle.h"
#include "game.h"
#include "level.h"
#include "ball.h"
#include <iostream>

GLuint Paddle::texture = 0;
QImage Paddle::image;

Paddle::Paddle() {
    if(!texture) {
        image = QGLWidget::convertToGLFormat(QImage(":/textures/textures/paddle.png"));
        glGenTextures(1, &texture);
    }
    position.setZ(Game::instance()->getLevel()->side * .5);
    size = QVector3D(8, 1, 1);
}

void Paddle::update(double dt) {
    if(Game::instance()->keyPressed(Qt::Key_Left)) {
        move(false);

    } else if(Game::instance()->keyPressed(Qt::Key_Right)) {
        move(true);
    }
    if(Game::instance()->keyPressed(Qt::Key_Space)) {
        stop();
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

void Paddle::move(bool right) {
    velocity.setX((right * 2 - 1) * 40);
}

void Paddle::stop() {
    velocity.setX(0);
    Game::instance()->getBall()->launch();
}

void Paddle::render() {
    glPushMatrix();
    glTranslated(position.x(), position.y(), position.z());
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    drawTexturedBox();
    glBindTexture(GL_TEXTURE_2D, NULL);
    glPopMatrix();
}

double Paddle::getCollision(const Ball& ball) {
    double radius = ball.getRadius();
    double ballX = ball.getPosition().x();
    double minX = position.x() - size.x() / 2 - radius;
    double maxX = position.x() + size.x() / 2 + radius;
    return (ballX - minX) / (maxX - minX) * 2 - 1;
}

void Paddle::reset() {
    position.setX(0);
    velocity.setX(0);
}
