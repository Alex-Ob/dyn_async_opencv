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
    //init(config_name); //Вызывается в производных классах
}

CV_plugin::~CV_plugin()
{
    for(std::map<int, Thread_Data>::iterator it = thread_map_.begin(); it != thread_map_.end(); ++it)
    {
        if(it->second.thread_.joinable())
            it->second.thread_.join();
    }
}

bool CV_plugin::init(const string& config_name)
{
    bool res = false;

    try
    {
        if(fileExists(config_name))
        {
            cv::String fstr(config_name.c_str());
            cv::FileStorage fs(fstr, cv::FileStorage::READ | cv::FileStorage::FORMAT_YAML);

            // Вызов виртуальной функции производного класса
            this->loadParameters(fs);

            res = true;
        }
    }
    catch(const cv::Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return res;

}

int CV_plugin::processAsync(Mat &Img)
{
    string Err = "Function " + string(__FUNCTION__) + " must be override!";
    throw(Err);

    return -1;
}


bool CV_plugin::waitForResult(int thread_id, Mat& img)
{
    bool res = false;

    if(thread_map_.find(thread_id) != thread_map_.end())
    {
        if(thread_map_[thread_id].thread_.joinable())
        {
            thread_map_[thread_id].thread_.join();
        }
        //img = thread_map_[thread_id].img_.clone();
        thread_map_[thread_id].img_.copyTo(img);
        thread_map_.erase(thread_id);

        res = true;
    }
    return res;
}

void CV_plugin::loadParameters(const cv::FileStorage& fs)
{
    string Err = "Function " + string(__FUNCTION__) + " must be override!";
    throw(Err);
}
