
#include "[name].h"


CV_plugin *create(const std::string &config_name)
{
    return new [Name](config_name);
}


[Name]::[Name](const string& ymlFile) : CV_plugin(ymlFile)
{
    init(ymlFile);
}

[Name]::~[Name]()
{

}


void [Name]::loadParameters(const cv::FileStorage& fs)
{
    // Any plugin's data
    sigma_ = static_cast<double>(fs["sigma"]);
}

int [Name]::processAsync(Mat &Img)
{
    inProcess_ = true;
    // исходная картинка может в дальнейшем модифицироваться
    inImg_ = Img.clone();

    // Поиск уникального id
    do { ++thread_counter_; }
    while(thread_map_.find(thread_counter_) != thread_map_.end());

    thread_map_[thread_counter_].img_ = Mat();
/// This function must be overwritten!
    thread_map_[thread_counter_].thread_ = std::thread([this]() { cv::GaussianBlur(inImg_, thread_map_[thread_counter_].img_, cv::Size(0,0), sigma_); inProcess_ = false; });

    return thread_counter_;
}

