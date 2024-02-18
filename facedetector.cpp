#include "facedetector.h"
#include <QDebug>


Point FaceDetector::middlePoint(Point p1, Point p2) {
    return Point(float(p1.x + p2.x) / 2, float(p1.y + p2.y) / 2);
}

float FaceDetector::blinkingRatio (vector<Point2f> landmarks, int points[])
{
    Point left = Point(landmarks[points[0]].x, landmarks[points[0]].y);
    Point right = Point(landmarks[points[3]].x, landmarks[points[3]].y);
    Point top = middlePoint(landmarks[points[1]], landmarks[points[2]]);
    Point bottom = middlePoint(landmarks[points[5]], landmarks[points[4]]);

    float eye_width = hypot((left.x - right.x), (left.y - right.y));
    float eye_height = hypot((top.x - bottom.x), (top.y - bottom.y));
    float ratio = eye_width / eye_height;

    try {
        float ratio = eye_width / eye_height;
    } catch (exception& e) {
        ratio = 0.0;
    }

    return ratio;
}

float FaceDetector::yawningRatio(vector<Point2f> landmarks, int points[]) {
    Point left = Point(landmarks[points[0]].x, landmarks[points[0]].y);
    Point right = Point(landmarks[points[3]].x, landmarks[points[3]].y);
    Point top = middlePoint(landmarks[points[1]], landmarks[points[2]]);
    Point bottom = middlePoint(landmarks[points[5]], landmarks[points[4]]);

    float eye_width = hypot((left.x - right.x), (left.y - right.y));
    float eye_height = hypot((top.x - bottom.x), (top.y - bottom.y));
    float ratio = eye_width / eye_height;

    try {
        float ratio = eye_width / eye_height;
    } catch (exception& e) {
        ratio = 0.0;
    }

    return ratio;
}

void FaceDetector::isolate( Mat frame, vector<Point2f> landmarks, int points[])
{
    Point region[1][20];

    for (int i = 0; i < 6; i++) {
        region[0][i] = Point(landmarks[points[i]].x, landmarks[points[i]].y);
    }

    Size size = frame.size();
    int height = size.height;
    int width = size.width;

    cv::Mat black_frame = cv::Mat(height, width, CV_8UC1, Scalar::all(0));
    cv::Mat mask = cv::Mat(height, width, CV_8UC1, Scalar::all(255));

    int npt[] = { 6 };
    const Point* ppt[1] = { region[0] };
    cv::fillPoly(mask, ppt, npt, 1, cv::Scalar(0, 0, 0), 0);
    cv::bitwise_not(mask, mask);

    Mat frame_mouth;
    frame.copyTo(frame_mouth, mask);

    int margin = 5;
    int x_vals[] = {region[0][0].x, region[0][1].x, region[0][2].x, region[0][3].x, region[0][4].x, region[0][5].x};
    int y_vals[] = {region[0][0].y, region[0][1].y, region[0][2].y, region[0][3].y, region[0][4].y, region[0][5].y};
    int min_x = *std::min_element(x_vals, x_vals+6) - margin;
    int max_x = *std::max_element(x_vals, x_vals+6) + margin;
    int min_y = *std::min_element(y_vals, y_vals+6) - margin;
    int max_y = *std::max_element(y_vals, y_vals+6) + margin;

    Mat frame_mouth_resized = frame_mouth(Range(min_y, max_y), Range(min_x, max_x));
    Point origin = Point(min_x, min_y);

    Size new_size = frame_mouth_resized.size();
    int new_height = new_size.height;
    int new_width = new_size.width;
    int center[] = {new_width / 2, new_height / 2};

    imshow("Isolate Mouth", frame_mouth_resized);

    //return frame_mouth_resized;
}

