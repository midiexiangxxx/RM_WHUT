#include<ros/ros.h>
#include<tf/transform_broadcaster.h>
#include<nav_msgs/Odometry.h>
#include<geometry_msgs/Twist.h>
#include<iostream>
 
void callback(const geometry_msgs::Twist& cmd_vel)
{
	ROS_INFO("Received a /cmd_vel message!");
	ROS_INFO("Linear Components:[%f,%f,%f]",cmd_vel.linear.x,cmd_vel.linear.y,cmd_vel.linear.z);
	ROS_INFO("Angular Components:[%f,%f,%f]",cmd_vel.angular.x,cmd_vel.angular.y,cmd_vel.angular.z);
	// Do velocity processing here:  
    // Use the kinematics of your robot to map linear and angular velocities into motor commands  
//    v_l = ...  
//    v_r = ...  
  
    // Then set your wheel speeds (using wheel_left and wheel_right as examples)  
//    wheel_left.set_speed(v_l)  
//    wheel_right.set_speed(v_r) 
}
 
int main(int argc, char** argv)
{
	ros::init(argc, argv, "cmd_vel_listener");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("cmd_vel", 1000, callback);    //订阅cmd_vel话题
	ros::spin();
 

	return 1;
}
