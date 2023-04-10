#ifndef ROBO_PREPROCESS_H
#define ROBO_PREPROCESS_H

#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

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
}

#endif //ROBO_PREPROCESS_H
