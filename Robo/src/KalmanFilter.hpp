#ifndef KALMAN_FILTER_
#define KALMAN_FILTER_
namespace filter{

#include "Eigen/Dense"
using cVxdMove = const Eigen::VectorXd&&;
using Vxd = Eigen::VectorXd;
class KalmanFilter
{
public:
    KalmanFilter(){
        this->is_initialized = false;
    }

    ~KalmanFilter();

    KalmanFilter(cVxdMove x_in,cVxdMove p_in,cVxdMove f_in,cVxdMove u_in,cVxdMove q_in,cVxdMove h_in,cVxdMove r_in): 
     x(x_in),f(f_in),p(p_in),h(h_in),u(u_in),q(q_in),r(r_in),is_initialized(true){};

    inline Eigen::VectorXd GetX() const{
        return this->x;
    }

    void Estimate(){
        this->x = this->f * this->x;
        Eigen::MatrixXd Ft = this->f.transpose();
        p = f * p * Ft + q;
    }

    void MeasurementUpdate(const Eigen:: VectorXd&& z){
        Eigen::VectorXd y = z - h * this->x;
        Eigen::MatrixXd S = h * p * h.transpose() + r;
        // Kalman Gain
        Eigen::MatrixXd K = p * h.transpose() * S.inverse();
        // estimate state vector
        x = x + K * y;
        int _sz = this->x.size();
        Eigen::Matrix2Xd I = Eigen::MatrixXd::Identity(_sz, _sz);
        // update state covariance matrix
        p = (I - K * h) * p;
    }

private:
    bool is_initialized; //flag of initialization
    Vxd x;   //state vector
    Vxd f;
    Vxd p;
    Vxd h;
    Vxd u;
    Vxd q;
    Vxd r;

};


}
#endif