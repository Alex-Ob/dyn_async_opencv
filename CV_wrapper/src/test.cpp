// links:
// https://amir.rachum.com/blog/2016/09/17/shared-libraries/
// https://www.opennet.ru/base/dev/shared_lib_intro.txt.html
// https://rtfm.co.ua/c-sozdanie-i-primenenie-shared-library-v-linux/
// https://tetraquark.ru/archives/47
// https://stackoverflow.com/questions/9534666/shared-libraries-dlopen-and-thread-safety-of-library-static-pointers
// http://www.yolinux.com/TUTORIALS/LibraryArchives-StaticAndDynamic.html
// https://www.cyberciti.biz/tips/linux-shared-library-management.html?__cf_chl_captcha_tk__=91fc82285cade7124330f72831390b26f00bbe6d-1591571227-0-ARO2gBNx21D9stcFNwWcqPCMPSFRtwr14KLCk0afAd_E1MAJuhJ1bLuK56DGFLLWk0dB0lUC0LQqcZNUkpJJCTmDSPVkzNvcoNtDiNr5YpDoM7FS54vM8Wl6-jflkxcJH3EQH8hCNbRdLc4QrusZmWr4jbe_hAEI2rz5-ofLeSTKTH2Ozb6BRvYwZet9IH2RQfAORPjn1CcKnRN1q4SrbnNNPKVgcVeg0gOQrJa1Dp91khUzX5efuvtBYZD6zW4Itsuir6yAt4B2n9CiDiQK-nlHWebw8eHTdd8qrjI7mmyBZ6CseY444Id8KMNAIjGDQkdyKvMp9lnySTS4V8Y5Ze0XXTG_kI-OHiVPEj1Ivh41Czdw8QMrYAN6DFWh2JfTTMV9S-5I10p2a-EyJNQsgnL1q7KdHF4hITIhM9igqK2Rl6JPqPNDn-gws020R2GRtfm8Atpo-Lir9JV7bXSx-6aQuzN3bSvz-Rx2m8O9PAi6WiZVYJ7DNuxVXl-hTY6oLfPUOTSJW01EG1CEZ_IdcBY017L2n0eTBoz8cuI5xrv2
// https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html
// https://developer.ibm.com/technologies/linux/tutorials/l-dynamic-libraries/
// http://tldp.org/HOWTO/Program-Library-HOWTO/more-examples.html
// https://stackoverflow.com/questions/9833731/pthread-library-initialization
// https://blablacode.ru/programmirovanie/183
// https://habr.com/ru/post/122757/
// https://www.opennet.ru/docs/RUS/zlp/003.html
// https://webhamster.ru/mytetrashare/index/mtb0/938
// https://gitlab.kitware.com/cmake/community/-/wikis/FAQ
// http://alexkutsan.blogspot.com/2013/11/linux.html

#include "CV_wrapper.h"

using std::cout;
using std::endl;

int main()
{
    string pluginName = "blur";
    cout << "Create plugin " << pluginName << endl;
    CV_wrapper blur("blur");
    CV_wrapper dilate("dilate");
    CV_wrapper erode("erode");

//    CV_wrapper erode("erode");
//    CV_wrapper dilate("dilate");

    string imagePath = "";
    string imageName = "BigCat.jpeg";
    string fullImageName = imagePath + imageName;

    cout << "Load image " << fullImageName << endl;
    Mat img = cv::imread(fullImageName);
    if(! img.empty() )
    {
        string proceedImageName;

        blur.processAsync(img);
        blur.waitForResult(img);

        proceedImageName = imagePath + "blurred_" + imageName;
        cout << "Save image " << proceedImageName << endl;
        cv::imwrite(proceedImageName, img);

        erode.processAsync(img);
        erode.waitForResult(img);

        proceedImageName = imagePath + "eroded_" + imageName;
        cout << "Save image " << proceedImageName << endl;
        cv::imwrite(proceedImageName, img);

        dilate.processAsync(img);
        dilate.waitForResult(img);

        proceedImageName = imagePath + "dilated_" + imageName;
        cout << "Save image " << proceedImageName << endl;
        cv::imwrite(proceedImageName, img);
    }
    return 0;
}

