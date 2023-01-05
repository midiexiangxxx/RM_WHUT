#ifndef _ARMOR_DETECTION_
#define _ARMOR_DETECTION_

#include <iostream>
#include <vector>
#include <opencv2\opencv.hpp>
#include <cmath>

#define _PI_ 3.141592653
#define InputImg cv::Mat
#define OutputImg cv::Mat

using namespace cv;
using namespace std;

namespace armor_detection{
    class armor_detecte{
    public:
        armor_detecte();
        armor_detecte(const InputImg &);

        void setImg_origin(const InputImg &);

        void loadParam(bool enermy_color, bool isParam,
                    int alpha = -1, int beta = -1, int thresh_value = -1,

                    double light_bit_min = -1, double light_bit_max = -1, double light_angle_min = -1, double light_angle_max = -1,
                    double light_area_min = -1, double light_area_max = -1, double light_angle_abs = 4,

                    double armor_bit_min = -1, double armor_bit_max = -1, double armor_area_min = -1, double armor_area_max = -1);
        
        // 得到与运算图像                
        void init(); 

        void contours();
        
        void contours_to_light();

        void light_to_armor();

        void drawrotate();

        //tool
        void showImg();
        void drawContours();
        const static bool ENERMY_COLOR_BLUE = 1;
        const static bool ENERMY_COLOR_RED = 0;

    private:
        cv::Mat img_origin, img_change, img_thresh, img_erode, img_dilate, img_and, img_combination;

        bool enermy_color;
        
        // init
        int alpha;
        int beta;
        int thresh_value;

        // light
        double light_bit_min;
        double light_bit_max;
        double light_angle_min;
        double light_angle_max;
        double light_area_max;
        double light_area_min;
        double light_angle_abs;

        // armor true_bit = 127:230 = 0.552
        double armor_bit_min;
        double armor_bit_max;
        double armor_area_min;
        double armor_area_max;

        //contours
        std::vector<cv::RotatedRect> contours_rects;
        std::vector<RotatedRect> light_rects;
        std::vector<RotatedRect> armor_rects;
        
        //tool
        void four_to_one(const std::vector<cv::Mat> &imgs, OutputImg &ans);
        };
}
#endif // !_ARMOR_DETECTION_