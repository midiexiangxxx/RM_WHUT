//
// Created by lbh on 23-7-14.
//

#ifndef ROBO7_PERSPECTIVE_H
#define ROBO7_PERSPECTIVE_H

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/video.hpp>
#include <array>
#include <vector>

#include "Entities.h"

namespace wutrm
{
    class PnP
    {
    public:
        PnP(const MVCamera & camera, const Armor & armor)
        {
            float direct4[2][4] = {{-1, 1, 1, -1}, {1, 1, -1, -1}};
            float halfLength = armor.realLength / 2, halfHeight = armor.realHeight / 2;

            for(int i = 0; i < 4; i++)
            {
                cv::Point3f obj_p(0, direct4[0][i] * halfLength, direct4[1][i] * halfHeight);
                objectPoints.push_back(obj_p);
                imagePoints.push_back(armor.boundingRect[i]);
            }

            cv::solvePnP(objectPoints,imagePoints,
                         camera.intrinsicsMatrix, camera.distCoeffsMatrix,
                         rotationMatrix, translationMatrix
                         );
            auto cx = float(camera.intrinsicsMatrix(0, 2));
            auto cy = float(camera.intrinsicsMatrix(1, 2));
            imageDistance = cv::norm(armor.center - cv::Point2f(cx, cy));
        };

        std::vector<cv::Point3f> objectPoints;
        std::vector<cv::Point2f> imagePoints;

        std::vector<float> rotationMatrix;
        std::vector<float> translationMatrix;

        double imageDistance = 0;
    };
}

#endif //ROBO7_PERSPECTIVE_H
