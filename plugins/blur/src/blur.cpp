#include "blur.h"


Blur::Blur(const string& ymlFile) : CV_plugin(ymlFile)
{
   init(ymlFile);
}

Blur::~Blur()
{

}

bool Blur::init(const string& config_name)
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


void Blur::loadParameters(const cv::FileStorage& fs)
{
    sigma_ = static_cast<double>(fs["sigma"]);
}

bool Blur::processAsync(Mat &Img)
{

    inProcess_ = true;
    inImg_ = Img.clone();
    thread_ = std::thread([this]() { cv::GaussianBlur(inImg_, outImg_, cv::Size(0,0), sigma_); inProcess_ = false; });

    return true;
}

bool Blur::waitForResult(Mat& img)
{
    if(thread_.joinable())
    {
        thread_.join();
    }
    img = outImg_.clone();

    return true;
}

CV_plugin *create(const std::string &config_name)
{
 return new Blur(config_name);
}
