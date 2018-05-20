#define _USE_MATH_DEFINES

#include "game.h"
#include <GL/glu.h>
#include <QApplication>
#include <QDesktopWidget>
#include <QDateTime>
#include <QFontDatabase>
#include <iostream>
#include "math.h"
#include "ball.h"
#include "level.h"
#include "paddle.h"
#include "ui.h"

const unsigned int WIN_WIDTH  = 960;
const unsigned int WIN_HEIGHT = 640;
const unsigned int FPS = 60;

Game* Game::inst = 0;

Game* Game::instance() {
    return inst;
}

Game::Game(MotionDetector &motionDetector) : QGLWidget() {
    Game::inst = this;
    glEnable(GL_TEXTURE_2D);
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    //showFullScreen();

    int id = QFontDatabase::addApplicationFont(":/fonts/fonts/XLMono.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(family);

    move(QApplication::desktop()->screen()->rect().center() - rect().center());
    gameTime = QDateTime::currentMSecsSinceEpoch();
    //animTime = 0;

    level = new Level();
    ball = new Ball();
    paddle = new Paddle();
    connect(&timer,  &QTimer::timeout, [&] {
        update();
    });
    timer.setInterval(1.0 / FPS);
    timer.start();

    this->motionDetector = &motionDetector;
    connect(&motionDetector, SIGNAL(motionDetected(MotionType)), this, SLOT(motionDetected(MotionType)));
    connect(this, SIGNAL(onUpdate()), &motionDetector, SLOT(updateCapture()));

    connect(&motionTimer,  &QTimer::timeout, [&] {
        emit onUpdate();
    });
    motionTimer.setInterval(.1);
    motionTimer.start();

    menuCameraPosition = QVector3D(0, 25, -level->side * .2);
    menuLookAt = QVector3D(0, 25, -level->side * .5);
    gameCameraPosition = QVector3D(0, 20, level->side * .4);
    gameLookAt = QVector3D(0, 0, 0);

    transitionTime = 2;
    transitionTimer = transitionTime;
}

void Game::initializeGL() {
    glEnable(GL_DEPTH_TEST | GL_LIGHTING);
    ui = new UI();
}

void Game::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, width / (double)height, .01, 1000);
}

void Game::update() {
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    double dt = (now - gameTime) / 1000.;
    gameTime = now;
    if(state == Playing) {
        paddle->update(dt);
        ball->update(dt);
    } else if(state == MovingIn || state == MovingOut) {
        transitionTimer -= dt;
        if(transitionTimer < 0) {
            cameraPosition = gameCameraPosition;
            transitionTimer = transitionTime;
            state = state == MovingIn ? Playing : Menu;
        } else {
            double t = transitionTimer / transitionTime;
            if(state == MovingIn) {
                t = 1 - t;
            }
            double p = (sin(t * acos(0) * 2 - acos(0)) + 1) * .5;
            cameraPosition = (1 - p) * menuCameraPosition + p * gameCameraPosition;
            cameraLookAt = (1 - p) * menuLookAt + p * gameLookAt;
        }
    } else if(state == Menu) {
        if(keyPressed(Qt::Key_Space)) {
            state = MovingIn;
            transitionTimer = transitionTime;
        }
    }
    ui->update(dt);
    updateGL();
    previousKeys = std::map<int, bool>(keys);
}

void Game::paintGL() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    double px = paddle->getPosition().x() * .5;
    double cy = 20;
    if(state == Menu) {
        gluLookAt(menuCameraPosition.x(), menuCameraPosition.y(), menuCameraPosition.z(),
                 menuLookAt.x(), menuLookAt.y(), menuLookAt.z(),
                  0, 1, 0);
    } else if(state == MovingIn || state == MovingOut) {
        gluLookAt(cameraPosition.x(), cameraPosition.y(), cameraPosition.z(),
                  cameraLookAt.x(), cameraLookAt.y(), cameraLookAt.z(),
                  0, 1, 0);
    } else if(state == Playing) {
        gluLookAt(px * .3, cy, level->side * .4 + fabs(px * px * .02), 0, 0, 0, 0, 1, 0);
    }
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    level->render();
    ball->render();
    paddle->render();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    ui->render();
}

bool Game::loseBall() {
    if(!extraBalls) {
        gameOver = true;
        state = MovingOut;
        return false;
    }
    extraBalls--;
    return true;
}

void Game::keyPressEvent(QKeyEvent * event) {
    event->accept();
    keys[event->key()] = true;
}

void Game::keyReleaseEvent(QKeyEvent * event ) {
    event->accept();
    keys[event->key()] = false;
}

void Game::motionDetected(MotionType motionType) {
    if(motionType == Left) {
        if(state == Playing) {
            paddle->move(false);
        }
    } else if(motionType == Right) {
        if(state == Playing) {
            paddle->move(true);
        }
    }
}
