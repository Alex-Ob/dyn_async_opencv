#include <opencv2/core.hpp>

#include "cv_plugin.h"

using cv::Mat;
using std::string;

bool fileExists(const string& filename)
{
    struct stat st;
    return( stat(filename.c_str(), &st) == 0) && !S_ISDIR(st.st_mode);
}

CV_plugin::CV_plugin(const string &config_name):
inProcess_(false)
{
    //init(config_name);
}

CV_plugin::~CV_plugin()
{
    if(thread_.joinable() && inProcess_)
    {
        thread_.join();
    }
}

bool CV_plugin::init(const string& config_name)
{
    string Err = "Function " + string(__FUNCTION__) + " must be override!";
    throw(Err);

    return false;
}
/*
bool CV_plugin::init(const string& config_name)
{
    bool res = false;

    try
    {
        if(fileExists(config_name))
        {
            cv::String fstr(config_name.c_str());
            cv::FileStorage fs(fstr, cv::FileStorage::READ | cv::FileStorage::FORMAT_YAML);
            //cv::FileNode plugins = fs["plugins"];

            loadParameters(fs);

            res = true;
        }
    }
    catch(const cv::Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return res;
}
*/

bool CV_plugin::processAsync(Mat &Img)
{
    string Err = "Function " + string(__FUNCTION__) + " must be override!";
    throw(Err);

   return false;
}


bool CV_plugin::waitForResult(Mat& Img)
{
    string Err = "Function " + string(__FUNCTION__) + " must be override!";
    throw(Err);
    return false;
}

void CV_plugin::loadParameters(const cv::FileStorage& fs)
{
    string Err = "Function " + string(__FUNCTION__) + " must be override!";
    throw(Err);
}
