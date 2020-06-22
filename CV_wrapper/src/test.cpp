#include "CV_wrapper.h"

using std::cout;
using std::endl;

int main()
{
    string pluginName = "blur";
    cout << "Create plugin " << pluginName << endl;
    CV_wrapper blur("blur");
    CV_wrapper erode("erode");
    CV_wrapper dilate("dilate");

    string imagePath = "";
    string imageName = "BigCat.jpeg";
    string fullImageName = imagePath + imageName;

    cout << "Load image " << fullImageName << endl;
    Mat img = cv::imread(fullImageName);
    if(! img.empty() )
    {
        string proceedImageName;
        cout << "Proceed images..." << endl;
        int blur_1 = blur.processAsync(img);
        int blur_2 = blur.processAsync(img);
        int blur_3 = blur.processAsync(img);
        int blur_4 = blur.processAsync(img);
        int blur_5 = blur.processAsync(img);
        cout << "Getting images..." << endl;
        blur.waitForResult(blur_1, img);
        blur.waitForResult(blur_2, img);
        blur.waitForResult(blur_3, img);
        blur.waitForResult(blur_4, img);
        blur.waitForResult(blur_5, img);

        proceedImageName = imagePath + "blurred_" + imageName;
        cout << "Save image " << proceedImageName << endl;
        cv::imwrite(proceedImageName, img);

        int erode_1 = erode.processAsync(img);
        erode.waitForResult(erode_1, img);

        proceedImageName = imagePath + "eroded_" + imageName;
        cout << "Save image " << proceedImageName << endl;
        cv::imwrite(proceedImageName, img);

        int dilate_1 = dilate.processAsync(img);
        dilate.waitForResult(dilate_1, img);

        proceedImageName = imagePath + "dilated_" + imageName;
        cout << "Save image " << proceedImageName << endl;
        cv::imwrite(proceedImageName, img);
    }
    return 0;
}

