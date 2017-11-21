# Install script for directory: /home/darling/Desktop/navya_working_copy/src/navya_control

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/darling/Desktop/navya_working_copy/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/navya_control/action" TYPE FILE FILES "/home/darling/Desktop/navya_working_copy/src/navya_control/action/Drive.action")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/navya_control/msg" TYPE FILE FILES
    "/home/darling/Desktop/navya_working_copy/devel/share/navya_control/msg/DriveAction.msg"
    "/home/darling/Desktop/navya_working_copy/devel/share/navya_control/msg/DriveActionGoal.msg"
    "/home/darling/Desktop/navya_working_copy/devel/share/navya_control/msg/DriveActionResult.msg"
    "/home/darling/Desktop/navya_working_copy/devel/share/navya_control/msg/DriveActionFeedback.msg"
    "/home/darling/Desktop/navya_working_copy/devel/share/navya_control/msg/DriveGoal.msg"
    "/home/darling/Desktop/navya_working_copy/devel/share/navya_control/msg/DriveResult.msg"
    "/home/darling/Desktop/navya_working_copy/devel/share/navya_control/msg/DriveFeedback.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/navya_control/cmake" TYPE FILE FILES "/home/darling/Desktop/navya_working_copy/build/navya_control/catkin_generated/installspace/navya_control-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/darling/Desktop/navya_working_copy/devel/include/navya_control")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/darling/Desktop/navya_working_copy/devel/share/roseus/ros/navya_control")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/darling/Desktop/navya_working_copy/devel/share/common-lisp/ros/navya_control")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/darling/Desktop/navya_working_copy/devel/share/gennodejs/ros/navya_control")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/darling/Desktop/navya_working_copy/devel/lib/python2.7/dist-packages/navya_control")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/darling/Desktop/navya_working_copy/devel/lib/python2.7/dist-packages/navya_control")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/darling/Desktop/navya_working_copy/build/navya_control/catkin_generated/installspace/navya_control.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/navya_control/cmake" TYPE FILE FILES "/home/darling/Desktop/navya_working_copy/build/navya_control/catkin_generated/installspace/navya_control-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/navya_control/cmake" TYPE FILE FILES
    "/home/darling/Desktop/navya_working_copy/build/navya_control/catkin_generated/installspace/navya_controlConfig.cmake"
    "/home/darling/Desktop/navya_working_copy/build/navya_control/catkin_generated/installspace/navya_controlConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/navya_control" TYPE FILE FILES "/home/darling/Desktop/navya_working_copy/src/navya_control/package.xml")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/navya_control" TYPE DIRECTORY FILES "/home/darling/Desktop/navya_working_copy/src/navya_control/config")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/navya_control" TYPE DIRECTORY FILES "/home/darling/Desktop/navya_working_copy/src/navya_control/launch")
endif()

