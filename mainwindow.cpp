#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    detector = FaceDetector();
    intervalTimer = new QTimer(this);
    pixmap = new QPixmap();
    scene = new QGraphicsScene();

    setWindowFlags(Qt::FramelessWindowHint);
    sizeGrip = new QSizeGrip(ui->size_grip);
    sizeGrip->setGeometry(ui->size_grip->width() - sizeGrip->width(), ui->size_grip->height() - sizeGrip->height(), sizeGrip->width(), sizeGrip->height());
    isDragging = false;
    installEventFilter(this);

    cameras = QCameraInfo::availableCameras();
    // Menambahkan informasi kamera ke dalam QStringList
    for (const QCameraInfo &cameraInfo : cameras) {
        cameraList << cameraInfo.description();
    }
    ui->listcamera->addItems(cameraList);
    ui->label_15->setText("CAM 1");
}

MainWindow::~MainWindow()
{
    delete pixmap;
    delete scene;
    delete intervalTimer;
    delete ui;
}

void MainWindow::capturing()
{
    capture.read(frame);
    QImage result = detector.detect(frame);
    ui->label_15->setScaledContents(true);
    result = result.scaled(ui->label_15->size(), Qt::KeepAspectRatio);
    ui->label_15->setPixmap(QPixmap::fromImage(result));
    // result = result.scaled(ui->graphicsView->size(), Qt::KeepAspectRatio);
    // pixmap = new QPixmap(QPixmap::fromImage(result));
    // scene = new QGraphicsScene(ui->graphicsView);
    // scene->addPixmap(*pixmap);
    // scene->setSceneRect(pixmap->rect());
    // ui->graphicsView->setScene(scene);
    // ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    // ui->graphicsView->setContentsMargins(0, 0, 0, 0);
}

void MainWindow::on_minimize_clicked()
{
    this->showMinimized();
}

void MainWindow::on_exit_clicked()
{
    this->close();
}

void MainWindow::on_maximize_toggled(bool checked)
{
    if(checked){
        this->showFullScreen();
        QIcon icon(":/icon/rectangle.png");
        ui->maximize->setIcon(icon);
    }else{
        this->showNormal();
        QIcon icon(":/icon/maximize.svg");
        ui->maximize->setIcon(icon);
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this) {
        if (event->type() == QEvent::MouseButtonPress) {
            // Store the initial mouse position when the left mouse button is pressed
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->buttons() & Qt::LeftButton) {
                isDragging = true;
                lastMousePosition = mouseEvent->globalPos() - frameGeometry().topLeft();
                return true;
            }
        } else if (event->type() == QEvent::MouseMove && isDragging) {
            // Move the window when dragging
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            move(mouseEvent->globalPos() - lastMousePosition);
            return true;
        } else if (event->type() == QEvent::MouseButtonRelease) {
            isDragging = false;
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier) {
        if (event->key() == Qt::Key_W) {
            // Close the application when Ctrl+W is pressed
            this->close();
        } else if (event->key() == Qt::Key_M) {
            // Minimize the application when Ctrl+M is pressed
            this->showMinimized();
        } else if (event->key() == Qt::Key_S) {
            ui->label_15->clear();
            indexcam = ui->listcamera->currentIndex();
            capture.open(indexcam);
            connect(intervalTimer, SIGNAL(timeout()), this, SLOT(capturing()));
            intervalTimer->start(33);
        } else if (event->key() == Qt::Key_A) {
            ui->label_15->clear();
            ui->label_15->setText("<strong>CAM 1<strong>");
            intervalTimer->stop();
            disconnect(intervalTimer, SIGNAL(timeout()), this, SLOT(capturing()));
            capture.release();
        } else if (event->key() == Qt::Key_F) {
            // Toggle fullscreen when Ctrl+F is pressed
            if (this->isFullScreen()) {
                this->showNormal();
                QIcon icon(":/icon/maximize.svg");
                ui->maximize->setIcon(icon);
            } else {
                this->showFullScreen();
                QIcon icon(":/icon/rectangle.png");
                ui->maximize->setIcon(icon);
            }
        }
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::on_start_clicked()
{
    ui->label_15->clear();
    indexcam = ui->listcamera->currentIndex();
    capture.open(indexcam);
    connect(intervalTimer, SIGNAL(timeout()), this, SLOT(capturing()));
    intervalTimer->start(33);
}

void MainWindow::on_stop_clicked()
{
    ui->label_15->clear();
    ui->label_15->setText("<strong>CAM 1<strong>");
    intervalTimer->stop();
    disconnect(intervalTimer, SIGNAL(timeout()), this, SLOT(capturing()));
    capture.release();
}



