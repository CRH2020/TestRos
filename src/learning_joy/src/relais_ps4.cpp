#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>


class TeleopTurtle
{
public:
  TeleopTurtle();

private:
  void velCallback(const geometry_msgs::Twist::ConstPtr& twist);

  void posCallback(const geometry_msgs::Pose2D::ConstPtr& pos);

  ros::NodeHandle nh_;

  ros::Publisher vel_pub_;
  ros::Subscriber vel_sub_;

  ros::Publisher pos_pub_;
  ros::Subscriber pos_sub_;
};


TeleopTurtle::TeleopTurtle()
{

  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("velocity", 1);
  vel_sub_ = nh_.subscribe<geometry_msgs::Twist>("velocity1", 10, &TeleopTurtle::velCallback, this);

  pos_pub_ = nh_.advertise<geometry_msgs::Pose2D>("pos1", 1);
  pos_sub_ = nh_.subscribe<geometry_msgs::Pose2D>("pos", 10, &TeleopTurtle::posCallback, this);

  ROS_INFO("Relais pret !\n");

}

void TeleopTurtle::velCallback(const geometry_msgs::Twist::ConstPtr& twist)
{
  geometry_msgs::Twist twist_send;

  twist_send = *twist;

  vel_pub_.publish(twist_send);

}

void TeleopTurtle::posCallback(const geometry_msgs::Pose2D::ConstPtr& pos)
{
  geometry_msgs::Pose2D pos_send;

  pos_send = *pos;

  pos_pub_.publish(pos_send);

}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "relais_ps4");
  TeleopTurtle teleop_turtle;

  ros::spin();
}
