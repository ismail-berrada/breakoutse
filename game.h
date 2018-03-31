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

class Game : public QGLWidget {
    Q_OBJECT

public:
    static Game* instance();
    Game(QWidget * parent = nullptr);
    Level* getLevel() const { return level; };
    Paddle* getPaddle() const { return paddle; };
    bool keyPressed(int key) { return keys[key]; };

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
    Ball *ball;
    Level *level;
    Paddle *paddle;
    static Game *inst;
};

#endif // MYGLWIDGET_H
