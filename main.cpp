#include <iostream> //stl
#include "OpenJpeg2KTool.h"

using namespace cv;
using namespace std;
using namespace kekxv;

int main(int argc, char *argv[]) {
    cv::Mat result;
    if (argc == 2) {
        for (int i = 0; i <= 4; i++)
            if (OpenJpeg2KTool::Read(argv[1], &result, i) >= 0) {
                cout << "格式为:" << ((CODEC_FORMAT) i) << endl;
                imshow("t",result);
                waitKey(0);
            }
    }
    return 0;
}