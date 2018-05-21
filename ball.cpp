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
        Paddle *pad = Game::instance()->getPaddle();
        if(position.z() + radius > side * .8) {
            visible = false;
            if(Game::instance()->loseBall()) {
                spawn();
            }
        } else if(position.z() - radius < -side * .5) {
            position.setZ(-side * .5 + radius);
            velocity.setZ(-velocity.z());
            hit = true;
        } else if(position.z() + radius < pad->getPosition().z() + pad->getSize().z() * .5 &&
                  position.z() + radius > pad->getPosition().z() - pad->getSize().z() * .2) {
            double collision = pad->getCollision(*this);
            if(collision >= -1 && collision <= 1) {
                if(Game::instance()->getLevel()->getBricks().size() == 0) {
                    stuck = true;
                    Game::instance()->win();
                    return;
                }
                velocity.setZ(-speed);
                velocity.setX(speed * collision);
                hit = true;
            }
        }
        QVector3D nextPos = position + velocity * dt;
        std::vector<Brick*>& bricks = Game::instance()->getLevel()->getBricks();
        bool collided, cx = false, cz = false;
        do {
            collided = false;
            // Compute collisions for each brick
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
                // Discretize the ball in 8 points along a circle.
                for(double angle = 0; angle < 4 * acos(0); angle += .5 * acos(0)) {
                    // Consider a segment that ends where the position of this point will be in the next frame.
                    // Compute segment/segment collision with the 4 brick sides.
                    QVector2D collisionPoint = ballCenter + radius * QVector2D(cos(angle), sin(angle));
                    QVector2D p = collisionPoint;
                    QVector2D q = collisionPoint + ballDeltaPos;
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
                if(collided) {
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
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glColor3d(1, 1, 1);
    gluSphere(quadric, radius, 30, 30);
    gluQuadricTexture(quadric, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, NULL);
    glColor3d(1, 1, 1);
}

void Ball::render(bool icon) {
    if(!icon) {
        if(!visible) {
            return;
        }
        glPushMatrix();
        glTranslated(position.x(), position.y(), position.z());
        glRotated(angle, 1, 1, 0);
    } else {
        glRotated(90, 1, 1, 0);
        glRotated(90, 1, 0, 0);
    }
    render();
    if(!icon) {
        glPopMatrix();
    }
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
    velocity = QVector3D(rand() % 100 / 100. * speed, 0, -speed);
    stuck = false;
}

bool Ball::segmentIntersection(QVector2D a, QVector2D b, QVector2D p, QVector2D q) {
    QVector2D ab = b - a, bp = p - b, bq = q - b, pq = q - p, qb = b - q, qa = a - q;
    return (ab.x() * bp.y() - ab.y() * bp.x() < 0) != (ab.x() * bq.y() - ab.y() * bq.x() < 0) &&
           (pq.x() * qb.y() - pq.y() * qb.x() < 0) != (pq.x() * qa.y() - pq.y() * qa.x() < 0);
}

void Ball::increaseSpeed() {
    speed += 4;
}
