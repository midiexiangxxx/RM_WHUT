//
// Created by lbh on 23-7-14.
//

#ifndef ROBO7_DETECTOR_H
#define ROBO7_DETECTOR_H

#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>

#include <cmath>
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <map>


#include "Entities.h"
#include "Params.h"

#include <CameraApi.h>

namespace wutrm
{
    class Detector
    {
    public:
        explicit Detector(DetectorParams dp, LightBarParams lp, ArmorParams ap)
        {
            d = dp;
            l = lp;
            a = ap;
            netPath = "../model/fc.onnx";
            lblPath = "../model/label.txt";
            net = cv::dnn::readNetFromONNX(netPath);
            std::ifstream label;
            text[HERO] = "Hero";
            text[INFANTRY] =  "Infantry";
            text[GUARD] = "Guard";
            text[TOWER] = "Tower";
        }

        DetectorParams d{};
        LightBarParams l{};
        ArmorParams a{};
        std::string netPath, lblPath;
        cv::dnn::Net net;
        std::map<RobotType, std::string> text;

        [[nodiscard]] std::vector<Armor> detectResult(cv::Mat &bgrImage, bool draw = true)
        {
            cv::Mat binaryImage = preprocessImage(bgrImage);
            auto lightBars = findLightBars(bgrImage, binaryImage);
            std::vector<Armor> armors = findArmors(bgrImage, lightBars);

            if(draw)
            {
                drawArmors(bgrImage, armors);

                // cv::imshow("binary", binaryImage);
            }

            return armors;
        }

        void drawArmors(cv::Mat & bgrImage, const std::vector<Armor> & armors)
        {
            if(armors.empty())
            {
                return;
            }
            for(const auto& armor : armors)
            {
                // auto leftCenter = armor.leftLightBar.center, rightCenter = armor.rightLightBar.center;
                auto leftTop = armor.leftLightBar.top, rightTop = armor.rightLightBar.top;
                auto leftBottom = armor.leftLightBar.bottom, rightBottom = armor.rightLightBar.bottom;
                cv::line(bgrImage, leftTop, rightTop, CV_RGB(0, 255, 0), 5);
                cv::line(bgrImage, leftBottom, rightBottom, CV_RGB(0, 255, 0), 5);
                cv::line(bgrImage, leftTop, leftBottom, CV_RGB(0, 255, 0), 5);
                cv::line(bgrImage, rightTop, rightBottom, CV_RGB(0, 255, 0), 5);

                cv::putText(bgrImage, text[armor.robotType], armor.center, CV_FONT_HERSHEY_COMPLEX_SMALL, 0.5, CV_RGB(0, 255 ,0), 0.3);
            }

        }


        [[nodiscard]] cv::Mat preprocessImage(const cv::Mat & bgrImage) const
        {
            cv::Mat grayImage, binaryImage;
            cv::cvtColor(bgrImage, grayImage, cv::COLOR_BGR2GRAY);
            cv::threshold(grayImage, binaryImage, d.MIN_LIGHT_VALUE, 255, cv::THRESH_BINARY);
            return binaryImage;
        }

