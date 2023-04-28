# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "serial_send: 2 messages, 0 services")

set(MSG_I_FLAGS "-Iserial_send:/home/rmua/roborts_ws/src/serial_send/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(serial_send_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Send.msg" NAME_WE)
add_custom_target(_serial_send_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "serial_send" "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Send.msg" ""
)

get_filename_component(_filename "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Receive.msg" NAME_WE)
add_custom_target(_serial_send_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "serial_send" "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Receive.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(serial_send
  "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Send.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serial_send
)
_generate_msg_cpp(serial_send
  "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Receive.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serial_send
)

### Generating Services

### Generating Module File
_generate_module_cpp(serial_send
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serial_send
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(serial_send_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(serial_send_generate_messages serial_send_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Send.msg" NAME_WE)
add_dependencies(serial_send_generate_messages_cpp _serial_send_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Receive.msg" NAME_WE)
add_dependencies(serial_send_generate_messages_cpp _serial_send_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(serial_send_gencpp)
add_dependencies(serial_send_gencpp serial_send_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS serial_send_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(serial_send
  "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Send.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serial_send
)
_generate_msg_eus(serial_send
  "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Receive.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serial_send
)

### Generating Services

### Generating Module File
_generate_module_eus(serial_send
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serial_send
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(serial_send_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(serial_send_generate_messages serial_send_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Send.msg" NAME_WE)
add_dependencies(serial_send_generate_messages_eus _serial_send_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Receive.msg" NAME_WE)
add_dependencies(serial_send_generate_messages_eus _serial_send_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(serial_send_geneus)
add_dependencies(serial_send_geneus serial_send_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS serial_send_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(serial_send
  "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Send.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serial_send
)
_generate_msg_lisp(serial_send
  "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Receive.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serial_send
)

### Generating Services

### Generating Module File
_generate_module_lisp(serial_send
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serial_send
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(serial_send_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(serial_send_generate_messages serial_send_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Send.msg" NAME_WE)
add_dependencies(serial_send_generate_messages_lisp _serial_send_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Receive.msg" NAME_WE)
add_dependencies(serial_send_generate_messages_lisp _serial_send_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(serial_send_genlisp)
add_dependencies(serial_send_genlisp serial_send_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS serial_send_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(serial_send
  "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Send.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serial_send
)
_generate_msg_nodejs(serial_send
  "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Receive.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serial_send
)

### Generating Services

### Generating Module File
_generate_module_nodejs(serial_send
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serial_send
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(serial_send_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(serial_send_generate_messages serial_send_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Send.msg" NAME_WE)
add_dependencies(serial_send_generate_messages_nodejs _serial_send_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Receive.msg" NAME_WE)
add_dependencies(serial_send_generate_messages_nodejs _serial_send_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(serial_send_gennodejs)
add_dependencies(serial_send_gennodejs serial_send_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS serial_send_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(serial_send
  "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Send.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serial_send
)
_generate_msg_py(serial_send
  "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Receive.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serial_send
)

### Generating Services

### Generating Module File
_generate_module_py(serial_send
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serial_send
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(serial_send_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(serial_send_generate_messages serial_send_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Send.msg" NAME_WE)
add_dependencies(serial_send_generate_messages_py _serial_send_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rmua/roborts_ws/src/serial_send/msg/Serial_Receive.msg" NAME_WE)
add_dependencies(serial_send_generate_messages_py _serial_send_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(serial_send_genpy)
add_dependencies(serial_send_genpy serial_send_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS serial_send_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serial_send)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/serial_send
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(serial_send_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serial_send)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/serial_send
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(serial_send_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serial_send)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/serial_send
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(serial_send_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serial_send)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/serial_send
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(serial_send_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serial_send)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serial_send\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/serial_send
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(serial_send_generate_messages_py std_msgs_generate_messages_py)
endif()
