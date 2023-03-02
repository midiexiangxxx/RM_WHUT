#include "ros/ros.h"
#include <geometry_msgs/Twist.h>

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"move");
    ros::NodeHandle nh;
	ros::Publisher pub_vel = nh.advertise<geometry_msgs::Twist>("cmd_vel",10);

	geometry_msgs::Twist twist;

	twist.linear.x = 0.0;
	twist.linear.y = 0.0;
	twist.linear.z = 0.0;
	twist.angular.x = 0.0;
	twist.angular.y = 0.0;
	twist.angular.z = 0.0;
	pub_vel.publish(twist);
	ROS_INFO("stop");
	ros::Duration(3).sleep();

	twist.linear.x = 0.2;
	twist.linear.y = 0.0;
	twist.linear.z = 0.0;
	twist.angular.x = 0.0;
	twist.angular.y = 0.0;
	twist.angular.z = 0.0;
	pub_vel.publish(twist);
	ROS_INFO("forward");
	ros::Duration(3).sleep();
	
	twist.linear.x = -0.2;
	twist.linear.y = 0.0;
	twist.linear.z = 0.0;
	twist.angular.x = 0.0;
	twist.angular.y = 0.0;
	twist.angular.z = 0.0;
	pub_vel.publish(twist);
	ROS_INFO("backward");
	ros::Duration(3).sleep();

	twist.linear.x = 0.0;
	twist.linear.y = 0.2;
	twist.linear.z = 0.0;
	twist.angular.x = 0.0;
	twist.angular.y = 0.0;
	twist.angular.z = 0.0;
	pub_vel.publish(twist);
	ROS_INFO("right");
	ros::Duration(3).sleep();

	twist.linear.x = 0.0;
	twist.linear.y = -0.2;
	twist.linear.z = 0.0;
	twist.angular.x = 0.0;
	twist.angular.y = 0.0;
	twist.angular.z = 0.0;
	pub_vel.publish(twist);
	ROS_INFO("left");
	ros::Duration(3).sleep();

	twist.linear.x = 0.0;
	twist.linear.y = 0.0;
	twist.linear.z = 0.0;
	twist.angular.x = 0.0;
	twist.angular.y = 0.0;
	twist.angular.z = 0.5;
	pub_vel.publish(twist);
	ROS_INFO("Rotate");
	ros::Duration(3).sleep();
	
	twist.linear.x = 0.0;
	twist.linear.y = 0.2;
	twist.linear.z = 0.0;
	twist.angular.x = 0.0;
	twist.angular.y = 0.0;
	twist.angular.z = -0.5;
	pub_vel.publish(twist);
	ROS_INFO("Reverse");
	ros::Duration(3).sleep();

	twist.linear.x = 0.0;
	twist.linear.y = 0.0;
	twist.linear.z = 0.0;
	twist.angular.x = 0.0;
	twist.angular.y = 0.0;
	twist.angular.z = 0.0;
	pub_vel.publish(twist);
	ROS_INFO("stop");
	ros::Duration(3).sleep();

    return 0;
}

