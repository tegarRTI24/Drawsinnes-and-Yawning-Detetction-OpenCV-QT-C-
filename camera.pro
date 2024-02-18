QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += C:/opencv/build/install/include
DEPENDPATH += C:/opencv/build/install/include

win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_highgui490.dll
win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_calib3d490.dll
win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_core490.dll
win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_dnn490.dll
win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_features2d490.dll
win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_flann490.dll
win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_gapi490.dll
win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_dnn490.dll
win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_imgcodecs490.dll
win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_imgproc490.dll
win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_ml490.dll
win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_objdetect490.dll
win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_stitching490.dll
win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_video490.dll
win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_videoio490.dll
win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_photo490.dll
win32: LIBS += C:/opencv/build/install/x64/mingw/bin/libopencv_face490.dll

INCLUDEPATH += C:/dlib-19.8/include
win32: LIBS += -L"C:/dlib-19.8/build"
win32: LIBS += -ldlib

SOURCES += \
    facedetector.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    facedetector.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc \
    resourceicon.qrc

RC_ICONS = sleepy.ico

