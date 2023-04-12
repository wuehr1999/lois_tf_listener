#ifndef POSE_FROM_TF_HPP
#define POSE_FROM_TF_HPP

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include <string>
#include <unistd.h>
#include <math.h>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <tf2/exceptions.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>

class PoseLookup
{
public:
  PoseLookup(void(*readyCallback)(double dx, double dy, double dz, double r, double p, double y), 
             std::string parent = "base_link", std::string child = "road_frame");
  ~PoseLookup(){};

  void waitForIt(int timeout_sec = 3);
  void getData(double* dx, double* dy, double* dz, double* r, double* p, double* y);

private:

  std::string parent, child;

  std::shared_ptr<tf2_ros::Buffer> buffer;
  std::shared_ptr<tf2_ros::TransformListener> listener;
  geometry_msgs::msg::TransformStamped transform;

  double dx, dy, dz, r, p, y;

  void(*readyCallback)(double dx, double dy, double dz, double r, double p, double y);
};
#endif 
