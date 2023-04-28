// #pragma once
#ifndef ROBO_LIGHTBAR_H
#define ROBO_LIGHTBAR_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "Params.h"

using namespace cv;
using namespace std;

namespace wutrm
{
    enum DETECT_COLOR  //判断对方采用的颜色
    {
        RED = 0,
        BLUE = 1,
        OTHERS = -1
    };

    enum COLOR_CHANNEL
    {
        BGR = 0,
        HSV = 1,
        GREEN = 2,
        GRAY = 3,
        MIXED = 4,
        HSV_BGR_GRAY = 5
    };

    typedef std::vector<RotatedRect> LightBarBlobs;

    class LightBarFinder
    {
    public:
        LightBarFinder();
        bool findLightBarBlobs(const cv::Mat &frame,
                                      LightBarBlobs &lightBarBlobs,
                                      const cv::Point2f &roi_offset = cv::Point2f(0, 0));
        static inline bool isValidLightBarBlob(const RotatedRect &);
        void setEnemyColor(int color)
        {
            enemy_color = (color & 0x01);
        }
        int enemy_color = DetectParam::color;
        //int enemy_color = 1;
        Mat kernel_erode;
        Mat kernel_dilate;
    private:
        static inline bool checkAspectRatio(const double &);
        static inline bool checkArea(const double &);
        static inline bool checkAngle(const double &angle);
        static inline bool checkRatioAndArea(const double &ratio, const double &area);
        bool isRightColor(const Mat &frame, const RotatedRect &rotatedRect);

    };
}

#endif //ROBO_LIGHTBAR_H
