#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QTimer>

class Game : public QGLWidget {
    Q_OBJECT

public:
    Game(QWidget * parent = nullptr);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void update();
    void paintGL();

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

private:
    QTimer timer;
    double position = 0;
    std::map<int, bool> keys;
};

#endif // MYGLWIDGET_H
