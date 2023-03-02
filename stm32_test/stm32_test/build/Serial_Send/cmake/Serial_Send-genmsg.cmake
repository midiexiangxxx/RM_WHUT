# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "Serial_Send: 2 messages, 0 services")

set(MSG_I_FLAGS "-ISerial_Send:/home/rmua/stm32_test/src/Serial_Send/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(Serial_Send_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Receive.msg" NAME_WE)
add_custom_target(_Serial_Send_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "Serial_Send" "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Receive.msg" ""
)

get_filename_component(_filename "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Send.msg" NAME_WE)
add_custom_target(_Serial_Send_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "Serial_Send" "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Send.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(Serial_Send
  "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Receive.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Serial_Send
)
_generate_msg_cpp(Serial_Send
  "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Send.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Serial_Send
)

### Generating Services

### Generating Module File
_generate_module_cpp(Serial_Send
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Serial_Send
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(Serial_Send_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(Serial_Send_generate_messages Serial_Send_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Receive.msg" NAME_WE)
add_dependencies(Serial_Send_generate_messages_cpp _Serial_Send_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Send.msg" NAME_WE)
add_dependencies(Serial_Send_generate_messages_cpp _Serial_Send_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Serial_Send_gencpp)
add_dependencies(Serial_Send_gencpp Serial_Send_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Serial_Send_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(Serial_Send
  "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Receive.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Serial_Send
)
_generate_msg_eus(Serial_Send
  "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Send.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Serial_Send
)

### Generating Services

### Generating Module File
_generate_module_eus(Serial_Send
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Serial_Send
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(Serial_Send_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(Serial_Send_generate_messages Serial_Send_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Receive.msg" NAME_WE)
add_dependencies(Serial_Send_generate_messages_eus _Serial_Send_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Send.msg" NAME_WE)
add_dependencies(Serial_Send_generate_messages_eus _Serial_Send_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Serial_Send_geneus)
add_dependencies(Serial_Send_geneus Serial_Send_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Serial_Send_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(Serial_Send
  "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Receive.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Serial_Send
)
_generate_msg_lisp(Serial_Send
  "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Send.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Serial_Send
)

### Generating Services

### Generating Module File
_generate_module_lisp(Serial_Send
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Serial_Send
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(Serial_Send_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(Serial_Send_generate_messages Serial_Send_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Receive.msg" NAME_WE)
add_dependencies(Serial_Send_generate_messages_lisp _Serial_Send_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Send.msg" NAME_WE)
add_dependencies(Serial_Send_generate_messages_lisp _Serial_Send_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Serial_Send_genlisp)
add_dependencies(Serial_Send_genlisp Serial_Send_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Serial_Send_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(Serial_Send
  "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Receive.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Serial_Send
)
_generate_msg_nodejs(Serial_Send
  "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Send.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Serial_Send
)

### Generating Services

### Generating Module File
_generate_module_nodejs(Serial_Send
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Serial_Send
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(Serial_Send_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(Serial_Send_generate_messages Serial_Send_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Receive.msg" NAME_WE)
add_dependencies(Serial_Send_generate_messages_nodejs _Serial_Send_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Send.msg" NAME_WE)
add_dependencies(Serial_Send_generate_messages_nodejs _Serial_Send_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Serial_Send_gennodejs)
add_dependencies(Serial_Send_gennodejs Serial_Send_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Serial_Send_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(Serial_Send
  "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Receive.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Serial_Send
)
_generate_msg_py(Serial_Send
  "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Send.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Serial_Send
)

### Generating Services

### Generating Module File
_generate_module_py(Serial_Send
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Serial_Send
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(Serial_Send_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(Serial_Send_generate_messages Serial_Send_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Receive.msg" NAME_WE)
add_dependencies(Serial_Send_generate_messages_py _Serial_Send_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rmua/stm32_test/src/Serial_Send/msg/Serial_Send.msg" NAME_WE)
add_dependencies(Serial_Send_generate_messages_py _Serial_Send_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Serial_Send_genpy)
add_dependencies(Serial_Send_genpy Serial_Send_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Serial_Send_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Serial_Send)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Serial_Send
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(Serial_Send_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Serial_Send)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Serial_Send
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(Serial_Send_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Serial_Send)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Serial_Send
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(Serial_Send_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Serial_Send)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Serial_Send
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(Serial_Send_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Serial_Send)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Serial_Send\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Serial_Send
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(Serial_Send_generate_messages_py std_msgs_generate_messages_py)
endif()