void FaceDetector::isolate_eye( Mat frame, vector<Point2f> landmarks, int points[])
{
    Point region[1][20];

    for (int i = 0; i < 6; i++) {
        region[0][i] = Point(landmarks[points[i]].x, landmarks[points[i]].y);
    }

    Size size = frame.size();
    int height = size.height;
    int width = size.width;

    cv::Mat black_frame = cv::Mat(height, width, CV_8UC1, Scalar::all(0));
    cv::Mat mask = cv::Mat(height, width, CV_8UC1, Scalar::all(255));

    int npt[] = { 6 };
    const Point* ppt[1] = { region[0] };
    cv::fillPoly(mask, ppt, npt, 1, cv::Scalar(0, 0, 0), 0);
    cv::bitwise_not(mask, mask);

    Mat frame_mouth;
    frame.copyTo(frame_mouth, mask);

    int margin = 5;
    int x_vals[] = {region[0][0].x, region[0][1].x, region[0][2].x, region[0][3].x, region[0][4].x, region[0][5].x};
    int y_vals[] = {region[0][0].y, region[0][1].y, region[0][2].y, region[0][3].y, region[0][4].y, region[0][5].y};
    int min_x = *std::min_element(x_vals, x_vals+6) - margin;
    int max_x = *std::max_element(x_vals, x_vals+6) + margin;
    int min_y = *std::min_element(y_vals, y_vals+6) - margin;
    int max_y = *std::max_element(y_vals, y_vals+6) + margin;

    Mat frame_eye_resized = frame_mouth(Range(min_y, max_y), Range(min_x, max_x));
    Point origin = Point(min_x, min_y);

    Size new_size = frame_eye_resized.size();
    int new_height = new_size.height;
    int new_width = new_size.width;
    int center[] = {new_width / 2, new_height / 2};

    imshow("Isolate Eye", frame_eye_resized);

    //return frame_mouth_resized;
}

FaceDetector::FaceDetector()
{
    cascade_eye_name = "D:/cameracctv/camera/haarcascade_eye.xml";
    cascade_face_name = "D:/cameracctv/camera/haarcascade_frontalface_alt.xml";

    face_cascade.load(cascade_face_name);
    eye_cascade.load(cascade_eye_name);

    if (!face_cascade.load(cascade_face_name) || !eye_cascade.load(cascade_eye_name)) {
        qDebug() << "--(!)Error loading cascade classifier\n";
    }

    facemark = FacemarkLBF::create();
    facemark->loadModel("D:/cameracctv/camera/lbfmodel.yaml");

    /* 8 colors collection */
    colorsCol   << cvScalar(0.0,0.0,255.0)   << cvScalar(0.0,128.0,255.0)
              << cvScalar(0.0,255.0,255.0) << cvScalar(0.0,255.0,0.0)
              << cvScalar(255.0,128.0,0.0) << cvScalar(255.0,255.0,0.0)
              << cvScalar(255.0,0.0,0.0)   << cvScalar(255.0,0.0,255.0);
}


