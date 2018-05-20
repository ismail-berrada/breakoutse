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
}

void Game::initializeGL() {
    glEnable(GL_DEPTH_TEST | GL_LIGHTING);
    ui = new UI();
}

void Game::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(85, width / (double)height, .01, 1000);
}

void Game::update() {
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    double dt = (now - gameTime) / 1000.;
    //animTime += dt;
    gameTime = now;
    paddle->update(dt);
    ball->update(dt);
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
    /*if(animTime <= 5) {
        double t = animTime / 5;
        t *= t;
        cy = t * 20;
    }*/
    gluLookAt(px * .3, cy, level->side * .4 + fabs(px * px * .02), px * .1, 0, 0, 0, 1, 0);
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
        paddle->move(false);
    } else if(motionType == Right) {
        paddle->move(true);
    }
}
