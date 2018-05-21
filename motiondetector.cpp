#include "motiondetector.h"
#include <cstdio>
#include <iostream>
using namespace cv;
using namespace std;

MotionDetector::MotionDetector() : frameWidth(320), frameHeight(240),
    divx(1), divy(1),
    templateWidth(25), templateHeight(25),
    cap(0) {
    divWidth = frameWidth / divx;
    divHeight = frameHeight / divy;
    lastMotion = None;
}

void MotionDetector::run() {
    cout << "width :" << cap.get(CV_CAP_PROP_FRAME_WIDTH) << endl;
    cout << "height :" << cap.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;
    cap.set(CV_CAP_PROP_FRAME_WIDTH, frameWidth);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, frameHeight);
    if(!cap.isOpened()) {
        cerr<<"Error openning the default camera"<<endl;
        return;
    }
    while(frame1.empty()) {
        cap >> frame1;
    }
    cv::flip(frame1, frame1, 1);
    cv::cvtColor(frame1, frame1Gray, COLOR_BGR2GRAY);
    int result_cols = frame1.cols - templateWidth + 1;
    int result_rows = frame1.rows - templateHeight + 1;
    resultImage.create(result_cols, result_rows, CV_32FC1);
    namedWindow("Camera", 1);

    exec();
}

void MotionDetector::updateCapture() {
    cap >> frame2;
    if(frame2.empty()) return;
    cv::flip(frame2, frame2, 1);
    cv::cvtColor(frame2, frame2Gray, COLOR_BGR2GRAY);
    vector<Point> vectors;
    for(int i = 0; i < divy; i++) {
        for(int j = 0; j < divx; j++) {
            Rect workingRect(j * divWidth, i * divHeight, divWidth, divHeight);
            Point center(workingRect.x + workingRect.width / 2, workingRect.y + workingRect.height / 2);
            Rect templateRect(workingRect.x + (workingRect.width - templateWidth) / 2,
                              workingRect.y + (workingRect.height - templateHeight) / 2,
                              templateWidth, templateHeight);
            Mat templateImage(frame1Gray, templateRect);
            matchTemplate(frame2Gray, templateImage, resultImage, TM_CCORR_NORMED);
            double minVal, maxVal; Point minLoc, maxLoc;
            minMaxLoc(resultImage, &minVal, &maxVal, &minLoc, &maxLoc);
            Point vect(maxLoc.x + (templateWidth - workingRect.width) / 2, maxLoc.y + (templateHeight - workingRect.height) / 2);
            vect -= Point(workingRect.x, workingRect.y);
            vectors.push_back(vect);
            rectangle(frame2, Rect(j * divWidth, i * divHeight, divWidth + 1, divHeight + 1), Scalar(255, 255, 0), 1);
            Point p(vect.x, vect.y);
            arrowedLine(frame2, center, center + p, Scalar(255, 255, 255), 1);
        }
    }
    imshow("Camera", frame2);
    swap(frame1Gray, frame2Gray);
    int nbLeft = 0, nbRight = 0, nbUp = 0;
    for(v : vectors) {
        if(v.x < -20) {
            nbLeft++;
        } else if(v.x > 20) {
            nbRight++;
        } else if(v.y < -20) {
            nbUp++;
        }
    }
    int total = divx * divy;
    MotionType motion = None;
    if(nbLeft * 4 > total) {
        motion = Left;
        cout << "left" << endl;
    }
    if(nbRight * 4 > total) {
        motion = Right;
        cout << "right" << endl;
    }
    if(nbUp * 4 > total) {
        motion = Stop;
        cout << "stop" << endl;
    }
    if(lastMotion == motion && motion != None) {
        emit motionDetected(motion);
    }
    lastMotion = motion;
}

void MotionDetector::endCapture() {
    quit();
}
