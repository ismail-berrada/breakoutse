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
}

Brick::~Brick() {
    std::cout << ("Brick deleted") << std::endl;
}

void Brick::update(double dt) {

}

void Brick::render() {
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
