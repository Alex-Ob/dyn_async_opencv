#ifndef INCLUDE_[NAME]_H
#define INCLUDE_[NAME]_H

/************************************************************
[Name] class header
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
class [Name]: public CV_plugin
{
public:
    [Name](const string& ymlFile);
   ~[Name]();
    int processAsync(Mat &Img);

protected:

    void loadParameters(const cv::FileStorage& fs);

private:

/// Any needed data
    double sigma_ = 1.6;


};

/**
 * Экспортируемая функция создания модуля
 */
extern "C" __attribute__((visibility("default"))) CV_plugin *create(const std::string &config_name);

#endif //#ifndef INCLUDE_[NAME]_H
