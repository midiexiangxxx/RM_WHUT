#!/usr/bin/python
# -*- coding: UTF-8 -*-
#! /usr/bin/env python

#1.导包 
import rospy
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Pose, Point, Quaternion, Twist
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from actionlib_msgs.msg import GoalStatus
import actionlib
import time
# min_distance = 0.4
min_distance = 0.45 #方案二
# 目标点1 
# target1 = Pose(Point(0,  0, 0.000), Quaternion(0.000, 0.000,   -0.711122731824, 0.70306789166))
# 方案二目标点
target1 = Pose(Point(2.85,  -0.68, 0.000), Quaternion(0.000, 0.000,   -0.711122731824, 0.70306789166))#true
target2 = Pose(Point(2.85,  -0.68, 0.000), Quaternion(0.000, 0.000,   -0.711122731824, 0.70306789166))#true
# target1 = Pose(Point(1,  0, 0.000), Quaternion(0.000, 0.000,   -0.711122731824, 0.70306789166))
# 目标点2
# target2 = Pose(Point(0,  0, 0.000), Quaternion(0.000, 0.000,   -0.711122731824, 0.70306789166))
# target2 = Pose(Point(0.68,  -2.85, 0.000), Quaternion(0.000, 0.000,   -0.711122731824, 0.70306789166))
# target2 = Pose(Point(2.85,  -0.68, 0.000), Quaternion(0.000, 0.000,   -0.711122731824, 0.70306789166))
# 旋转速度
move_cmd = Twist()
move_cmd.angular.z = 1000
# move_cmd.angular.z = 0.5
shoot = 0
def get_shoot(shoot_data):
    global shoot
    shoot = shoot_data.linear.z
def scan_sub(scan_data):
    global min_distance, move_cmd
    # scan_length = len(scan_data.ranges)
    # scan_min = min(scan_data.ranges)
    # rospy.loginfo("scan_min:%f",min(scan_data.ranges))
    # scan_min_index = scan_data.ranges.index(min(scan_data.ranges))
    # rospy.loginfo("scan_min_index:%d",scan_min_index)
    # rospy.loginfo("scan_min:%f",scan_min)
    # if(shoot == 0):
    scan_min = scan_data.ranges[300]
    pub.publish(move_cmd)
    if scan_min < min_distance:
        rospy.loginfo("Starting position2 navigation ")
        send_goal2()
        finished_within_time = move_base.wait_for_result(rospy.Duration(10))
        if not finished_within_time:
                move_base.cancel_goal()
                rospy.logerr("ERROR:Timed out achieving goal")
        else:
            state = move_base.get_state()
            if state == GoalStatus.SUCCEEDED:
                rospy.loginfo("Goal succeeded!")
def send_goal1():
    # Set up the next goal location
    goal = MoveBaseGoal()
    goal.target_pose.pose = target1
    goal.target_pose.header.frame_id = 'map'
    goal.target_pose.header.stamp = rospy.Time.now()
    move_base.send_goal(goal) #send goal to move_base      
        
def send_goal2():
    # Set up the next goal location
    goal = MoveBaseGoal()
    goal.target_pose.pose = target2
    goal.target_pose.header.frame_id = 'map'
    goal.target_pose.header.stamp = rospy.Time.now()
    move_base.send_goal(goal) #send goal to move_base
if __name__ == "__main__":
    #2.初始化 ROS 节点:命名(唯一)
    rospy.init_node("scan_min_pub")
    #3.实例化 订阅者 对象
    move_base = actionlib.SimpleActionClient("move_base", MoveBaseAction)
    rospy.loginfo("Connected to move base server")
    
    # 游戏开始，跳出循环
    while(rospy.get_param("game_start") == False):
        rospy.loginfo("game not start")
    rospy.loginfo("-------------------------------------")
    rospy.loginfo("wait for 5s")
    time.sleep(5)
    # 方案二等待英雄步兵出来
    move_base.wait_for_server(rospy.Duration(10))
    rospy.loginfo("Starting position1 navigation ")
    send_goal1()
    finished_within_time = move_base.wait_for_result(rospy.Duration(30))
    if not finished_within_time:
            move_base.cancel_goal()
            rospy.logerr("ERROR:Timed out achieving goal")
            send_goal1()
            rospy.logerr("resend!")
    else:
        state = move_base.get_state()
        if state == GoalStatus.SUCCEEDED:
            rospy.loginfo("Goal succeeded!")
    
    sub = rospy.Subscriber("scan",LaserScan,scan_sub,queue_size=10)
    pub = rospy.Publisher("cmd_vel",Twist,queue_size=10)
    sub_shoot = rospy.Subscriber("shooter",Twist,get_shoot,queue_size=10)
    
    #4.处理订阅的消息(回调函数)
    #5.设置循环调用回调函数
    rospy.spin()
