#include "entity.h"

Entity::Entity() {
    quadric = gluNewQuadric();
}

Entity::~Entity() {
    gluDeleteQuadric(quadric);
}