QImage FaceDetector::detect(Mat frame)
{
    if (frame.empty()) {
        qDebug() << "Input frame is empty!";
        return QImage(); // Returning an empty QImage
    }

    Mat frame_gray;
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    std::vector<Rect> faces;
    face_cascade.detectMultiScale(frame_gray, faces, 1.01,3,CASCADE_FIND_BIGGEST_OBJECT|CASCADE_SCALE_IMAGE,Size(200,200));

    if (!faces.empty()) {
        rectangle(frame, faces[0], colorsCol[0], 2);
        vector<vector<Point2f>> shapes;
        if (facemark->fit(frame, faces, shapes)) {
            vector<Point2f> faceLandmarks = shapes[0];
            for (int k = 36; k <= 67; k++) {
                circle(frame, faceLandmarks[k], 2, colorsCol[0], FILLED);
            }

            if (shapes.size() > 0) {
                //eye detection
                isolate_eye(frame, shapes[0], LEFT_EYE_POINTS);
                float blinking_ratio_left = blinkingRatio( shapes[0], LEFT_EYE_POINTS );
                float blinking_ratio_right = blinkingRatio( shapes[0], RIGHT_EYE_POINTS );

                float avg_blinking_ratio = (blinking_ratio_left + blinking_ratio_right) /2;
                qDebug() << "BLinking ratio: " << avg_blinking_ratio;

                if (avg_blinking_ratio > 4.6)
                {
                    qDebug()<<"Sleep";
                    putText(frame, "Sleep!", Point(10, frame.rows - 40), FONT_HERSHEY_DUPLEX, 0.8, colorsCol[0], 1, LINE_AA);
                }else{
                    qDebug()<<"normal";
                    putText(frame, "normal", Point(10, frame.rows - 40), FONT_HERSHEY_DUPLEX, 0.8, colorsCol[0], 1, LINE_AA);
                }

                //yawning detection
                isolate(frame, shapes[0], MOUTH_EDGE_POINTS);
                float yawning_ratio = yawningRatio(shapes[0], MOUTH_EDGE_POINTS);
                qDebug() << "Yawning ratio: " << yawning_ratio;
                if (yawning_ratio < 1.65) {
                    qDebug() << "YAWNING!";
                    putText(frame, "YAWNING!", Point(10, frame.rows - 10), FONT_HERSHEY_DUPLEX, 0.8, colorsCol[0], 1, LINE_AA);
                } else {
                    qDebug() << "Not yawning";
                    putText(frame, "Not yawning", Point(10, frame.rows - 10), FONT_HERSHEY_DUPLEX, 0.8, colorsCol[0], 1, LINE_AA);
                }
            }
        }

        // StateOutput blink = isBlinking( frame );
        // StateOutput yaw = isYawning( frame );
        // bool is_blinking = blink.state;
        // bool is_yawning = yaw.state;

        // if( blink.frame.empty() || yaw.frame.empty() )
        // {
        //     qDebug() << "--(!) No captured eye or mouth frame -- Break!\n";
        // }

        // Mat eye_frame;
        // Mat mouth_frame;

        // resize(blink.frame, eye_frame, Size(100, 100), 0, 0, INTER_CUBIC);
        // resize(yaw.frame, mouth_frame, Size(100, 100), 0, 0, INTER_CUBIC);

        // Mat canvas(frame.rows+130, frame.cols+20, CV_8UC3, Scalar(0, 0, 0));
        // Rect r(10, 10, frame.cols, frame.rows);
        // frame.copyTo(canvas(r));

        // Rect show_eye(10, frame.rows + 20, 100, 100);
        // Rect show_mouth(120, frame.rows + 20, 100, 100);

        // eye_frame.copyTo(canvas(show_eye));
        // mouth_frame.copyTo(canvas(show_mouth));

        // frame_counter++;
        // if (is_blinking)
        // {
        //     blink_counter++;
        // };

        // if (is_yawning)
        // {
        //     yaw_counter++;
        // }

        // float drowsiness_perc;
        // float yaw_perc;
        // if (frame_counter == 20)
        // {
        //     drowsiness_perc = (float)blink_counter / frame_counter;
        //     yaw_perc = (float)yaw_counter / frame_counter;
        //     frame_counter = 0;
        //     blink_counter = 0;
        //     yaw_counter = 0;
        //     // cout << "Drowsiness percentage: " << (drowsiness_perc) << endl;
        //     // cout << "Yawing percentage: " << (yaw_perc) << endl;
        // }

        // if (!drowsiness_perc)
        // {
        //     drowsiness_perc = 0.0;
        //     yaw_perc = 0.0;
        // }

        // putText(canvas, "Drowsiness percentage: " + to_string(drowsiness_perc), Point2f(20, 40), FONT_HERSHEY_DUPLEX, 0.9, Scalar(0, 200, 200), 1);
        // putText(canvas, "Yawing percentage: " + to_string(yaw_perc), Point2f(20, 75), FONT_HERSHEY_DUPLEX, 0.9, Scalar(0, 200, 200), 1);

        // if (drowsiness_perc > 0.8)
        // {
        //     // cout << "ALERT! The driver is sleepy!" << endl;
        //     putText(canvas, "ALERT! The driver is sleepy!", Point2f(canvas.cols - 400, canvas.rows - 50), FONT_HERSHEY_DUPLEX, 0.9, Scalar(30, 30, 147), 1);
        // }
        // else
        // {
        //     putText(canvas, "The driver state is OK", Point2f(canvas.cols - 400, canvas.rows - 50), FONT_HERSHEY_DUPLEX, 0.9, Scalar(30, 147, 31), 1);
        // }
    }else {

    }

    // Convert Mat to QImage
    QImage result = QImage((const uchar *)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888).rgbSwapped();
    return result;
}
