#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

class Game : public QGLWidget {
    Q_OBJECT

public:
    Game(QWidget * parent = nullptr);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:

};

#endif // MYGLWIDGET_H
