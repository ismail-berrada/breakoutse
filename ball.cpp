#include "ball.h"
#include "game.h"
#include "level.h"
#include "paddle.h"
#include <iostream>

GLuint Ball::texture = 0;
QImage Ball::image;

Ball::Ball() {
    if(!texture) {
        image = QGLWidget::convertToGLFormat(QImage(":/textures/textures/ball.png"));
        glGenTextures(1, &texture);
    }
    spawn();
}

void Ball::update(double dt) {
    angle += dt * 360;
    if(stuck) {
        position.setX(Game::instance()->getPaddle()->getPosition().x());
        position.setZ(Game::instance()->getPaddle()->getPosition().z() - radius);
    } else {
        bool hit = false;
        double side = Game::instance()->getLevel()->side;
        if(position.x() - radius < -side * .5) {
            position.setX(-side * .5 + radius);
            velocity.setX(-velocity.x());
            hit = true;
        } else if(position.x() + radius > side * .5) {
            position.setX(side * .5 - radius);
            velocity.setX(-velocity.x());
            hit = true;
        }
        if(position.z() + radius > side * .8) {
            visible = false;
            if(Game::instance()->loseBall()) {
                spawn();
            }
        } else if(position.z() - radius < -side * .5) {
            position.setZ(-side * .5 + radius);
            velocity.setZ(-velocity.z());
            hit = true;
        } else if(position.z() + radius > side * .5) {
            double collision = Game::instance()->getPaddle()->getCollision(*this);
            if(collision >= -1 && collision <= 1) {
                position.setZ(side * .5 - radius);
                velocity.setZ(-velocity.z());
                velocity.setX(2 * abs(velocity.z()) * collision);
                hit = true;
            }
        }
        QVector3D nextPos = position + velocity * dt;
        std::vector<Brick*>& bricks = Game::instance()->getLevel()->getBricks();
        bool collided, cx = false, cz = false;
        do {
            collided = false;
            for(std::vector<Brick*>::iterator it = bricks.begin(); it != bricks.end(); ++it) {
                Brick *brick = *it;
                QVector2D brickCenter(brick->getPosition().x(), brick->getPosition().z());
                QVector2D brickSize(brick->getSize().x(), brick->getSize().z());
                QVector2D a = brickCenter - brickSize * .5;
                QVector2D b = a + QVector2D(brickSize.x(), 0);
                QVector2D c = b + QVector2D(0, brickSize.y());
                QVector2D d = c - QVector2D(brickSize.x(), 0);
                QVector2D ballCenter(position.x(), position.z());
                QVector2D ballDeltaPos(velocity.x() * dt, velocity.z() * dt);
                QVector2D p = ballCenter;
                QVector2D q = ballCenter + ballDeltaPos;
                if(segmentIntersection(p, q, a, b) ||
                        segmentIntersection(p, q, c, d)) {
                    cz = true;
                    collided = true;
                }
                if(segmentIntersection(p, q, b, c) ||
                        segmentIntersection(p, q, d, a)) {
                    cx = true;
                    collided = true;
                }
                if(collided) {
                    bricks.erase(it);
                    Game::instance()->addScore(50);
                    break;
                }
            }
        } while(collided);
        if(cx) {
            velocity.setX(-velocity.x());
        }
        if(cz) {
            velocity.setZ(-velocity.z());
        }
        position += velocity * dt;
    }
}

void Ball::render() {
    if(!visible) return;
    glPushMatrix();
    glTranslated(position.x(), position.y(), position.z());
    glRotated(angle, 1, 1, 0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glColor3d(1, 1, 1);
    gluSphere(quadric, radius, 30, 30);
    gluQuadricTexture(quadric, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, NULL);
    glColor3d(1, 1, 1);
    glPopMatrix();
}

void Ball::spawn() {
    position = QVector3D(0, 0, 0);
    velocity = QVector3D(0, 0, 0);
    stuck = true;
    visible = true;
}

void Ball::launch() {
    if(!stuck) {
        return;
    }
    velocity = QVector3D(rand() % 100 / 20. * speed, 0, -speed * 20);
    stuck = false;
}

bool Ball::segmentIntersection(QVector2D a, QVector2D b, QVector2D p, QVector2D q) {
    QVector2D ab = b - a, bp = p - b, bq = q - b, pq = q - p, qb = b - q, qa = a - q;
    return (ab.x() * bp.y() - ab.y() * bp.x() < 0) != (ab.x() * bq.y() - ab.y() * bq.x() < 0) &&
           (pq.x() * qb.y() - pq.y() * qb.x() < 0) != (pq.x() * qa.y() - pq.y() * qa.x() < 0);
}
