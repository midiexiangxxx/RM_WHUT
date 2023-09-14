//
// Created by lbh on 23-7-15.
//

#ifndef ROBO7_FILTER_H
#define ROBO7_FILTER_H

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/video.hpp>
#include <array>
#include <vector>
#include <eigen3/Eigen/Dense>


#include "Entities.h"
#include "Perspective.h"

namespace wutrm
{
    class EKFilter
    {
    public:
        explicit EKFilter()
        {
            auto f = [this](const Eigen::VectorXd & x)
            {
                Eigen::VectorXd xNew = x;
                xNew(0) += x(4) * dt;
                xNew(1) += x(5) * dt;
                xNew(2) += x(6) * dt;
                xNew(3) += x(7) * dt;
                return xNew;
            };

            F = f;

            auto jf = [this](const Eigen::VectorXd &)
            {
                Eigen::MatrixXd f(9, 9);
                f <<    1,  0,  0,  0,  dt, 0,  0,  0,  0,
                        0,  1,  0,  0,  0,  dt, 0,  0,  0,
                        0,  0,  1,  0,  0,  0,  dt, 0,  0,
                        0,  0,  0,  1,  0,  0,  0,  dt, 0,
                        0,  0,  0,  0,  1,  0,  0,  0,  0,
                        0,  0,  0,  0,  0,  1,  0,  0,  0,
                        0,  0,  0,  0,  0,  0,  1,  0,  0,
                        0,  0,  0,  0,  0,  0,  0,  1,  0,
                        0,  0,  0,  0,  0,  0,  0,  0,  1;

                return f;
            };

            JF = jf;

            auto h = [](const Eigen::VectorXd & x)
            {
                Eigen::VectorXd z(4);
                double xc = x(0), yc = x(0), yaw = x(3), r = x(8);
                z(0) = xc - r * cos(yaw);
                z(1) = yc - r * sin(yaw);
                z(2) = x(2);
                z(3) = x(3);

                return z;
            };

            H = h;

            auto jh = [](const Eigen::VectorXd & x)
            {
                Eigen::MatrixXd h(4, 9);
                double yaw = x(3), r = x(8);
                double h14 = r * sin(yaw), h19 = -cos(yaw);
                double h24 = -r * cos(yaw), h29 = -sin(yaw);

                h <<    1,  0,  0,  h14,    0,  0,  0,  0,  h19,
                        0,  1,  0,  h24,    0,  0,  0,  0,  h29,
                        0,  0,  1,  0,      0,  0,  0,  0,  0,
                        0,  0,  0,  1,      0,  0,  0,  0,  0;

                return h;
            };

            JH = jh;

            auto qv = std::vector<double>{1e-2, 1e-2, 1e-2, 2e-2, 5e-1, 5e-2, 1e-4, 4e-2, 1e-3};

            Q.diagonal() << qv[0], qv[1], qv[2], qv[3], qv[4], qv[5], qv[6], qv[7], qv[8];

            auto rv = std::vector<double>{1e-1, 1e-1, 1e-1, 2e-1};

            R.diagonal() << rv[0], rv[1], rv[2], rv[3];

            Eigen::DiagonalMatrix<double, 9> p0;
            p0.setIdentity();


        };

        using NonlinearFunc = std::function<Eigen::VectorXd(const Eigen::VectorXd &)>;
        using JacobianFunc = std::function<Eigen::MatrixXd(const Eigen::VectorXd &)>;

        void setState(const Eigen::VectorXd &x0)
        {
            xPost = x0;
        }

        void init(const Armor & armor)
        {
            double x = armor.pos.x, y = armor.pos.y, z = armor.pos.z;

        }

        Eigen::MatrixXd predict()
        {
            xPredict = F(xPost);
            fPredict = JF(xPost);
            // pPredict = fPredict * pPost * fPredict.transpose() + Q;
            xPost = xPredict;
            pPost = pPredict;

            return xPredict;
        }

        Eigen::MatrixXd update(const Eigen::VectorXd & z)
        {

        }

        double dt = 0.0;

        Eigen::VectorXd xPost, xPredict;
        Eigen::MatrixXd K, I, pPredict, pPost, fPredict;
        Eigen::DiagonalMatrix<double, 9> Q;
        Eigen::DiagonalMatrix<double, 4> R;

//        auto f(Eigen::VectorXd & x) const
//        {
//            Eigen::VectorXd xNew = x;
//            xNew(0) += x(4) * dt;
//            xNew(1) += x(5) * dt;
//            xNew(2) += x(6) * dt;
//            xNew(3) += x(7) * dt;
//            return xNew;
//
//        }
        NonlinearFunc F, H;
        JacobianFunc JF, JH;

    };

    class KalmanFilterOnImage // test filter
    {
        // x 4*1: px, py, vx, vy;
        // p 4*4;
        // z 2*1: px, py;
        // f 4*4;
        // q 4*4;
        // h 2*4;
        // r 2*2;
        // i 4*4;
        // k 4*2;
        void init(const testFilterParams & fp) // initialize x_now p_now f q h r i
        {
            fp.x_init(x_now);
            fp.p_init(p_now);
            fp.f_init(f);
            fp.q_init(q);
            fp.h_init(h);
            fp.r_init(r);
            fp.i_init(i);

        }
        void predict()
        {
            x_predict = f * x_now;
            p_predict = f * p_now * f.transpose() + q;

            x_pre = x_predict;
            p_pre = p_predict;
        }

        void update(const Eigen::VectorXd & z_measure)
        {
            z = z_measure;

            Eigen::MatrixXd s = h * p_pre * h.transpose() + r;
            k = p_pre * h.transpose() * s.inverse();

            x_now = x_pre + k * (z - h * x_pre);

            Eigen::MatrixXd temp = i - k * h;
            p_now = temp * p_pre * temp.transpose() + k * r * k.transpose();
        }

        double dt;

        Eigen::VectorXd x_predict, x_now, x_pre, z;
        Eigen::MatrixXd p_predict, p_now, p_pre, f, q, h, r, k, i;
    };

}

#endif //ROBO7_FILTER_H
