#define _USE_MATH_DEFINES

#include "game.h"
#include <GL/glu.h>
#include <QApplication>
#include <QDesktopWidget>
#include <QDateTime>
#include "ball.h"
#include "level.h"
#include "paddle.h"

const unsigned int WIN_WIDTH  = 960;
const unsigned int WIN_HEIGHT = 640;
const unsigned int FPS = 60;

Game* Game::inst = 0;

Game* Game::instance() {
    return inst;
}

Game::Game(QWidget * parent) : QGLWidget(parent) {
    Game::inst = this;
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
    connect(&timer,  &QTimer::timeout, [&] {
        update();
    });
    timer.setInterval(1.0 / FPS);
    timer.start();
    gameTime = QDateTime::currentMSecsSinceEpoch();
    level = new Level();
    ball = new Ball();
    paddle = new Paddle();
}

void Game::initializeGL() {
    glEnable(GL_DEPTH_TEST);
}

void Game::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, width / (double)height, .01, 1000);
}

void Game::update() {
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    double dt = (now - gameTime) / 1000.;
    gameTime = now;
    paddle->update(dt);
    ball->update(dt);
    updateGL();
    previousKeys = std::map<int, bool>(keys);
}

void Game::paintGL() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    double a = sin(gameTime * .003);
    //gluLookAt(paddle->getPosition().x(), 15, level->side * .6, ball->getPosition().x(), ball->getPosition().y(), ball->getPosition().z(), 0, 1, 0);
    gluLookAt(0, 15, level->side * .6, 0, 0, 0, 0, 1, 0);
    glPushMatrix();
    level->render();
    ball->render();
    paddle->render();
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
