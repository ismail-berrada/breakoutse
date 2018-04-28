#ifndef BRICK_H
#define BRICK_H

#include <QImage>
#include <QRect>
#include "entity.h"

class Brick : public Entity {

  public:
    Brick(QVector3D position);
    ~Brick();
    void update(double dt);
    void render();

  public:
    bool isDestroyed() {return destroyed; };
    void setDestroyed(bool d) {destroyed = d; };

  private:
    bool destroyed;
    static GLuint texture;
    static QImage image;
};

#endif // BRICK_H
