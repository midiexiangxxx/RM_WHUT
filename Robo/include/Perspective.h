#ifndef ROBO_PERSPECTIVE_H
#define ROBO_PERSPECTIVE_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "Params.h"

using namespace cv;
using namespace std;

namespace wutrm
{
    class Perspective
    {
    public:
        std::pair<Mat,Mat> PnP(const Mat& img, const Mat& cam, const Mat& dis);  // PnP解算
        Mat cameraMatrixParams();  // 相机内参矩阵
        Mat distCoeffsParams();  // 相机畸变矩阵
    };
}

#endif //ROBO_PERSPECTIVE_H
