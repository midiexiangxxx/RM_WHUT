cmake_minimum_required(VERSION 3.1)
project(ROBO7)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig)
find_package(OpenCV REQUIRED)

pkg_search_module(SERIAL REQUIRED libserial)
include_directories(${SERIAL_INCLUDE_DIRS})
link_directories(${SERIAL_LIBRARY_DIRS})


message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


add_executable(ROBO7 src/main.cpp include include/Entities.h include/Detector.h include/Perspective.h include/Filter.h
        include/Params.h include/Tracker.h include/stop_watch.hpp include/uart.hpp)


target_link_libraries(ROBO7 PRIVATE ${SERIAL_LIBRARIES})
target_link_libraries(ROBO7 PRIVATE ${OpenCV_LIBS} /lib/libMVSDK.so -lpthread )
