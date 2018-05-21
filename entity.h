#ifndef ENTITY_H
#define ENTITY_H

#include <QVector3D>
#include <GL/glu.h>

// An abstract class that represent any moving game object.
class Entity
{
public:
    Entity();
    Entity(QVector3D position);
    ~Entity();

    // Draw a box at the entity's position
    void drawBox();

    // Same but with a texture
    void drawTexturedBox();

    // Called when the game updates
    virtual void update(double dt) = 0;

    // Called when the game renders
    virtual void render() = 0;
    QVector3D getPosition() const {return position;};
    QVector3D getSize() const {return size;};
    void setPosition(QVector3D position) {this->position = position;};

protected:
    QVector3D position;
    QVector3D velocity;
    QVector3D size;
    GLUquadric *quadric;
    bool visible = true;
};

#endif // ENTITY_H
