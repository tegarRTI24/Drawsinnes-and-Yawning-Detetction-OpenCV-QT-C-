#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H
//opencv inculdes
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/core/types_c.h"
#include "opencv2/face.hpp"
#include "opencv2/face/facemarkLBF.hpp"
#include <opencv2/core/mat.hpp>
#include <stdio.h>
#include <math.h>
#include <tuple>
#include <iostream>


//qt & C++ includes
#include <QImage>
#include <vector>

using namespace std;
using namespace cv;
using namespace cv::face;

class FaceDetector
{
public:
    FaceDetector();

public slots:
    QImage detect(Mat frame);
    float yawningRatio (vector<Point2f> landmarks, int points[]);
    Point middlePoint(Point p1, Point p2);
    void isolate( Mat frame, vector<Point2f> landmarks, int points[]);
    void isolate_eye( Mat frame, vector<Point2f> landmarks, int points[]);
    float blinkingRatio (vector<Point2f> landmarks, int points[]);

private:

    String                   cascade_face_name;
    String                   cascade_eye_name;
    CascadeClassifier        face_cascade;
    CascadeClassifier        eye_cascade;
    QList<CvScalar>          colorsCol;
    vector<Rect>             eyes;
    Ptr<Facemark>            facemark;
    int LEFT_EYE_POINTS[6] = {36, 37, 38, 39, 40, 41};
    int RIGHT_EYE_POINTS[6] = {42, 43, 44, 45, 46, 47};
    int MOUTH_INNER[2] = {62, 66};
    int MOUTH_EDGE_POINTS[6] = {48, 50, 52, 54, 56, 58};
    int frame_counter = 0;
    int yaw_counter = 0;
    int blink_counter = 0;
};

#endif // FACEDETECTOR_H
