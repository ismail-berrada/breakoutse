#define _USE_MATH_DEFINES

#include "Game.h"
#include <GL/glu.h>
#include <QApplication>
#include <QDesktopWidget>

const unsigned int WIN_WIDTH  = 960;
const unsigned int WIN_HEIGHT = 640;


// Constructeur
Game::Game(QWidget * parent) : QGLWidget(parent) {
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
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

void Game::paintGL() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(.5, 1, .5, 0, 0, 0, 0, 1, 0);
	
    glBegin(GL_QUADS);
    glVertex3f(-.5, 0, -.5);
    glVertex3f(.5, 0, -.5);
    glVertex3f(.5, 0, .5);
    glVertex3f(-.5, 0, .5);
    glEnd();
}
