#ifndef BLUR_H
#define BLUR_H


#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "cv_plugin.h"

using cv::Mat;
using std::string;


class Blur : public CV_plugin
{
public:
    Blur(const string& ymlFile);
   ~Blur();
    int processAsync(Mat &Img);

protected:

    void loadParameters(const cv::FileStorage& fs);

private:

    double sigma_ = 1.6;
};

extern "C" __attribute__((visibility("default"))) CV_plugin *create(const std::string &config_name);

#endif //#ifndef BLUR_H
