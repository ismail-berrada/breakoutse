#include "level.h"
#include "GL/gl.h"

Level::Level() {

}

void Level::render() {
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 0, 0);
    glVertex3d(-side / 2, 0, -side / 2);
    glVertex3d(side / 2, 0, -side / 2);
    glColor3f(1, 1, 1);
    glVertex3d(side / 2, 0, -side / 2);
    glVertex3d(side / 2, 0, side / 2);
    glVertex3d(-side / 2, 0, side / 2);
    glVertex3d(-side / 2, 0, -side / 2);
    glColor3f(1, 0, 0);
    glVertex3d(-side / 2, 0, -side / 2);
    glColor3f(1, 1, 1);
    glEnd();
}
