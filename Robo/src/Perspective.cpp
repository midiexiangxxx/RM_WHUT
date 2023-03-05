#include <Perspective.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace wutrm;

//!DONE! TODO 补全相机内参矩阵、畸变矩阵、枪管到相机偏移量、装甲板尺寸

Mat Perspective::cameraMatrixParams() {
    double fx = wutrm::RobotParam::fx, fy = wutrm::RobotParam::fy;
    double u0 = wutrm::RobotParam::u0, v0 = wutrm::RobotParam::v0;
    Mat cam = (Mat_<double>(3, 3)<<fx, 0, u0, 0, fy, v0, 0, 0, 1);
    return cam;
}

Mat Perspective::distCoeffsParams() {
    double k1 = wutrm::RobotParam::k1, k2 = wutrm::RobotParam::k2, k3 = wutrm::RobotParam::k3;
    double p1 =  wutrm::RobotParam::p1, p2 =  wutrm::RobotParam::p2;
    Mat dis = (Mat_<double>(1, 5)<<k1, k2, k3, p1, p2);
    return dis;
}

std::pair<Mat,Mat> Perspective::PnP(const Mat& img, const Mat& cam, const Mat& dis) {
    float half_width = wutrm::ArmorDetectParam::armor_real_width / 2;
    float half_height = wutrm::ArmorDetectParam::armor_real_height / 2;

    double c2s_x = wutrm::RobotParam::camara_shoot_x;
    double c2s_y = wutrm::RobotParam::camara_shoot_y;
    double c2s_z = wutrm::RobotParam::camara_shoot_z;

    vector<Point3f> obj = vector<Point3f>{
            Point3f(-half_width, -half_height, 0),
            Point3f(half_width, -half_height, 0),
            Point3f(half_width, half_height, 0),
            Point3f(-half_width, half_height, 0)
    };

    // Mat rVec = Mat::zeros(3, 1, CV_64FC1);
    // Mat tVec = Mat::zeros(3, 1, CV_64FC1);
    Mat rVec;
    Mat tVec;

    // Mat c2s = (Mat_<double>(3, 1)<<c2s_x, c2s_y, c2s_z);

    solvePnP(obj, img, cam, dis, rVec, tVec, true, cv::SOLVEPNP_EPNP);
    return std::make_pair(rVec,tVec);
}