        [[nodiscard]] std::vector<LightBar> findLightBars(const cv::Mat & bgrImage, const cv::Mat & binaryImage) const
        {
            std::vector<std::vector<cv::Point>> contours;
            std::vector<cv::Vec4i> hierarchy;
            cv::findContours(binaryImage, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
            std::vector<LightBar> lightBars;

            for(const auto & contour : contours)
            {
                if(contour.size() < 5) continue;
                cv::RotatedRect rotatedRect = cv::minAreaRect(contour);
                LightBar lightBar(rotatedRect);

                if(isLightBar(lightBar))
                {
                    auto rect = rotatedRect.boundingRect();

                    if(isRectInImage(rect, bgrImage))
                    {
                        int sumRed = 0, sumBlue = 0;
                        auto roi = bgrImage(rect);

                        for(int i = 0; i < roi.rows; i++)
                        {
                            for(int j = 0; j < roi.cols; j++)
                            {
                                if(cv::pointPolygonTest(contour, cv::Point2f(float(j + rect.x), float(i + rect.y)), false) >= 0)
                                {
                                    // BGR Image
                                    sumRed += roi.at<cv::Vec3b>(i, j)[2];
                                    sumBlue += roi.at<cv::Vec3b>(i, j)[0];
                                }
                            }
                        }
                        lightBar.color = sumRed > sumBlue ? RED : BLUE;
                        lightBar.sum = sumRed - sumBlue;
                        // cv::line(bgrImage, lightBar.top, lightBar.bottom, CV_RGB(255, 255, 0), 5);
                        lightBars.emplace_back(lightBar);
                    }
                }
            }

            return lightBars;
        }

        [[nodiscard]] std::vector<Armor> findArmors(const cv::Mat & bgrImage, const std::vector<LightBar> & lightBars)
        {
            // int count_armor = 0;
            std::vector<Armor> armors;
            for(auto lightBar1 = lightBars.begin(); lightBar1 != lightBars.end(); lightBar1++)
            {
                for(auto lightBar2 = lightBar1 + 1; lightBar2 != lightBars.end(); lightBar2++)
                {
                    // std::cout << lightBar1->center << " " << lightBar2->center << " " << d.ENEMY_COLOR << " " << ++ count_armor << std::endl;
                    if(lightBar1->color != d.ENEMY_COLOR || lightBar2->color != d.ENEMY_COLOR)
                    {
                        continue;
                    }

                    if(containLightBar(*lightBar1, *lightBar2, lightBars))
                    {
                        continue;
                    }

                    Armor armor(*lightBar1, *lightBar2);
                    // std::cout << armor.center << std::endl;
                    if(isArmor(armor))
                    {
                        extractNumberROI(bgrImage, armor);
                        classifyNumber(armor);
                        if((armor.armorType == LARGE && armor.robotType != HERO) || (armor.armorType == SMALL && (armor.robotType == HERO || armor.robotType == NOTARMOR)))
                        {
                            continue;
                        }
                        armors.emplace_back(armor);
                        // std::cout << armors.size() << " " << armor.center << std::endl;
                    }
                }
            }
            return armors;
        }

        [[nodiscard]] bool isLightBar(const LightBar & lightBar) const
        {
            double hwRatio = lightBar.width / lightBar.length;
            return l.MIN_HW_RATIO < hwRatio && hwRatio < l.MAX_HW_RATIO && lightBar.angle < l.MAX_VERTICAL_ANGLE;
        }

        static bool isRectInImage(cv::Rect_<int> rect, const cv::Mat & bgrImage)
        {
            return  0 <= rect.x && 0 <= rect.width && rect.x + rect.width <= bgrImage.cols &&
                    0 <= rect.y && 0 <= rect.height && rect.y + rect.height <= bgrImage.rows;
        }

        bool isArmor(Armor & armor) const
        {
            LightBar leftLightBar = armor.leftLightBar, rightLightBar = armor.rightLightBar;
            double leftLength = leftLightBar.length, rightLength = rightLightBar.length;
            auto leftCenter = leftLightBar.center, rightCenter = rightLightBar.center;

            double lightBarLengthRatio = leftLength < rightLength ? leftLength / rightLength : rightLength / leftLength;
            bool checkLengthRatio = lightBarLengthRatio > a.MIN_LIGHT_RATIO;

            double averageLightBarLength = (leftLength + rightLength) / 2;
            double center_distance = cv::norm(leftCenter - rightCenter) / averageLightBarLength;
            bool checkCenterDistanceSmall = a.MIN_SMALL_CENTER_DISTANCE < center_distance && center_distance < a.MAX_SMALL_CENTER_DISTANCE;
            bool checkCenterDistanceLarge = a.MIN_LARGE_CENTER_DISTANCE < center_distance && center_distance < a.MAX_LARGE_CENTER_DISTANCE;
            bool checkCenterDistance = checkCenterDistanceSmall || checkCenterDistanceLarge;

            auto diff = leftCenter - rightCenter;
            auto angle = std::abs(std::atan(diff.y / diff.x)) / CV_PI * 180;
            bool checkAngle = angle < a.MAX_HORIZONTAL_ANGLE;

            bool isArmor = checkLengthRatio && checkCenterDistance && checkAngle;
            armor.armorType = center_distance > a.MIN_LARGE_CENTER_DISTANCE ? LARGE : SMALL;
            return isArmor;
        }

        static bool containLightBar(const LightBar & lightBar1, const LightBar & lightBar2, const std::vector<LightBar> & lightBars)
        {
            auto points = std::vector<cv::Point2f> {lightBar1.top, lightBar1.bottom, lightBar2.top, lightBar2.bottom};
            auto boundingRect = cv::boundingRect(points);

            for(const auto & lightBar : lightBars)
            {
                if(lightBar.center == lightBar1.center || lightBar.center == lightBar2.center)
                {
                    continue;
                }

                if( boundingRect.contains(lightBar.top) ||
                    boundingRect.contains(lightBar.bottom) ||
                    boundingRect.contains(lightBar.center))
                {
                    // printf("?????");
                    return true;
                }
            }
            // printf("!!!!!");
          return false;
//
//            std::function<bool(LightBar)> isBounding = [&lightBar1, &lightBar2, &boundingRect](LightBar lightBar) -> bool
//            {
//                if(lightBar.center != lightBar1.center && lightBar.center == lightBar2.center)
//                {
//                    if( boundingRect.contains(lightBar.top) ||
//                        boundingRect.contains(lightBar.bottom) ||
//                        boundingRect.contains(lightBar.center))
//                    {
//                        return true;
//                    }
//                }
//                return false;
//            };
//            bool flag = std::any_of(lightBars.begin(), lightBars.end(), isBounding);
//            std::cout << "contain lightbar? " << flag << std::endl;
//            return flag;
        }


        static void extractNumberROI(const cv::Mat & bgrImage, Armor & armor)
        {
            const int lightBarLength = 12;
            const int roiHeight = 28;
            const int smallArmorWidth = 32;
            const int largeArmorWidth = 54;
            const cv::Size roiSize(20, 28);

            cv::Point2f preVertices[4] = {armor.leftLightBar.bottom, armor.leftLightBar.top,
                                          armor.rightLightBar.top, armor.rightLightBar.bottom};

            const int topY = (roiHeight - lightBarLength) / 2 - 1;
            const int botY = topY + lightBarLength;
            const int roiWidth = armor.armorType == SMALL ? 32 : 54;
            cv::Point2f newVertices[4] = {cv::Point(0, botY), cv::Point(0, topY),
                                          cv::Point(roiWidth - 1, topY), cv::Point(roiWidth - 1, botY)};

            cv::Mat roi;
            auto rotationMatrix = cv::getPerspectiveTransform(preVertices, newVertices);
            cv::warpPerspective(bgrImage, roi, rotationMatrix, cv::Size(roiWidth, roiHeight));

            roi = roi(cv::Rect(cv::Point((roiWidth - roiSize.width) / 2, 0), roiSize));
            cv::cvtColor(roi, roi, cv::COLOR_BGR2GRAY);
            cv::threshold(roi, roi, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
            armor.roi = roi;
        }

        void classifyNumber(Armor & armor)
        {
            cv::Mat image = armor.roi.clone() / 255.0;

            cv::Mat blob;
            cv::dnn::blobFromImage(image, blob, 1.0, cv::Size(28, 20));

            net.setInput(blob);
            cv::Mat outputs = net.forward();

            float maxProb = *std::max_element(outputs.begin<float>(), outputs.end<float>());
            cv::Mat softmaxProb;
            cv::exp(outputs - maxProb, softmaxProb);
            float sum = static_cast<float>(cv::sum(softmaxProb)[0]);
            softmaxProb /= sum;

            double confidence;
            cv::Point idLoc;
            cv::minMaxLoc(softmaxProb.reshape(1, 1), nullptr, &confidence, nullptr, &idLoc);
            int labelId = idLoc.x;

            armor.robotType = labelId == 1 ? HERO : INFANTRY;
            if(labelId == 6) armor.robotType = GUARD;
            if(labelId == 0) armor.robotType = TOWER;
            if(confidence < d.NUMBER_THRESHOLD || labelId == 8) armor.robotType = NOTARMOR;
            else armor.ID = labelId;
            // std::cout << "label id " << labelId << std::endl;
       }
    };
}

#endif //ROBO7_DETECTOR_H
