#include "ui.h"
#include "text3d.h"
#include "game.h"
#include "level.h"
#include "ball.h"
#include <sstream>
#include <string>
#include <iomanip>

UI::UI() {
    text = new Text3D();
    text->initFont(Game::instance()->getFont(), .05);
    score = 0;
}

UI::~UI() {
    delete text;
}

void UI::update(double dt) {
    angle += 1000 * dt;
    double cur = Game::instance()->getScore();
    score += dt * 6 * (cur - score);
}

void UI::render() {
    glDisable(GL_TEXTURE_2D);

    std::stringstream ss;
    std::string scoreString;
    ss << std::setfill('0') << std::setw(5) << ceil(score);
    ss >> scoreString;

    // display menu
    glPushMatrix();
    glTranslated(0, 27, -Game::instance()->getLevel()->side * .499);
    glScaled(.5, .5, .5);
    text->print(QString("BreakouTSE"));
    glPopMatrix();

    //display gameplay UI
    glPushMatrix();
    glTranslated(0, 7, -8);

    glPushMatrix();
    glScaled(.5, .5, .5);
    glColor3f(1, 1, 1);
    text->print(QString(scoreString.c_str()));
    glColor3f(1, 1, 0);
    glTranslated(0, 0, -2);
    text->print(QString(scoreString.c_str()));
    glPopMatrix();

    glTranslated(0, 7, 0);
    //glScaled(.3, .3, .3);
    glEnable(GL_TEXTURE_2D);
    int ballCount = Game::instance()->getExtraBalls();
    double width = 5;
    double step = width / (ballCount - 1);
    for(int i = 0; i < ballCount; i++) {
        glPushMatrix();
        glTranslated((i - (double)(ballCount - 1) * .5) * width * .5, 0, 0);
        Game::instance()->getBall()->render(true);
        glPopMatrix();
    }
    glPopMatrix();
}

void UI::resetScore() {
    score = 0;
}
