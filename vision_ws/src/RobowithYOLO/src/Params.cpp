#include "Params.h"

using namespace std;

namespace wutrm
{
    int DetectParam::color                              = 1;
    int DetectParam::binary_threshold                   = 180;
    int DetectParam::use_num_classify;
    string DetectParam::color_channel;
    int DetectParam::erode_index[2]                     = {3, 3};
    int DetectParam::dilate_index[2]                    = {3, 5};
    int DetectParam::kernel_index[2];

    float ArmorDetectParam::angle_diff_max              = 25;
    float ArmorDetectParam::light_bar_ratio_max         = 10;
    float ArmorDetectParam::light_bar_ratio_min         = 1.0;
    float ArmorDetectParam::light_bar_area_max          = 3200;
    float ArmorDetectParam::light_bar_area_min          = 60;
    float ArmorDetectParam::armor_ratio_max             = 5.5;
    float ArmorDetectParam::armor_ratio_min             = 1.4;
    float ArmorDetectParam::light_bar_center_diff       = 90;
    float ArmorDetectParam::light_bar_angle_min         = -22;
    float ArmorDetectParam::light_bar_angle_max         = 22;
    float ArmorDetectParam::rectangle_likely            = 0.3;
    float ArmorDetectParam::light_bar_length_ratio      = 2;
    int ArmorDetectParam::armor_area_min                = 100;
    int ArmorDetectParam::armor_area_max                = 80000;
    bool ArmorDetectParam::show_thresh                  = false;
    bool ArmorDetectParam::show_light_bar_info          = false;
    bool ArmorDetectParam::show_armor_info              = false;
    bool ArmorDetectParam::show_classify;
    bool ArmorDetectParam::debug_show;

    float ArmorDetectParam::armor_real_width = 55.5;
    float ArmorDetectParam::armor_real_height = 133.8;

    double RobotParam::camara_shoot_x;
    double RobotParam::camara_shoot_y;
    double RobotParam::camara_shoot_z;
    double RobotParam::fx = 875.237354;
    double RobotParam::fy = 875.237354;
    double RobotParam::u0 = 640.0;
    double RobotParam::v0 = 512.0;
    double RobotParam::k1 = -0.11855;
    double RobotParam::k2 = 0.141896;
    double RobotParam::k3 = -0.073338;
    double RobotParam::p1 = 0;
    double RobotParam::p2 = 0;

}
