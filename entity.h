#ifndef ENTITY_H
#define ENTITY_H

#include <QVector3D>
#include <GL/glu.h>

class Entity
{
public:
    Entity();
    ~Entity();
    virtual void update(double dt) = 0;
    virtual void render() = 0;

protected:
    QVector3D position;
    QVector3D velocity;
    GLUquadric *quadric;
};

#endif // ENTITY_H
