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

// Used to detect three different gestures with the user webcam.
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
     // The size of the captured frames
     int frameWidth;
     int frameHeight;

     // The number of matching points per dimension, set to 1 by default. (Center only)
     int divx;
     int divy;
     int divWidth;
     int divHeight;

     // The size of the template matched between frames
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
