cmake_minimum_required(VERSION 2.8)
project(Robo)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(
        # /usr/include
        ./include
        ${OpenCV_INCLUDE_DIRS}
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
)

target_link_libraries(Robo ${OpenCV_LIBS} -lMVSDK)
# LINK_LIBRARIES("/lib/libMVSDK.so")
