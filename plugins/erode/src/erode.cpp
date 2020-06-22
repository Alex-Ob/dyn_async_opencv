
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


void Erode::loadParameters(const cv::FileStorage& fs)
{
    fs["kernel"] >> kernel_;
    fs["border"] >> border_;
}

int Erode::processAsync(Mat &Img)
{

    inProcess_ = true;
    inImg_ = Img.clone();

    // Поиск уникального id
    do { ++thread_counter_; }
    while(thread_map_.find(thread_counter_) != thread_map_.end());

    thread_map_[thread_counter_].img_ = Mat();
/// This function must be overwritten!
    thread_map_[thread_counter_].thread_ = std::thread([this]() { cv::erode(inImg_, thread_map_[thread_counter_].img_, kernel_); inProcess_ = false; });

    return thread_counter_;
}

