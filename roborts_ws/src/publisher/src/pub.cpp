#include "ros/ros.h"
#include "Serial_Send/Serial_Send.h"


void Get_Msg(const Serial_Send::Serial_Send::ConstPtr& Ptr_Msg)
{

    Serial_Send_Msg.gimbal_x = Ptr_Msg->gimbal_x;
    Serial_Send_Msg.gimbal_y = Ptr_Msg->gimbal_y;
    Serial_Send_Msg.gimbal_z = Ptr_Msg->gimbal_z;
    Serial_Send_Msg.vx_set = Ptr_Msg->vx_set;
    Serial_Send_Msg.vy_set = Ptr_Msg->vy_set;
    Serial_Send_Msg.wz_set = Ptr_Msg->wz_set;
    Serial_Send_Msg.vx_set = Ptr_Msg->Li
    Msg_To_Data();
    ser.write(Serial_Send_Data);
    ROS_INFO("------------------------------------------------------------------");
    ROS_INFO("gimbal_x:%f",Serial_Send_Msg.gimbal_x);
    ROS_INFO("gimbal_y:%f",Serial_Send_Msg.gimbal_y);
    ROS_INFO("gimbal_z:%f",Serial_Send_Msg.gimbal_z);
    ROS_INFO("vx_set:%f",Serial_Send_Msg.vx_set);
    ROS_INFO("vy_set:%f",Serial_Send_Msg.vy_set);
    ROS_INFO("wz_set:%f",Serial_Send_Msg.wz_set);
}


int main(int argc, char *argv[])
{
    ros::init(argc,argv,"message_pub");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<Serial_Send::Serial_Send>("Serial_Send_Msg",1000);
    ros::Subscriber sub_vel = nh.subscribe<geometry::Twist>("cmd_vel",10,Get_Msg);
    Serial_Send::Serial_Send Serial_Send_Msg;

    Serial_Send_Msg.vx_set = 0.2555;

    ros::Rate r(1);
    while (ros::ok())
    {
        pub.publish(Serial_Send_Msg);
        r.sleep();
        ros::spinOnce();
    }

    return 0;
}

