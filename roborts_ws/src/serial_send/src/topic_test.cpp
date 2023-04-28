#include "ros/ros.h"
#include "serial_send/Serial_Send.h"
#include <geometry_msgs/Twist.h>

static int count = 0;

serial_send::Serial_Send Serial_Send_Msg;

void Get_Shot(const geometry_msgs::Twist::ConstPtr& Ptr_Msg)
{
    Serial_Send_Msg.yaw_add = Ptr_Msg->linear.x;
    Serial_Send_Msg.pitch_add = Ptr_Msg->linear.y;
    count++;
    if(count >= 5)
    {
	count = 0;
	Serial_Send_Msg.mode = 0x81;
    }
}
void Get_Msg(const geometry_msgs::Twist::ConstPtr& Ptr_Msg)
{
    Serial_Send_Msg.vx_set = Ptr_Msg->linear.x;
    Serial_Send_Msg.vy_set = Ptr_Msg->linear.y;
    Serial_Send_Msg.wz_set = Ptr_Msg->angular.z;
    
    Serial_Send_Msg.mode |= 0x00;
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
    ros::Publisher pub_all = nh.advertise<serial_send::Serial_Send>("Serial_Send_Msg",1000);
    ros::Subscriber sub_shot = nh.subscribe<geometry_msgs::Twist>("shooter",100,Get_Shot);


    ros::Rate r(50);
    while (ros::ok())
    {
        pub_all.publish(Serial_Send_Msg);
	    Serial_Send_Msg.mode = 0x00;
        r.sleep();

        ros::spinOnce();
    }

    return 0;
}

