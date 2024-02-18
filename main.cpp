#include "mainwindow.h"

#include <QApplication>
//paten include dlib with opencv
// #include <dlib/opencv.h>
// #include <dlib/image_processing/frontal_face_detector.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
