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
CMAKE_SOURCE_DIR = /home/rmua/roborts_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rmua/roborts_ws/build

# Utility rule file for serial_send_generate_messages_cpp.

# Include any custom commands dependencies for this target.
include serial_send/CMakeFiles/serial_send_generate_messages_cpp.dir/compiler_depend.make

# Include the progress variables for this target.
include serial_send/CMakeFiles/serial_send_generate_messages_cpp.dir/progress.make

serial_send/CMakeFiles/serial_send_generate_messages_cpp: /home/rmua/roborts_ws/devel/include/serial_send/Serial_Send.h
serial_send/CMakeFiles/serial_send_generate_messages_cpp: /home/rmua/roborts_ws/devel/include/serial_send/Serial_Receive.h

/home/rmua/roborts_ws/devel/include/serial_send/Serial_Receive.h: /opt/ros/melodic/lib/gencpp/gen_cpp.py
/home/rmua/roborts_ws/devel/include/serial_send/Serial_Receive.h: /home/rmua/roborts_ws/src/serial_send/msg/Serial_Receive.msg
/home/rmua/roborts_ws/devel/include/serial_send/Serial_Receive.h: /opt/ros/melodic/share/gencpp/msg.h.template
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/rmua/roborts_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating C++ code from serial_send/Serial_Receive.msg"
	cd /home/rmua/roborts_ws/src/serial_send && /home/rmua/roborts_ws/build/catkin_generated/env_cached.sh /usr/bin/python2 /opt/ros/melodic/share/gencpp/cmake/../../../lib/gencpp/gen_cpp.py /home/rmua/roborts_ws/src/serial_send/msg/Serial_Receive.msg -Iserial_send:/home/rmua/roborts_ws/src/serial_send/msg -Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg -p serial_send -o /home/rmua/roborts_ws/devel/include/serial_send -e /opt/ros/melodic/share/gencpp/cmake/..

/home/rmua/roborts_ws/devel/include/serial_send/Serial_Send.h: /opt/ros/melodic/lib/gencpp/gen_cpp.py
/home/rmua/roborts_ws/devel/include/serial_send/Serial_Send.h: /home/rmua/roborts_ws/src/serial_send/msg/Serial_Send.msg
/home/rmua/roborts_ws/devel/include/serial_send/Serial_Send.h: /opt/ros/melodic/share/gencpp/msg.h.template
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/rmua/roborts_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating C++ code from serial_send/Serial_Send.msg"
	cd /home/rmua/roborts_ws/src/serial_send && /home/rmua/roborts_ws/build/catkin_generated/env_cached.sh /usr/bin/python2 /opt/ros/melodic/share/gencpp/cmake/../../../lib/gencpp/gen_cpp.py /home/rmua/roborts_ws/src/serial_send/msg/Serial_Send.msg -Iserial_send:/home/rmua/roborts_ws/src/serial_send/msg -Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg -p serial_send -o /home/rmua/roborts_ws/devel/include/serial_send -e /opt/ros/melodic/share/gencpp/cmake/..

serial_send_generate_messages_cpp: serial_send/CMakeFiles/serial_send_generate_messages_cpp
serial_send_generate_messages_cpp: /home/rmua/roborts_ws/devel/include/serial_send/Serial_Receive.h
serial_send_generate_messages_cpp: /home/rmua/roborts_ws/devel/include/serial_send/Serial_Send.h
serial_send_generate_messages_cpp: serial_send/CMakeFiles/serial_send_generate_messages_cpp.dir/build.make
.PHONY : serial_send_generate_messages_cpp

# Rule to build all files generated by this target.
serial_send/CMakeFiles/serial_send_generate_messages_cpp.dir/build: serial_send_generate_messages_cpp
.PHONY : serial_send/CMakeFiles/serial_send_generate_messages_cpp.dir/build

serial_send/CMakeFiles/serial_send_generate_messages_cpp.dir/clean:
	cd /home/rmua/roborts_ws/build/serial_send && $(CMAKE_COMMAND) -P CMakeFiles/serial_send_generate_messages_cpp.dir/cmake_clean.cmake
.PHONY : serial_send/CMakeFiles/serial_send_generate_messages_cpp.dir/clean

serial_send/CMakeFiles/serial_send_generate_messages_cpp.dir/depend:
	cd /home/rmua/roborts_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rmua/roborts_ws/src /home/rmua/roborts_ws/src/serial_send /home/rmua/roborts_ws/build /home/rmua/roborts_ws/build/serial_send /home/rmua/roborts_ws/build/serial_send/CMakeFiles/serial_send_generate_messages_cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : serial_send/CMakeFiles/serial_send_generate_messages_cpp.dir/depend

