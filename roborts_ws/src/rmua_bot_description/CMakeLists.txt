cmake_minimum_required(VERSION 3.0.2)
project(rmua_bot_description)

#project(nexus_4wd_mecanum_gazebo)
find_package(catkin REQUIRED COMPONENTS
  robot_state_publisher
 ## rviz
  urdf
  controller_manager
  joint_state_controller
  geometry_msgs
  #gazebo-dev
  nav_msgs
  roscpp
  std_msgs
  std_srvs
  tf
  message_generation
)
include_directories(
# include
 ${catkin_INCLUDE_DIRS}
)
MESSAGE(STATUS "-super-----------------------------catkin_INCLUDE_DIRS" ${catkin_INCLUDE_DIRS})
## Find gazebo
find_package(gazebo REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
## Find Boost
find_package(Boost REQUIRED COMPONENTS thread)
include_directories(${Boost_INCLUDE_DIRS})
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES nexus_4wd_mecanum_description
  CATKIN_DEPENDS robot_state_publisher controller_manager joint_state_controller urdf
  roscpp std_msgs geometry_msgs nav_msgs tf message_runtime
  INCLUDE_DIRS include
  LIBRARIES
#  DEPENDS system_lib
)

#find_package(roslaunch)


###########
## Build ##
###########
#add_library(nexus_ros_force_based_move src/nexus_ros_force_based_move.cpp)
#MESSAGE(STATUS "-super------------------------------catkin_LIBRARIES" ${catkin_LIBRARIES})

#target_link_libraries(nexus_ros_force_based_move ${Boost_LIBRARIES} ${GAZEBO_LIBRARIES} ${catkin_LIBRARIES})

#install(DIRECTORY include/${PROJECT_NAME}/
 # DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
 # FILES_MATCHING PATTERN "*.h"
 # PATTERN ".svn" EXCLUDE
#)
#############
## Install ##
#############
#install(TARGETS
#  nexus_ros_force_based_move
#  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#)

