#ifndef DETECTION_PNP
#define DETECTION_PNP

#include<opencv2\opencv.hpp>
#include<vector>

namespace{
    class detection_pnp{
    public:
        void loadParam(const cv::Mat &cameraMatrix, const cv::Mat &distCoeffs);
        void solvePNP(const std::vector<cv::Point3d> &, const std::vector<cv::Point2d> &, cv::Mat &, cv::Mat &);
        void get3DPoint(const std::vector<cv::Point3d> &, const cv::Mat &, const cv::Mat &, std::vector<cv::Point3d> &);

    private:
        cv::Mat cameraMatrix, distCoeffs;//相机内参与畸变参数
    };
}
#endif // !DETECTION_PNP
