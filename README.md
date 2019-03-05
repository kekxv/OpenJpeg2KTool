# OpenJPEG x OpenCV

读取 JPEG2000 的方法

根据仓库 [Cpp-OpenJPEGxOpenCV](https://github.com/Pandinosaurus/Cpp-OpenJPEGxOpenCV) 优化封装之后版本

## Dependencies
- OpenCV >= 3.3.1 ( tried with a build from source on Windows with msvc2015 : https://github.com/opencv/opencv )
- OpenJPEG 2.3.0 ( tried with a build from source on Windows with msvc2015 : https://github.com/uclouvain/openjpeg )
- CMake >= 2.8  

## 说明

* `Read` 从磁盘读取`JPEG2000`文件,必须指定文件格式.
    
    ````objectivec
    /**
     * Supported codec
    */
    typedef enum CODEC_FORMAT {
        OPJ_CODEC_UNKNOWN = -1, /**< place-holder */
        OPJ_CODEC_J2K  = 0,     /**< JPEG-2000 codestream : read/write */
        OPJ_CODEC_JPT  = 1,     /**< JPT-stream (JPEG 2000, JPIP) : read only */
        OPJ_CODEC_JP2  = 2,     /**< JP2 file format : read/write */
        OPJ_CODEC_JPP  = 3,     /**< JPP-stream (JPEG 2000, JPIP) : to be coded */
        OPJ_CODEC_JPX  = 4      /**< JPX file format (JPEG 2000 Part-2) : to be coded */
    } OPJ_CODEC_FORMAT;
    ````
 * `AutoRead` 从磁盘读取`JPEG2000`文件,自动识别文件格式,返回值为文件格式;`-1`为读取失败.


## 头文件代码

````objectivec
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
````