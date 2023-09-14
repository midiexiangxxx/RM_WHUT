//
// Created by lbh on 23-7-21.
//

#ifndef ROBO7_TRACKER_H
#define ROBO7_TRACKER_H

#include <eigen3/Eigen/Eigen>
#include <vector>

#include "Filter.h"
#include "Perspective.h"
#include "Entities.h"

namespace wutrm
{
    class Tracker
    {
    public:
        Tracker() = default;
        void init(const std::vector<Armor> & armors)
        {
            if(armors.empty())
            {
                return;
            }
            CameraParams cp;
            MVCamera camera(cp);
            auto minDist = DBL_MAX;
            trackingArmor = armors[0];
            for(const auto & armor : armors)
            {
                auto imageDistance = PnP(camera, armor).imageDistance;
                if(imageDistance < minDist)
                {
                    minDist = imageDistance;
                    trackingArmor = armor;
                }
            }
            trackType = DETECTING;
            trackingID = trackingArmor.ID;
        }

        void update(const std::vector<Armor> & armors)
        {

        }

        void initEKF();

        Armor trackingArmor;
        TrackType trackType = DETECTING;
        int trackingID = 0;
    };
}


#endif //ROBO7_TRACKER_H
