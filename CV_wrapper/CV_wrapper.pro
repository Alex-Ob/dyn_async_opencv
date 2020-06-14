TEMPLATE = app

CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_WARN_ON  += -Wno-unknown-pragmas
QMAKE_CXXFLAGS_WARN_OFF += -Wunused-parameter
QMAKE_CXXFLAGS_WARN_OFF += -Wno-undefined

DESTDIR = $$PWD/../bin
OBJECTS_DIR = build
OPENCV_INCLUDE_DIR = /usr/local/include

# Project files
INCLUDEPATH += $$PWD/include
HEADERS += \
       include/CV_wrapper.h \
       include/cv_plugin.h

SOURCES += \
    src/CV_wrapper.cpp \
    src/cv_plugin.cpp \
    src/test.cpp
       
LIBS += \
    -L/usr/local/lib \
    -lopencv_highgui \
    -lopencv_core \
    -lopencv_imgproc \
    -lopencv_imgcodecs \
    -lpthread \
    -ldl
