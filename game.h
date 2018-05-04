#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QTimer>

class Ball;
class Level;
class Paddle;
class UI;
class Text3D;

class Game : public QGLWidget {
    Q_OBJECT

public:
    static Game* instance();
    Game(QWidget * parent = nullptr);
    Level* getLevel() const { return level; };
    Paddle* getPaddle() const { return paddle; };
    Ball* getBall() const { return ball; };
    QFont& getFont() { return font; };
    unsigned int getScore() const { return score; };
    unsigned int getExtraBalls() const { return extraBalls; };
    void addScore(unsigned int val) { score += val; };
    bool loseBall();
    bool keyDown(int key) { return keys[key]; };
    bool keyPressed(int key) { return keys[key] && !previousKeys[key]; };
    bool isOver() const {return gameOver; };

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void update();
    void paintGL();

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

private:
    QTimer timer;
    qint64 gameTime;
    std::map<int, bool> keys;
    std::map<int, bool> previousKeys;
    QFont font;
    Ball *ball;
    Level *level;
    Paddle *paddle;
    UI *ui;
    unsigned int score = 0;
    unsigned int extraBalls = 2;
    bool gameOver = false;
    static Game *inst;
};

#endif // MYGLWIDGET_H
