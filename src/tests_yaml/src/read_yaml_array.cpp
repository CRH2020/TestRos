#include <ros/ros.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "test_tirette_timer");
  ros::NodeHandle n;
  int test;
  std::vector<int> array_test(0, 10);

  while (ros::ok())
  {
    n.getParam("/param_test", test);
    n.getParam("/array_test", array_test);
    ROS_INFO("Param value : %d\n", test);
    for(int i = 0; i < 10; i++){
      ROS_INFO("%d\n", array_test[i]);
    }
  }

  return 0;
}
