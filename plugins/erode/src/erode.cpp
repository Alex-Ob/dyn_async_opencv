
#include "erode.h"


CV_plugin *create(const std::string &config_name)
{
 return new Erode(config_name);
}


Erode::Erode(const string& ymlFile) : CV_plugin(ymlFile)
{
   init(ymlFile);
}

Erode::~Erode()
{

}

bool Erode::init(const string& config_name)
{
    bool res = false;

    try
    {
        if(fileExists(config_name))
        {
            cv::String fstr(config_name.c_str());
            cv::FileStorage fs(fstr, cv::FileStorage::READ | cv::FileStorage::FORMAT_YAML);

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


void Erode::loadParameters(const cv::FileStorage& fs)
{
    fs["kernel"] >> kernel_;
    fs["border"] >> border_;
}

bool Erode::processAsync(Mat &Img)
{

    inProcess_ = true;
    inImg_ = Img.clone();
/// This function must be overwritten!
    thread_ = std::thread([this]() { cv::erode(inImg_, outImg_, kernel_); inProcess_ = false; });

    return true;
}

bool Erode::waitForResult(Mat& img)
{
    if(thread_.joinable())
    {
        thread_.join();
    }
    img = outImg_.clone();

    return true;
}

