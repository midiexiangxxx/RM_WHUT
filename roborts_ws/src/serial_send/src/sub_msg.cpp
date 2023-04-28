#include "ros/ros.h"
#include "serial/serial.h"
#include "Serial_Send/Serial_Send.h"
#include "Serial_Send/Serial_Receive.h"
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
Serial_Send::Serial_Receive Serial_Receive_Msg;

  double vx = 0;
  double vy = 0;
  double vth = 0;
  int num = 0;


void Get_Msg(const Serial_Send::Serial_Receive::ConstPtr& P)
{
  if (num % 100 == 0)
  {
    ROS_INFO("------------------------------------------------------------------");
    ROS_INFO("vx_set:%f",P->vx);
    ROS_INFO("vy_set:%f",P->vy);
    ROS_INFO("wz_set:%f",P->wz);
    ROS_INFO("------------------------------------------------------------------");
  }
  vx=P->vx;
  vy=P->vy;
  vth=P->wz;
  num++;
  // if((num > 10) && (num <= 100))
  // {
  //   odom_err += vth;
  //   if(num == 100)
  //   {
  //     odom_err = odom_err / 90;
  //   }
  // }
}

int main(int argc, char** argv){
  ros::init(argc, argv, "odometry_publisher");

  ros::NodeHandle nh;
  ros::Publisher odom_pub = nh.advertise<nav_msgs::Odometry>("odom", 50);
  ros::Subscriber sub_vell = nh.subscribe<Serial_Send::Serial_Receive>("Serial_Receive",1000,Get_Msg);
  tf::TransformBroadcaster odom_broadcaster;
 
  //ros::spin();
  double x = 0.0;
  double y = 0.0;
  double th = 0.0;



  ros::Time current_time, last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();

  ros::Rate r(50);
  while(nh.ok()){

    ros::spinOnce();               // check for incoming messages
    current_time = ros::Time::now();

    //compute odometry in a typical way given the velocities of the robot
    double dt = (current_time - last_time).toSec();
    double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
    double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
    double delta_th = vth * dt;

    x += delta_x;
    y += delta_y;
    th += delta_th;

    //since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    odom_broadcaster.sendTransform(odom_trans);

    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    //set the position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //set the velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = vx;
    odom.twist.twist.linear.y = vy;
    odom.twist.twist.angular.z = vth ;



    //publish the message

    
    odom_pub.publish(odom);

    last_time = current_time;
    r.sleep();
  }
}

/*
#include "ros/ros.h"
#include "serial/serial.h"
#include "Serial_Send/Serial_Send.h"
#include "Serial_Send/Serial_Receive.h"
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>


using namespace std;


Serial_Send::Serial_Receive Serial_Receive_Msg;

void Get_Msg(const Serial_Send::Serial_Receive::ConstPtr& P)
{
    ROS_INFO("------------------------------------------------------------------");
    ROS_INFO("vx_set:%f",P->vx);
    ROS_INFO("vy_set:%f",P->vy);
    ROS_INFO("wz_set:%f",P->wz);
    ROS_INFO("------------------------------------------------------------------");

}

int main(int argc, char *argv[])
{
    
    ros::init(argc,argv,"rodometry_publishere");
    ros::NodeHandle nh;
    ros::Subscriber sub_vell = nh.subscribe<Serial_Send::Serial_Receive>("Serial_Receive_Msg",1000,Get_Msg);
    ros::spin();


    return 0;
}

*/

