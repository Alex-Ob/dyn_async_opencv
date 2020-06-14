#ifndef CV_WRAPPER_H
#define CV_WRAPPER_H

#include <string>
#include <map>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include <dlfcn.h>
#include <sys/stat.h>

#include "cv_plugin.h"

using std::string;
using cv::Mat;

class CV_plugin;

class CV_wrapper
{
public:

    CV_wrapper(const string& pluginName);
   ~CV_wrapper();

    void setParameters(const string& ymlFile);

    int  processAsync(Mat& img);

    bool waitForResult(Mat& img);
    
protected:

    CV_plugin *cv_plugin_ = nullptr;
    
private:
    
    CV_wrapper() = delete; //Для верности

    bool isInited_ = false;
    void *handle_   = nullptr;

    CV_plugin * (*create_fcn_)(const string& paramFile) = nullptr;
};


#endif //#ifndef CV_WRAPPER_H
