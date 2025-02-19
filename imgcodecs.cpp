#include <stdlib.h>
#include "imgcodecs.h"

// Image
Mat Image_IMRead(const char* filename, int flags) {
    cv::Mat img = cv::imread(filename, flags);
    return new cv::Mat(img);
}

Mats Image_IMReadMulti(const char* filename, int flags) {
    std::vector<cv::Mat> dst;
    Mats m = Mats();

    bool b = cv::imreadmulti(filename, dst, flags);
    if (b) {
        m.mats = new Mat[dst.size()];
        for (size_t i = 0; i < dst.size(); ++i) {
            m.mats[i] = new cv::Mat(dst[i]);
        }
        m.length = (int)dst.size();        
    }

    return m;
}

Mats Image_IMReadMulti_WithParams(const char* filename, int start, int count, int flags) {
    std::vector<cv::Mat> dst;
    auto m = Mats();
    
    auto b = cv::imreadmulti(filename, dst, start, count, flags);
    if (b) {
        m.mats = new Mat[dst.size()];
        for (size_t i = 0; i < dst.size(); ++i) {
            m.mats[i] = new cv::Mat(dst[i]);
        }
        m.length = (int)dst.size();        
    }

    return m;
}


bool Image_IMWrite(const char* filename, Mat img) {
    return cv::imwrite(filename, *img);
}

bool Image_IMWrite_WithParams(const char* filename, Mat img, IntVector params) {
    std::vector<int> compression_params;

    for (int i = 0, *v = params.val; i < params.length; ++v, ++i) {
        compression_params.push_back(*v);
    }

    return cv::imwrite(filename, *img, compression_params);
}

void Image_IMEncode(const char* fileExt, Mat img, void* vector) {
    auto vectorPtr = reinterpret_cast<std::vector<uchar> *>(vector);
    cv::imencode(fileExt, *img, *vectorPtr);
}

void Image_IMEncode_WithParams(const char* fileExt, Mat img, IntVector params, void* vector) {
    auto vectorPtr = reinterpret_cast<std::vector<uchar> *>(vector);
    std::vector<int> compression_params;

    for (int i = 0, *v = params.val; i < params.length; ++v, ++i) {
        compression_params.push_back(*v);
    }

    cv::imencode(fileExt, *img, *vectorPtr, compression_params);
}

Mat Image_IMDecode(ByteArray buf, int flags) {
    std::vector<uchar> data(buf.data, buf.data + buf.length);
    cv::Mat img = cv::imdecode(data, flags);
    return new cv::Mat(img);
}

void Image_IMDecodeIntoMat(ByteArray buf, int flags, Mat dest) {
    std::vector<uchar> data(buf.data, buf.data + buf.length);
    cv::imdecode(data, flags, dest);
}
