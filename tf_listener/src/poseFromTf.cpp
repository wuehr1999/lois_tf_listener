#include <tf_listener/poseFromTf.hpp>

PoseLookup::PoseLookup(rclcpp::Node* node, void (*readyCallback)(double dx, double dy, double dz,
                                             double r, double p, double y),
                       std::string parent, std::string child) {
        this->node = node;
        buffer = std::make_unique<tf2_ros::Buffer>(node->get_clock());
        listener = std::make_shared<tf2_ros::TransformListener>(*buffer);
        this->readyCallback = readyCallback;
        this->parent = parent;
        this->child = child;
}

void PoseLookup::waitForIt(int timeout_sec)
{
  bool found = false;
  while(!found)
  {
    try{
      sleep(timeout_sec);
      transform = buffer->lookupTransform(parent, child,  tf2::TimePointZero);
      tf2::Quaternion quat;
      tf2::fromMsg(transform.transform.rotation, quat);
      tf2::Matrix3x3 m(quat);
      m.getRPY(r, p, y);
      found = true;
      RCLCPP_WARN(node->get_logger(), "%s, %s\n", parent.c_str(), child.c_str());
      dx = transform.transform.translation.x;
      dy = transform.transform.translation.y;
      dz = transform.transform.translation.z;
      if(readyCallback)
      {
        readyCallback(dx, dy, dz, r, p, y);
      }
    }
    catch(const tf2::TransformException & ex)
    {
      RCLCPP_WARN(node->get_logger(), "Waiting for transform %s", ex.what());
    }
  }
}

void PoseLookup::getData(double* dx, double* dy, double* dz, double* r, double* p, double* y)
{
  *dx = this->dx;
  *dy = this->dy;
  *dz = this->dz;
  *r = this->r;
  *p = this->p;
  *y = this->y;
}
