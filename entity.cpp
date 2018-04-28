#include "entity.h"

Entity::Entity() {
    quadric = gluNewQuadric();
}

Entity::Entity(QVector3D position) {
    quadric = gluNewQuadric();
    this->position = position;
}

Entity::~Entity() {
    gluDeleteQuadric(quadric);
}

void Entity::drawBox() {
    glBegin(GL_QUADS);

    glColor3f(1, 0, 0);
    glVertex3d(-size.x()/2, -size.y()/2, -size.z()/2);
    glVertex3d(size.x()/2, -size.y()/2, -size.z()/2);
    glVertex3d(size.x()/2, size.y()/2, -size.z()/2);
    glVertex3d(-size.x()/2, size.y()/2, -size.z()/2);

    glColor3f(1, 1, 0);
    glVertex3d(-size.x()/2, -size.y()/2, -size.z()/2);
    glVertex3d(size.x()/2, -size.y()/2, -size.z()/2);
    glVertex3d(size.x()/2, -size.y()/2, size.z()/2);
    glVertex3d(-size.x()/2, -size.y()/2, size.z()/2);

    glColor3f(1, 0, 1);
    glVertex3d(-size.x()/2, -size.y()/2, -size.z()/2);
    glVertex3d(-size.x()/2, size.y()/2, -size.z()/2);
    glVertex3d(-size.x()/2, size.y()/2, size.z()/2);
    glVertex3d(-size.x()/2, -size.y()/2, size.z()/2);

    glColor3f(0, 1, 1);
    glVertex3d(-size.x()/2, -size.y()/2, size.z()/2);
    glVertex3d(size.x()/2, -size.y()/2, size.z()/2);
    glVertex3d(size.x()/2, size.y()/2, size.z()/2);
    glVertex3d(-size.x()/2, size.y()/2, size.z()/2);

    glColor3f(0, 1, 0);
    glVertex3d(-size.x()/2, size.y()/2, -size.z()/2);
    glVertex3d(size.x()/2, size.y()/2, -size.z()/2);
    glVertex3d(size.x()/2, size.y()/2, size.z()/2);
    glVertex3d(-size.x()/2, size.y()/2, size.z()/2);

    glColor3f(0, 0, 1);
    glVertex3d(size.x()/2, -size.y()/2, -size.z()/2);
    glVertex3d(size.x()/2, size.y()/2, -size.z()/2);
    glVertex3d(size.x()/2, size.y()/2, size.z()/2);
    glVertex3d(size.x()/2, -size.y()/2, size.z()/2);

    glEnd();
}

void Entity::drawTexturedBox() {
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);

    glTexCoord2d(0, 0);
    glVertex3d(-size.x()/2, -size.y()/2, -size.z()/2);
    glTexCoord2d(1, 0);
    glVertex3d(size.x()/2, -size.y()/2, -size.z()/2);
    glTexCoord2d(1, 1);
    glVertex3d(size.x()/2, size.y()/2, -size.z()/2);
    glTexCoord2d(0, 1);
    glVertex3d(-size.x()/2, size.y()/2, -size.z()/2);

    glTexCoord2d(0, 0);
    glVertex3d(-size.x()/2, -size.y()/2, -size.z()/2);
    glTexCoord2d(1, 0);
    glVertex3d(size.x()/2, -size.y()/2, -size.z()/2);
    glTexCoord2d(1, 1);
    glVertex3d(size.x()/2, -size.y()/2, size.z()/2);
    glTexCoord2d(0, 1);
    glVertex3d(-size.x()/2, -size.y()/2, size.z()/2);

    glVertex3d(-size.x()/2, -size.y()/2, -size.z()/2);
    glVertex3d(-size.x()/2, size.y()/2, -size.z()/2);
    glVertex3d(-size.x()/2, size.y()/2, size.z()/2);
    glVertex3d(-size.x()/2, -size.y()/2, size.z()/2);

    glTexCoord2d(0, 0);
    glVertex3d(-size.x()/2, -size.y()/2, size.z()/2);
    glTexCoord2d(1, 0);
    glVertex3d(size.x()/2, -size.y()/2, size.z()/2);
    glTexCoord2d(1, 1);
    glVertex3d(size.x()/2, size.y()/2, size.z()/2);
    glTexCoord2d(0, 1);
    glVertex3d(-size.x()/2, size.y()/2, size.z()/2);

    glTexCoord2d(0, 0);
    glVertex3d(-size.x()/2, size.y()/2, -size.z()/2);
    glTexCoord2d(1, 0);
    glVertex3d(size.x()/2, size.y()/2, -size.z()/2);
    glTexCoord2d(1, 1);
    glVertex3d(size.x()/2, size.y()/2, size.z()/2);
    glTexCoord2d(0, 1);
    glVertex3d(-size.x()/2, size.y()/2, size.z()/2);

    glVertex3d(size.x()/2, -size.y()/2, -size.z()/2);
    glVertex3d(size.x()/2, size.y()/2, -size.z()/2);
    glVertex3d(size.x()/2, size.y()/2, size.z()/2);
    glVertex3d(size.x()/2, -size.y()/2, size.z()/2);

    glEnd();
}
