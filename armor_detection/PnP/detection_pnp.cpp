#include<detection_pnp.h>

namespace {
    void detection_pnp::loadParam(const cv::Mat &cameraMatrix, const cv::Mat &distCoeffs){
        this->cameraMatrix = cameraMatrix;
        this->distCoeffs = distCoeffs;
    }

    void detection_pnp::solvePNP(const std::vector<cv::Point3d> &worldPoints, 
                                const std::vector<cv::Point2d> &imagePoints, 
                                cv::Mat &rvec, 
                                cv::Mat &tvec){
        cv::solvePnP(worldPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec, false, cv::SOLVEPNP_P3P);
    }

    void detection_pnp::get3DPoint(const std::vector<cv::Point3d> &worldPoints, 
                                const cv::Mat &rvec, 
                                const cv::Mat &tvec,
                                std::vector<cv::Point3d> &cameraPoints){
        for (int i = 0; i < 3;i++){
            cv::Point3d worldPoint = worldPoints[i];
            std::vector<double> cameraPoint(3);
            for (int j = 0; j < 3; i++){
                double sum = 0;
                sum += rvec.at<double>(j, 0) * worldPoint.x;
                sum += rvec.at<double>(j, 1) * worldPoint.y;
                sum += rvec.at<double>(j, 2) * worldPoint.z;
                sum += tvec.at<double>(j, 0);
                cameraPoint[i] = sum;
            }
            cameraPoints.push_back(cv::Point3d(cameraPoint[0],cameraPoint[1],cameraPoint[2]));
        }
    }

}
