#include "level.h"
#include "brick.h"
#include <QGLWidget>

Level::Level() {
    wall = QGLWidget::convertToGLFormat(QImage(":/textures/textures/wall.png"));
    ground = QGLWidget::convertToGLFormat(QImage(":/textures/textures/ground.png"));
    glGenTextures(1, &wallTexture);
    glGenTextures(1, &groundTexture);
}

Level::~Level() {
    bricks.clear();
}

void Level::build() {
    totalBricks = 0;
    bricks.clear();
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 5; j++) {
            int jj = 9 - j;
            int ci = 6, cj = 5;
            int di = abs(i - ci), dj = abs(j - cj) + 2;
            int d = di*di + dj*dj;
            if(rand() % 70 > d) {
                totalBricks += 2;
                bricks.push_back(new Brick(QVector3D(-13.5 + j * 3, -10, -13.5 + i)));
                bricks.push_back(new Brick(QVector3D(-13.5 + jj * 3, -10, -13.5 + i)));
            }
        }
    }
}

void Level::update(double dt) {
    for(auto b : bricks) {
        b->update(dt);
    }
}

void Level::render() {
    const double wallHeight = 50, p = 1. / wall.width();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wall.width(), wall.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, wall.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);

    //back
    glTexCoord2d(0., 0);
    glVertex3d(-side / 2, -wallHeight, -side / 2);
    glTexCoord2d(0, wallHeight / 2);
    glVertex3d(-side / 2, wallHeight, -side / 2);
    glTexCoord2d(side / 4, wallHeight / 2);
    glVertex3d(side / 2, wallHeight, -side / 2);
    glTexCoord2d(side / 4, 0);
    glVertex3d(side / 2, -wallHeight, -side / 2);

    //side walls
    glTexCoord2d(0., 0);
    glVertex3d(side / 2, -wallHeight, -side / 2);
    glTexCoord2d(0, wallHeight / 2);
    glVertex3d(side / 2, wallHeight, -side / 2);
    glTexCoord2d(side / 2, wallHeight / 2);
    glVertex3d(side / 2, wallHeight, side);
    glTexCoord2d(side / 2, 0);
    glVertex3d(side / 2, -wallHeight, side);

    glTexCoord2d(0., 0);
    glVertex3d(-side / 2, -wallHeight, -side / 2);
    glTexCoord2d(0, wallHeight / 2);
    glVertex3d(-side / 2, wallHeight, -side / 2);
    glTexCoord2d(side / 2, wallHeight / 2);
    glVertex3d(-side / 2, wallHeight, side);
    glTexCoord2d(side / 2, 0);
    glVertex3d(-side / 2, -wallHeight, side);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, groundTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ground.width(), ground.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, ground.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBegin(GL_QUADS);

    //ground
    glTexCoord2d(0., 0);
    glVertex3d(-side / 2, -1, -side / 2);
    glTexCoord2d(side / 2, 0);
    glVertex3d(side / 2, -1, -side / 2);
    glTexCoord2d(side / 2, side);
    glVertex3d(side / 2, -1, side);
    glTexCoord2d(0, side);
    glVertex3d(-side / 2, -1, side);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, NULL);

    for(auto b : bricks) {
        b->render();
    }
}
