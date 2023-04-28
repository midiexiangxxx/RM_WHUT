// #pragma once
#ifndef ROBO_ARMOR_H
#define ROBO_ARMOR_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "Params.h"

using namespace std;
using namespace cv;

namespace wutrm
{
    static bool status = false;

    class ArmorBlob
    {
    public:
        ArmorBlob()
        {
            corners = vector<Point2f>(4);
        }
        Rect rect;
        vector<Point2f> corners;
        int _class;
    };

    typedef vector<ArmorBlob> ArmorBlobs;

    class ArmorFinder
    {
    public:
        bool judgeArmor(const ArmorBlob &);
        bool matchTwoLightBar(const RotatedRect &, const RotatedRect &);
        bool getArmor(const RotatedRect &, const RotatedRect &, ArmorBlob &armor);

    private:
        inline double getAngle(const RotatedRect &);
        inline bool checkAngleDiff(const RotatedRect &, const RotatedRect &);
        inline bool checkHeightDiff(const RotatedRect &, const RotatedRect &);
    };
}

#endif //ROBO_ARMOR_H
