# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/rmua/Applications/rmuas/cmake-3.26.0-linux-aarch64/bin/cmake

# The command to remove a file.
RM = /home/rmua/Applications/rmuas/cmake-3.26.0-linux-aarch64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rmua/Documents/ROBO7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rmua/Documents/ROBO7/build

# Include any dependencies generated for this target.
include CMakeFiles/ROBO7.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ROBO7.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ROBO7.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ROBO7.dir/flags.make

CMakeFiles/ROBO7.dir/src/main.cpp.o: CMakeFiles/ROBO7.dir/flags.make
CMakeFiles/ROBO7.dir/src/main.cpp.o: /home/rmua/Documents/ROBO7/src/main.cpp
CMakeFiles/ROBO7.dir/src/main.cpp.o: CMakeFiles/ROBO7.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rmua/Documents/ROBO7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ROBO7.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ROBO7.dir/src/main.cpp.o -MF CMakeFiles/ROBO7.dir/src/main.cpp.o.d -o CMakeFiles/ROBO7.dir/src/main.cpp.o -c /home/rmua/Documents/ROBO7/src/main.cpp

CMakeFiles/ROBO7.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ROBO7.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rmua/Documents/ROBO7/src/main.cpp > CMakeFiles/ROBO7.dir/src/main.cpp.i

CMakeFiles/ROBO7.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ROBO7.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rmua/Documents/ROBO7/src/main.cpp -o CMakeFiles/ROBO7.dir/src/main.cpp.s

# Object files for target ROBO7
ROBO7_OBJECTS = \
"CMakeFiles/ROBO7.dir/src/main.cpp.o"

# External object files for target ROBO7
ROBO7_EXTERNAL_OBJECTS =

ROBO7: CMakeFiles/ROBO7.dir/src/main.cpp.o
ROBO7: CMakeFiles/ROBO7.dir/build.make
ROBO7: /usr/lib/aarch64-linux-gnu/libopencv_dnn.so.4.1.1
ROBO7: /usr/lib/aarch64-linux-gnu/libopencv_gapi.so.4.1.1
ROBO7: /usr/lib/aarch64-linux-gnu/libopencv_highgui.so.4.1.1
ROBO7: /usr/lib/aarch64-linux-gnu/libopencv_ml.so.4.1.1
ROBO7: /usr/lib/aarch64-linux-gnu/libopencv_objdetect.so.4.1.1
ROBO7: /usr/lib/aarch64-linux-gnu/libopencv_photo.so.4.1.1
ROBO7: /usr/lib/aarch64-linux-gnu/libopencv_stitching.so.4.1.1
ROBO7: /usr/lib/aarch64-linux-gnu/libopencv_video.so.4.1.1
ROBO7: /usr/lib/aarch64-linux-gnu/libopencv_videoio.so.4.1.1
ROBO7: /lib/libMVSDK.so
ROBO7: /usr/lib/aarch64-linux-gnu/libopencv_imgcodecs.so.4.1.1
ROBO7: /usr/lib/aarch64-linux-gnu/libopencv_calib3d.so.4.1.1
ROBO7: /usr/lib/aarch64-linux-gnu/libopencv_features2d.so.4.1.1
ROBO7: /usr/lib/aarch64-linux-gnu/libopencv_flann.so.4.1.1
ROBO7: /usr/lib/aarch64-linux-gnu/libopencv_imgproc.so.4.1.1
ROBO7: /usr/lib/aarch64-linux-gnu/libopencv_core.so.4.1.1
ROBO7: CMakeFiles/ROBO7.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rmua/Documents/ROBO7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ROBO7"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ROBO7.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ROBO7.dir/build: ROBO7
.PHONY : CMakeFiles/ROBO7.dir/build

CMakeFiles/ROBO7.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ROBO7.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ROBO7.dir/clean

CMakeFiles/ROBO7.dir/depend:
	cd /home/rmua/Documents/ROBO7/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rmua/Documents/ROBO7 /home/rmua/Documents/ROBO7 /home/rmua/Documents/ROBO7/build /home/rmua/Documents/ROBO7/build /home/rmua/Documents/ROBO7/build/CMakeFiles/ROBO7.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ROBO7.dir/depend

