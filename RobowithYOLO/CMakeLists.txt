cmake_minimum_required(VERSION 2.8)
project(RobowithYOLO)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)

find_package(TensorRT REQUIRED)
find_package(OpenCV 4 REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Ceres 2 REQUIRED)
find_package(fmt REQUIRED)

include_directories(
        # /usr/include
        ./include
        ${OpenCV_INCLUDE_DIRS}
	${EIGEN3_INCLUDE_DIR}
	${TensorRT_INCLUDE_DIRS}
	${CERES_INCLUDE_DIRS}
)

add_executable(
        Robo
        src/Robo.cpp
        # include/Preprocess.h    src/Preprocess.cpp
        # include/LightBar.h      src/LightBar.cpp
        # include/Params.h        src/Params.cpp
        # include/Armor.h         src/Armor.cpp
        # include/Perspective.h   src/Perspective.cpp
        src/Preprocess.cpp
        src/LightBar.cpp
        src/Params.cpp
        src/Armor.cpp
        src/Perspective.cpp
	src/TRTModule.cpp
)
target_link_libraries(Robo ${OpenCV_LIBS} ${TensorRT_LIBS} ${TensorRT_SOURCE} ${CERES_LIBRARIES} fmt::fmt nvonnxparser cuda -lMVSDK)
# LINK_LIBRARIES("/lib/libMVSDK.so")
