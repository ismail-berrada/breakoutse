#include "ui.h"
#include "text3d.h"
#include "game.h"
#include <sstream>
#include <string>
#include <iomanip>

UI::UI() {
    scoreText = new Text3D();
    scoreText->initFont(Game::instance()->getFont(), .05);
    score = 0;
}

UI::~UI() {
    delete scoreText;
}

void UI::update(double dt) {
    angle += 1000 * dt;
    double cur = Game::instance()->getScore();
    score += dt * 6 * (cur - score);
}

void UI::render() {
    std::stringstream ss;
    std::string scoreString;
    ss << std::setfill('0') << std::setw(5) << ceil(score);
    ss >> scoreString;
    glPushMatrix();
    glTranslated(0, 7, -8);

    glPushMatrix();
    glScaled(.5, .5, .5);
    glColor3f(1, 1, 1);
    scoreText->print(QString(scoreString.c_str()));
    glColor3f(1, 1, 0);
    glTranslated(0, 0, -2);
    scoreText->print(QString(scoreString.c_str()));
    glPopMatrix();

    glTranslated(0, 6, 0);
    glScaled(.3, .3, .3);
    scoreText->print("x0");

    glPopMatrix();
}
