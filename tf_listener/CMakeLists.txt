cmake_minimum_required(VERSION 3.8)

project(tf_listener)

add_definitions(-std=c++17 -g)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)

include_directories(
  include
)

add_library(tf_listener src/poseFromTf.cpp)
ament_export_targets(tf_listener HAS_LIBRARY_TARGET)

ament_target_dependencies(tf_listener
    rclcpp
    std_msgs
    geometry_msgs
    tf2
    tf2_ros
)

install(
    DIRECTORY include/tf_listener
    DESTINATION include
)

install(
   TARGETS tf_listener
   EXPORT tf_listener
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
   RUNTIME DESTINATION lib
   INCLUDES DESTINATION include
)

ament_package()
