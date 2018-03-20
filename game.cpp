#define _USE_MATH_DEFINES

#include "Game.h"
#include <GL/glu.h>
#include <QApplication>
#include <QDesktopWidget>

const unsigned int WIN_WIDTH  = 960;
const unsigned int WIN_HEIGHT = 640;
const unsigned int FPS = 60;

// Constructeur
Game::Game(QWidget * parent) : QGLWidget(parent) {
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
    connect(&timer,  &QTimer::timeout, [&] {
        update();
    });
    timer.setInterval(1.0 / FPS);
    timer.start();
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
    //todo: update game elapsed time
    //todo: update game objects
    if(keys[Qt::Key_Left]) {
        position += .005;
    }
    if(keys[Qt::Key_Right]) {
        position -= .005;
    }
    updateGL();
}

void Game::paintGL() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(.3, 1, .3, 0, 0, 0, 0, 1, 0);

    glTranslated(position, 0, 0);
    glBegin(GL_QUADS);
    glVertex3f(-.5, 0, -.5);
    glVertex3f(.5, 0, -.5);
    glVertex3f(.5, 0, .5);
    glVertex3f(-.5, 0, .5);
    glEnd();
}

void Game::keyPressEvent(QKeyEvent * event) {
    event->accept();
    keys[event->key()] = true;
}

void Game::keyReleaseEvent(QKeyEvent * event ) {
    event->accept();
    keys[event->key()] = false;
}
