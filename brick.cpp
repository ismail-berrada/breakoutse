#include "brick.h"
#include <QGLWidget>
#include <iostream>

GLuint Brick::texture = 0;
QImage Brick::image;

Brick::Brick(QVector3D position) : Entity(position) {
    destroyed = false;
    size = QVector3D(2.8, .9, .9);
    if(!texture) {
        image = QGLWidget::convertToGLFormat(QImage(":/textures/textures/brick.png"));
        glGenTextures(1, &texture);
    }
    spawnTime = .3 + .7 * rand() / (float)RAND_MAX;
    spawnTimer = spawnTime;
    position.setY(-10);
}

Brick::~Brick() {

}

void Brick::update(double dt) {
    if(spawnTimer > 0) {
        spawnTimer -= dt;
        if(spawnTimer < 0) {
            position.setY(0);
        } else {
            double t = spawnTimer / spawnTime;
            position.setY(-t * t * 3);
        }
    }
}

void Brick::render() {
    glPushMatrix();
    glTranslated(position.x(), position.y(), position.z());
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    drawTexturedBox();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, NULL);
}
