// #pragma once
#ifndef ROBO_PARAMS_H
#define ROBO_PARAMS_H

#include <opencv2/opencv.hpp>
#include <string>
#include <tuple>

using namespace std;

namespace wutrm
{
    class RobotParam
    {
    public:
        static double camara_shoot_x;
        static double camara_shoot_y;
        static double camara_shoot_z;

        static double fx;           // 相机内参
        static double fy;
        static double u0;
        static double v0;
        static double k1;
        static double k2;
        static double k3;
        static double p1;
        static double p2;
    };

    class DetectParam
    {
    public:
        static int binary_threshold;  //二值化阈值
        static int color;  //阵营颜色
        static int use_num_classify;  //是否使用数字识别
        static string color_channel;  //选用的颜色通道
        static int erode_index[2];
        static int dilate_index[2];
        static int kernel_index[2];

    };

    class ArmorDetectParam
    {
    public:
        static float angle_diff_max;     // 灯条角度差
        static float light_bar_ratio_max; // 灯条长宽比
        static float light_bar_ratio_min;
        static float light_bar_area_max; // 灯条面积
        static float light_bar_area_min;
        static float armor_ratio_max; // 装甲板长宽比
        static float armor_ratio_min;
        static float light_bar_center_diff; // 两灯条中心像素差
        static float light_bar_angle_min;   // 灯条角度
        static float light_bar_angle_max;
        static float rectangle_likely;      // 多像矩形
        static float light_bar_length_ratio; // 两灯条长度比例

        static int armor_area_min; // 装甲板面积
        static int armor_area_max;

        static float armor_real_height;
        static float armor_real_width;

        // debug参数
        static bool show_thresh;        // 是否显示二值化图像
        static bool show_classify;      // 是否显示分类图像
        static bool debug_show;         // 是否显示原图框出装甲板的图像
        static bool show_light_bar_info; // 控制台显示灯条信息
        static bool show_armor_info;    // 控制台显示装甲板信息
    };
}

#endif //ROBO_PARAMS_H
