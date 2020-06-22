#include "blur.h"

CV_plugin *create(const std::string &config_name)
{
    return new Blur(config_name);
}


Blur::Blur(const string& ymlFile) : CV_plugin(ymlFile)
{
    init(ymlFile);
}

Blur::~Blur()
{

}

void Blur::loadParameters(const cv::FileStorage& fs)
{
    sigma_ = static_cast<double>(fs["sigma"]);
}

int Blur::processAsync(Mat &Img)
{
    inProcess_ = true;
    // исходная картинка может в дальнейшем модифицироваться
    inImg_ = Img.clone();

    // Поиск уникального id
    do { ++thread_counter_; }
    while(thread_map_.find(thread_counter_) != thread_map_.end());

    thread_map_[thread_counter_].img_ = Mat();
    thread_map_[thread_counter_].thread_ = std::thread([this]() { cv::GaussianBlur(inImg_, thread_map_[thread_counter_].img_, cv::Size(0,0), sigma_); inProcess_ = false; });

    return thread_counter_;
}
