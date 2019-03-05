//
// Created by caesar on 19-3-5.
//

#ifndef PROJECT_OPENJPEG2KTOOL_H
#define PROJECT_OPENJPEG2KTOOL_H

#include <opencv2/opencv.hpp>
#include <openjpeg-2.3/openjpeg.h>

using namespace cv;
namespace kekxv {
    class OpenJpeg2KTool {
    public:
        /**
         * 读取 JPEG2000 图像
         * @param FilePath
         * @param outMat
         * @param format
         * @return
         */
        static int Read(const char *FilePath, Mat *outMat, int format = OPJ_CODEC_J2K);

        /**
         * 自动读取 返回类型
         * @param FilePath 图像路径
         * @param outMat 输出为 opencv Mat类型
         * @return
         */
        static int AutoRead(const char *FilePath, Mat *outMat);

    private:
        static bool init(opj_dparameters *mparameters);

        static bool Jp2kToMat(opj_image_t *mopj_img, Mat *outMat);
    };
}

#endif //PROJECT_OPENJPEG2KTOOL_H
