//
// Created by caesar on 19-3-5.
//

#include "OpenJpeg2KTool.h"

using namespace kekxv;

int OpenJpeg2KTool::Read(const char *FilePath, Mat *outMat, int format) {
    opj_dparameters mparameters{};
    if (!init(&mparameters)) {
        return -1;
    }
    std::strcpy(mparameters.infile, FilePath);
    opj_stream_t *mopj_stream_fname = nullptr; /* Stream */
    mopj_stream_fname = opj_stream_create_default_file_stream(mparameters.infile, true);
    if (mopj_stream_fname == nullptr) {
        // fprintf(stderr, "ERROR -> failed to create the stream from the file %s\n", mparameters.infile);
        return -2;
    }
    opj_codec_t *mopj_codec = nullptr;
    mopj_codec = opj_create_decompress((OPJ_CODEC_FORMAT) format);
    opj_setup_decoder(mopj_codec, &mparameters);
    opj_codec_set_threads(mopj_codec, 4);

    opj_image_t *mopj_img = nullptr;
    if (!opj_read_header(mopj_stream_fname, mopj_codec, &mopj_img)) { /* you need to read the header before decoding */
        opj_stream_destroy(mopj_stream_fname);
        opj_destroy_codec(mopj_codec);
        return -3;//return error_message("Unable to read_header in main.");
    }
    if (!opj_decode(mopj_codec, mopj_stream_fname, mopj_img)) { /* decoding */
        opj_stream_destroy(mopj_stream_fname);
        opj_destroy_codec(mopj_codec);
        return -4;//return error_message("Unable to decode in main.");
    }

    int ret = Jp2kToMat(mopj_img, outMat);

    opj_stream_destroy(mopj_stream_fname);
    opj_destroy_codec(mopj_codec);
    opj_image_destroy(mopj_img);
    return ret ? 1 : -9;
}

bool OpenJpeg2KTool::init(opj_dparameters *mparameters) {
    if (mparameters) {
        memset(mparameters, 0, sizeof(opj_dparameters));
        mparameters->decod_format = 1; //jp2
        mparameters->cod_format = 2; //bmp
        mparameters->cp_reduce = 0; //full resolution
        opj_set_default_decoder_parameters(mparameters);
        return true;
    }
    return false;
}

bool OpenJpeg2KTool::Jp2kToMat(opj_image_t *mopj_img, Mat *outMat) {
    int width = mopj_img->comps->w;
    int height = mopj_img->comps->h;
    int channels = mopj_img->numcomps;
    *outMat = cv::Mat(cv::Size(width, height), CV_8UC3);
    /* iterate through the image pixels stored in the components data of an opj_image pointer */
    for (int index = 0; index < width * height; index++) {
        for (int ch = 0; ch < channels; ch++) {
            // Based on imagemagick implementation https://github.com/ImageMagick/ImageMagick/blob/master/coders/jp2.c
//        outMat->data[i] = *(mopj_img->comps->data++);
            outMat->data[index * channels + ch] = static_cast<uchar>(mopj_img->comps[channels - ch -1].data[index]);
        }
    }

    return true;
}


int OpenJpeg2KTool::AutoRead(const char *FilePath, Mat *outMat){
    int type = -1;
    cv::Mat result;
        for (int i = 0; i <= 4; i++)
            if (OpenJpeg2KTool::Read(FilePath, &result, i) >= 0) {
                imshow("t",result);
                waitKey(0);
                return i;
            }
    return type;
}