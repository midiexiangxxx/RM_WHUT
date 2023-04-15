cmake_minimum_required(VERSION 2.8)
project(RobowithYOLO)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)

option(LINK_SHARED_ZED "Link with the ZED SDK shared executable" ON)


find_package(TensorRT REQUIRED)
find_package(ZED 3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Ceres 2 REQUIRED)
find_package(fmt REQUIRED)
find_package(CUDA ${ZED_CUDA_VERSION} REQUIRED)

include_directories(
        # /usr/include
        ./include
        ${OpenCV_INCLUDE_DIRS}
	${EIGEN3_INCLUDE_DIR}
	${TensorRT_INCLUDE_DIRS}
	${CERES_INCLUDE_DIRS}
)
include_directories(${CUDA_INCLUDE_DIRS})
include_directories(${ZED_INCLUDE_DIRS})


link_directories(${ZED_LIBRARY_DIR})

if (LINK_SHARED_ZED)
    SET(ZED_LIBS ${ZED_LIBRARIES} ${CUDA_CUDA_LIBRARY} ${CUDA_CUDART_LIBRARY})
else()
    SET(ZED_LIBS ${ZED_STATIC_LIBRARIES} ${CUDA_CUDA_LIBRARY} ${CUDA_LIBRARY})
endif()

add_executable(
        Robo
        src/Robo.cpp
        src/Preprocess.cpp
        src/LightBar.cpp
        src/Params.cpp
        src/Armor.cpp
        src/Perspective.cpp
	src/TRTModule.cpp
)
target_link_libraries(Robo ${OpenCV_LIBS} ${ZED_LIBS} ${TensorRT_LIBS} ${TensorRT_SOURCE} ${CERES_LIBRARIES} fmt::fmt nvonnxparser cuda )

