#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//qt includes
#include <QMainWindow>
#include <QGraphicsView>
#include <QTimer>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
//local include
#include "facedetector.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void capturing();
    void on_minimize_clicked();
    void on_exit_clicked();
    void on_maximize_toggled(bool checked);
    void on_start_clicked();
    void on_stop_clicked();

private:
    Ui::MainWindow *ui;
    VideoCapture    capture;
    Mat             frame;
    FaceDetector    detector;
    QPixmap        *pixmap;
    QTimer         *intervalTimer;
    QGraphicsScene *scene;
    QSizeGrip *sizeGrip;
    bool isDragging;
    QPoint lastMousePosition;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    int indexcam;
    QStringList cameraList;
    QList<QCameraInfo> cameras;

};
#endif // MAINWINDOW_H
