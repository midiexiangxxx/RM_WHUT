//
// Created by lbh on 23-7-17.
//

#ifndef ROBO7_PARAMS_H
#define ROBO7_PARAMS_H

#include <opencv2/core.hpp>
#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Dense>
#include <CameraApi.h>

#include <array>
#include <vector>
#include <map>

namespace wutrm
{
    enum ColorType {RED = 0, BLUE = 1, NONE = 2, PURPLE = 3};
    enum ArmorType {SMALL = 0, LARGE = 1};
    enum RobotType {HERO = 1, INFANTRY = 3, GUARD = 5, TOWER = 0, NOTARMOR = -1};
    enum TrackType {DETECTING = 1, LOST = 2, TRACKING = 3, LOSING = 4};

    struct CameraParams
    {
        double fx = 915.120479, fy = 915.120479, cx = 640, cy = 512; // camera params
        double k1 = -0.117114, k2 = 0.121163, k3 = -0.000718, p1 = 0, p2 = 0;
    };

    struct LightBarParams
    {
        double MIN_HW_RATIO = 0.1;
        double MAX_HW_RATIO = 0.55;
        double MAX_VERTICAL_ANGLE = 40;
    };

    struct ArmorParams
    {
        double MIN_LIGHT_RATIO = 0.6;
        double MIN_SMALL_CENTER_DISTANCE = 0.8;
        double MAX_SMALL_CENTER_DISTANCE = 2.8;
        double MIN_LARGE_CENTER_DISTANCE = 3.2;
        double MAX_LARGE_CENTER_DISTANCE = 4.3;

        double MAX_HORIZONTAL_ANGLE = 35;
    };

    struct DetectorParams
    {
        int MIN_LIGHT_VALUE = 160;
        ColorType ENEMY_COLOR = RED;
        double NUMBER_THRESHOLD = 0.7;
    };

    struct testFilterParams
    {
        double dt;
        // x 4*1: px, py, vx, vy;
        // p 4*4;
        // z 2*1: px, py;
        // f 4*4;
        // q 4*4;
        // h 2*4;
        // r 2*2;
        // i 4*4;
        // k 4*2;
        // initialize x_now p_now f q h r i
        static void x_init(Eigen::VectorXd & x)
        {
            x << 320, 240, 0, 0;
        }
        void p_init(Eigen::MatrixXd & p) const
        {
            p;
        }
        void f_init(Eigen::MatrixXd & f) const
        {
            f <<    1,  0,  dt, 0,
                    0,  1,  0,  dt,
                    0,  0,  1,  0,
                    0,  0,  0,  1;
            f.resize(4, 4);
        }
        void q_init(Eigen::MatrixXd & q) const
        {
            double var_ax, var_ay;
            double var_px = var_ax * pow(dt, 4) / 4, var_py = var_ay * pow(dt, 4) / 4;
            double var_vx = var_ax * pow(dt, 2), var_vy = var_ax * pow(dt, 2);
            double cov_xv = var_ax * pow(dt, 3) / 2, cov_yv = var_ay * pow(dt, 3) / 2;

            q <<    var_px,     0,          cov_xv,     0,
                    0,          var_py,     0,          cov_yv,
                    cov_xv,     0,          var_vx,     0,
                    0,          cov_yv,     0,          var_vy;

            q.resize(4, 4);
        }
        static void h_init(Eigen::MatrixXd & h)
        {
            h <<    1,  0,  0,  0,
                    0,  1,  0,  0;
            h.resize(2, 4);
        }
        void r_init(Eigen::MatrixXd & r) const
        {

        }
        static void i_init(Eigen::MatrixXd & i)
        {
            i = Eigen::Matrix4d::Identity();
        }
    };

    struct FilterParams
    {

    };

    struct TrackerParams
    {
        double MAX_MATCH_DISTANCE = 0.2;
        int TRACKING_THRESHOLD = 5;
        int LOST_THRESHOLD = 5;
    };
}

#endif //ROBO7_PARAMS_H
