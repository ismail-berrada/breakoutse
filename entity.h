#ifndef ENTITY_H
#define ENTITY_H

#include <QVector3D>
#include <GL/glu.h>

class Entity
{
public:
    Entity();
    Entity(QVector3D position);
    ~Entity();
    void drawBox();
    void drawTexturedBox();
    virtual void update(double dt) = 0;
    virtual void render() = 0;
    QVector3D getPosition() const {return position;};
    QVector3D getSize() const {return size;};

protected:
    QVector3D position;
    QVector3D velocity;
    QVector3D size;
    GLUquadric *quadric;
    bool visible = true;
};

#endif // ENTITY_H
