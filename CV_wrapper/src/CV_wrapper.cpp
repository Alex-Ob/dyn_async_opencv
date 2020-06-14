#include <iostream>

#include "CV_wrapper.h"
#include "cv_plugin.h"
#include <unistd.h>

CV_wrapper::CV_wrapper(const string& pluginName)
{
    try
    {
        assert( ! pluginName.empty() );

        string pluginFile = "lib" + pluginName + ".so";
        //bool fex = fileExists(pluginFile);
        handle_ = dlopen(pluginFile.c_str(), RTLD_LAZY);
        if(handle_ == NULL)
        {
            std::cout << dlerror() << std::endl;
            throw("Can't load library!");
        }

        create_fcn_ = (CV_plugin * (*)(const string& paramFile))dlsym(handle_, "create");

        string paramsFile = CONFIG_PATH + pluginName + ".yml";
        cv_plugin_ = create_fcn_(paramsFile);
        if(cv_plugin_ == NULL)
        {
            throw("Can't create plugin!");
        }
    }
    catch(const string &ex)
    {
        delete cv_plugin_;

        if(handle_ != NULL)
            dlclose(handle_);
    }
}

CV_wrapper::~CV_wrapper()
{
    delete cv_plugin_;

    if(handle_ != NULL)
        dlclose(handle_);
}

void CV_wrapper::setParameters(const string& ymlFile)
{
    if(cv_plugin_ != NULL)
    {
        cv_plugin_->init(ymlFile);
    }
}

int CV_wrapper::processAsync(Mat& img)
{
    if(cv_plugin_ != NULL)
    {
        cv_plugin_->processAsync(img);
    }

    return 0;
}


bool CV_wrapper::waitForResult(Mat& img)
{
    return cv_plugin_->waitForResult(img);
}
