cmake_minimum_required(VERSION 2.8.3)
project(navya_control)



#find_package(catkin REQUIRED genmsg actionlib_msgs actionlib)
find_package(catkin REQUIRED 
COMPONENTS
  controller_manager
  joint_state_controller
  robot_state_publisher
  roscpp
  actionlib_msgs
  move_base_msgs
  actionlib
  std_msgs
)
include_directories(${catkin_INCLUDE_DIRS})

find_package(catkin REQUIRED genmsg actionlib_msgs actionlib)
add_action_files(DIRECTORY action FILES Drive.action)
generate_messages(DEPENDENCIES actionlib_msgs)

catkin_package()

install(DIRECTORY config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
  
  
  find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")
  


add_library(NavyaDriver SHARED busdriver.cpp)
target_link_libraries(NavyaDriver ${GAZEBO_libraries})

add_library(bus_driver SHARED navyabusdriver.cc)

target_link_libraries(bus_driver ${GAZEBO_LIBRARIES})

add_library(vehicle_driver SHARED move_base_server.cpp)

target_link_libraries(vehicle_driver ${GAZEBO_LIBRARIES})

# Build the stand-alone test program
add_executable(driveit driveit.cc)

if (${gazebo_VERSION_MAJOR} LESS 6)
  # These two
  include(FindBoost)
  find_package(Boost ${MIN_BOOST_VERSION} REQUIRED system filesystem regex)
  target_link_libraries(driveit ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})
else()
  target_link_libraries(driveit ${GAZEBO_LIBRARIES})
endif()

add_executable(simple_navigation_goals move_base.cc)
target_link_libraries(simple_navigation_goals ${catkin_LIBRARIES})
