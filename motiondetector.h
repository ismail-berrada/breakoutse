#ifndef MOTIONDETECTOR_H
#define MOTIONDETECTOR_H

#include <QThread>
#include <QTimer>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

enum MotionType {
    None, Left, Right, Stop
};

class MotionDetector : public QThread {
    Q_OBJECT
public:
    MotionDetector();
     void run();

signals:
     void motionDetected(MotionType motionType);

private slots:
     void updateCapture();
     void endCapture();

private:
     int frameWidth;
     int frameHeight;
     int divx;
     int divy;
     int divWidth;
     int divHeight;
     int templateWidth;
     int templateHeight;
     VideoCapture cap;
     Mat frame1;
     Mat frame2;
     Mat frame1Gray;
     Mat frame2Gray;
     Mat resultImage;
     QTimer timer;
     MotionType lastMotion;
};

#endif // MOTIONDETECTOR_H
