#ifndef INCLUDE_ERODE_H
#define INCLUDE_ERODE_H

/************************************************************
Erode class header
************************************************************/

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "cv_plugin.h"

using cv::Mat;
using std::string;


/************************************************************/

/**
 * Описание модуля
 */
class Erode: public CV_plugin
{
public:
    Erode(const string& ymlFile);
   ~Erode();
    int processAsync(Mat &Img);

protected:

    void loadParameters(const cv::FileStorage& fs);

private:

/// Any needed data
    Mat kernel_;
    int border_ = cv::BORDER_CONSTANT;

};

/**
 * Экспортируемая функция создания модуля
 */
extern "C" __attribute__((visibility("default"))) CV_plugin *create(const std::string &config_name);

#endif //#ifndef INCLUDE_ERODE_H
