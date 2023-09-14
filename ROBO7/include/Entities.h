//
// Created by lbh on 23-7-13.
//

#ifndef ROBO7_ENTITIES_H
#define ROBO7_ENTITIES_H

#include <opencv2/core.hpp>
#include <CameraApi.h>

#include <array>
#include <vector>

#include "Params.h"

namespace wutrm
{
    class MVCamera
    {
    public:

        explicit MVCamera(CameraParams c)
        {
            intrinsicsMatrix = cv::Matx33d(c.fx, 0, c.cx, 0, c.fy, c.cy, 0, 0, 1);
            distCoeffsMatrix = (cv::Mat_<double>(1, 5) << c.k1, c.k2, c.k3, c.p1, c.p2);
        }
        cv::Matx33d intrinsicsMatrix;
        cv::Mat distCoeffsMatrix;
    };

    bool cmp(cv::Point2f u, cv::Point2f v)
    {
        return u.y == v.y ? u.x < v.x : u.y < v.y;
    }

    class LightBar
    {
    public:
        explicit LightBar(cv::RotatedRect lightRect)
        {
            // rect = lightRect;
            cv::Point2f p[4];
            lightRect.points(p);
            std::sort(p, p + 4, cmp);
            top = (p[0] + p[1]) / 2;
            bottom = (p[2] + p[3]) / 2;
            center = (top + bottom) / 2;

            length = cv::norm(top - bottom);
            width = cv::norm(p[0] - p[1]);

            angle = std::atan2(std::abs(top.x - bottom.x), std::abs(top.y - bottom.y)) / CV_PI * 180;
        }
        ColorType color = RED;
        double length, width, angle;
        int sum = 0;
        cv::Point2f center, top, bottom;
        // cv::RotatedRect rect;
    };


    class Armor
    {
    public:
        explicit Armor(LightBar lLightBar, LightBar rLightBar)
                : leftLightBar(lLightBar) , rightLightBar(rLightBar)
        {
            if(leftLightBar.center.x > rightLightBar.center.x)
            {
                std::swap(leftLightBar, rightLightBar);
            }
            center = (leftLightBar.center + rightLightBar.center) / 2;
            if(armorType == LARGE && robotType == HERO)
            {
                realLength = 235;
                realHeight = 60;
            }
            boundingRect.push_back(leftLightBar.top);
            boundingRect.push_back(rightLightBar.top);
            boundingRect.push_back(rightLightBar.bottom);
            boundingRect.push_back(leftLightBar.bottom);
        }

        cv::Point2f center;
        std::vector<cv::Point2f> boundingRect;
        ArmorType armorType = SMALL;
        RobotType robotType = INFANTRY;
        int ID = 0;
        float realLength = 140, realHeight = 60; // unit mm 127&125
        LightBar leftLightBar, rightLightBar;
        cv::Mat roi;
        struct position
        {
            double x = 0;
            double y = 0;
            double z = 0;
        } pos;
    };

    class Number
    {

    };

}

#endif //ROBO7_ENTITIES_H
