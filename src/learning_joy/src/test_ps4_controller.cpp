#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>


class TeleopTurtle
{
public:
  TeleopTurtle();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

  ros::NodeHandle nh_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;

};


TeleopTurtle::TeleopTurtle():
  linear_(1),
  angular_(2)
{

  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);


  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);


  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopTurtle::joyCallback, this);

}

void TeleopTurtle::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist twist;
  twist.angular.z = /* a_scale_* */ joy->axes[angular_];
  twist.linear.x = /* l_scale_* */ joy->axes[linear_];
  //rospy.loginfo("test : %d", joy->axes[0]);

//ROS_INFO("0:[%d] - 1:[%d] - 2:[%d] - 3:[%d] - 4:[%d] - 5:[%d] - 6:[%d] - \n", joy->buttons[7],joy->buttons[8],joy->buttons[9],joy->buttons[10],joy->buttons[11],joy->buttons[14],joy->buttons[15]);
ROS_INFO("lecture 1 : [%f]\n s", joy->axes[11]);
ROS_INFO("lecture 2 : [%f] - [%f]\n s", joy->axes[12],joy->axes[6]);
//ROS_INFO("lecture 3 : [%f]\n s", joy->axes[3]);
//ROS_INFO("lecture 4 : [%f]\n s", joy->axes[4]);
//ROS_INFO("lecture 5 : [%f]\n s", joy->axes[5]);
//ROS_INFO("lecture taile : [%f]\n s", joy->axes[6]);

  vel_pub_.publish(twist);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_turtle");
  TeleopTurtle teleop_turtle;
//  rospy.init_node('talker', log_level=rospy.DEBUG);

ROS_INFO("I heard: [%s]", "hello");

  ros::spin();
}
