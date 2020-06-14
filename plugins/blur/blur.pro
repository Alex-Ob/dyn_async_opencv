TEMPLATE = lib

CONFIG += c++11
CONFIG += plugin        #need for .so modules in oder to prevent multi-version links
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_WARN_ON  += -Wno-unknown-pragmas
QMAKE_CXXFLAGS_WARN_OFF += -Wunused-parameter
QMAKE_CXXFLAGS_WARN_OFF += -Wno-undefined

OPENCV_INCLUDE_DIR = /usr/local/include

# Build properties

#Отключить "теневую сборку" в криейторе!
DESTDIR = $$PWD/../../bin
OBJECTS_DIR = $$PWD/build

# Common

INCLUDEPATH += $$PWD/../../CV_wrapper/include
HEADERS += $$PWD/../../CV_wrapper/include/cv_plugin.h

SOURCES += $$PWD/../../CV_wrapper/src/cv_plugin.cpp

# Project files
INCLUDEPATH += $$PWD/include
HEADERS += include/blur.h

SOURCES += src/blur.cpp

# Boost and common
LIBS += \
        -lpthread \
        -ldl -fPIC

# OpenCV
INCLUDEPATH += $$OPENCV_INCLUDE_DIR
LIBS += -L/usr/local/lib \
        -lopencv_core \
        -lopencv_imgproc \
        -lopencv_highgui
