cmake_minimum_required(VERSION 2.8.3)
project(ecn_ros2015)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
)

catkin_package(
)


include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(midwa_node src/node.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(midwa_node   ${catkin_LIBRARIES} )
