#include "ros/ros.h"
#include "Serial_Send/Serial_Send.h"
#include <geometry_msgs/Twist.h>



Serial_Send::Serial_Send Serial_Send_Msg;

void Get_Msg(const geometry_msgs::Twist::ConstPtr& Ptr_Msg)
{
    Serial_Send_Msg.vx_set = Ptr_Msg->linear.x;
    Serial_Send_Msg.vy_set = Ptr_Msg->linear.y;
    Serial_Send_Msg.wz_set = Ptr_Msg->angular.z;

    ROS_INFO("------------------------------------------------------------------");
    ROS_INFO("vx_set:%f",Serial_Send_Msg.vx_set);
    ROS_INFO("vy_set:%f",Serial_Send_Msg.vy_set);
    ROS_INFO("wz_set:%f",Serial_Send_Msg.wz_set);
    ROS_INFO("------------------------------------------------------------------");

}

int main(int argc, char *argv[])
{
    
    ros::init(argc,argv,"test");
    ros::NodeHandle nh;
    ros::Subscriber sub_vel = nh.subscribe<geometry_msgs::Twist>("cmd_vel",10,Get_Msg);
    ros::Publisher pub_all = nh.advertise<Serial_Send::Serial_Send>("Serial_Send_Msg",1000);


    ros::Rate r(1);
    while (ros::ok())
    {
        pub_all.publish(Serial_Send_Msg);
        r.sleep();

        ros::spinOnce();
    }

    return 0;
}

