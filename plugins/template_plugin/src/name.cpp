
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

bool [Name]::init(const string& config_name)
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


void [Name]::loadParameters(const cv::FileStorage& fs)
{
    sigma_ = static_cast<double>(fs["sigma"]);
}

bool [Name]::processAsync(Mat &Img)
{

    inProcess_ = true;
    inImg_ = Img.clone();
/// This function must be overwritten!
    thread_ = std::thread([this]() { cv::GaussianBlur(inImg_, outImg_, cv::Size(0,0), sigma_); inProcess_ = false; });

    return true;
}

bool [Name]::waitForResult(Mat& img)
{
    if(thread_.joinable())
    {
        thread_.join();
    }
    img = outImg_.clone();

    return true;
}

