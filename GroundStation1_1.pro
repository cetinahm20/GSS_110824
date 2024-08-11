QT       += core gui multimedia multimediawidgets
QT += widgets network
QT += multimedia
QT += quick quick3d
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport quickwidgets

CONFIG += c++17

# Specify the path to the OpenCV installation
OPENCV_DIR = C:/Users/aali_/opencv/build

# Include OpenCV headers
INCLUDEPATH += $$OPENCV_DIR/include

# Link OpenCV libraries
LIBS += -L$$OPENCV_DIR/x64/vc16/lib \
        -lopencv_world4100 \
        -lopencv_world4100d \



# Specify the path to the GStreamer installation
GST_DIR = C:/gstreamer/1.0/msvc_x86_64

# Include GStreamer headers
INCLUDEPATH += $$GST_DIR/include/gstreamer-1.0 \
               $$GST_DIR/include/glib-2.0 \
               $$GST_DIR/lib/glib-2.0/include

# Link GStreamer libraries
LIBS += -L$$GST_DIR/lib -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0

# Additional libraries if required
LIBS += -lgstbase-1.0 -lgstapp-1.0 -lgstvideo-1.0 -lgstaudio-1.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc \
    Resources.qrc

DISTFILES +=


