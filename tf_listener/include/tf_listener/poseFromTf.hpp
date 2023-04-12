#ifndef POSE_FROM_TF_HPP
#define POSE_FROM_TF_HPP

#include <string>
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <unistd.h>
#include <math.h>

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

  tf::TransformListener listener;
  tf::StampedTransform transform;

  double dx, dy, dz, r, p, y;

  void(*readyCallback)(double dx, double dy, double dz, double r, double p, double y);
};
#endif 
