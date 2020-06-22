#ifndef CV_PLUGIN_H
#define CV_PLUGIN_H

#include <string>
#include <iostream>
#include <thread>
#include <map>
#include <sys/stat.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using std::string;
using cv::Mat;

typedef struct
{
    std::thread thread_;
    Mat img_;

} Thread_Data;

bool fileExists(const string& filename);

const string CONFIG_PATH = "../res/";

class CV_plugin
{
public:

    CV_plugin(const string &config_name);

    virtual ~CV_plugin();

    bool init(const string& config_name);
    
    // @return: thread_id which must be used for thread control;
    virtual int processAsync(Mat&);
    
    bool waitForResult(int, Mat&);

protected:
    
    virtual void loadParameters(const cv::FileStorage&);

    int thread_counter_ = 0;
    std::map<int, Thread_Data> thread_map_;

    std::string name_;

    volatile bool inProcess_ = false;

    cv::Mat inImg_, outImg_;
};

/* Определяется только в производных классах
extern "C"
{
    __attribute__((visibility("default"))) CV_plugin* create(const string& params);
}
*/

#endif //#ifndef CV_PLUGIN_H
