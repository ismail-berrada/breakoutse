#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QVector3D>
#include "motiondetector.h"

class Ball;
class Level;
class Paddle;
class UI;
class Text3D;

enum GameState {
    Menu, MovingIn, Building, Playing, MovingOut
};

// The main game class, stores every game objects and handles the different game states.
class Game : public QGLWidget {
    Q_OBJECT

public:
    static Game* instance();
    Game(MotionDetector &motionDetector);

    // Called to start the game, resets the level and moves the camera down.
    void quitMenu();

    Level* getLevel() const { return level; };
    Paddle* getPaddle() const { return paddle; };
    Ball* getBall() const { return ball; };
    QFont& getFont() { return font; };
    unsigned int getScore() const { return score; };
    unsigned int getExtraBalls() const { return extraBalls; };
    void addScore(unsigned int val) { score += val; };

    bool loseBall();
    void win();

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

private slots:
    void motionDetected(MotionType motionType);

signals:
    void onUpdate();
    void onEnd();

private:
    QTimer timer;
    QTimer motionTimer;
    qint64 gameTime;

    // Two maps to detect a new key press.
    std::map<int, bool> keys;
    std::map<int, bool> previousKeys;

    QFont font;

    Ball *ball;
    Level *level;
    Paddle *paddle;
    UI *ui;
    MotionDetector *motionDetector;
    unsigned int score = 0;
    unsigned int extraBalls = 2;
    bool gameOver = false;
    double transitionTime;
    double transitionTimer;
    GameState state = Menu;

    // Camera positions and lookAt points
    QVector3D cameraPosition;
    QVector3D cameraLookAt;
    QVector3D gameLookAt;
    QVector3D gameCameraPosition;
    QVector3D menuLookAt;
    QVector3D menuCameraPosition;
    static Game *inst;
};

#endif // MYGLWIDGET_H
