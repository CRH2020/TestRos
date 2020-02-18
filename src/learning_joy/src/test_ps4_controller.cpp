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

  const double ANGULAR_SCALE_MAX = 2;
  double angular_scale_ = 0;
  const double LINEAR_SCALE_MAX = 10;
  double linear_scale_ = 10;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;

  const int AXE_X_GAUCHE = 0;
  const int AXE_Y_GAUCHE = 1;

  const int AXE_X_DROITE = 2;
  const int AXE_Y_DROITE = 5;

  const int AXE_R2 = 4;

  const int AXE_X_FLECHE = 9;
  int axe_x_fleche_inactif = 0;
  const int AXE_Y_FLECHE = 10;
  int axe_y_fleche_inactif = 0;

  int send_0 = 0;

};


TeleopTurtle::TeleopTurtle():
  linear_(1),
  angular_(2)
{

  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", angular_scale_, angular_scale_);
  nh_.param("scale_linear", linear_scale_, linear_scale_);


  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("velocity", 1);

  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopTurtle::joyCallback, this);

  ROS_INFO("angular_:[%d] - linear_:[%d]\n", angular_, linear_);

}

void TeleopTurtle::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist twist;

  double r2_accel = (joy->axes[AXE_R2] - 1 ) / -2;

  /* Devient Non actif */
  if ( joy->axes[AXE_X_FLECHE] == 0 && axe_x_fleche_inactif == 0) {
    axe_x_fleche_inactif = 1;
  } else if ( joy->axes[AXE_X_FLECHE] == 1 && axe_x_fleche_inactif == 1) {
      /* Diminue le facteur des axes x*/
    axe_x_fleche_inactif = 0;
    angular_scale_ = angular_scale_ > 0 ? angular_scale_ - 0.02 : 0;
  } else if ( joy->axes[AXE_X_FLECHE] == -1 && axe_x_fleche_inactif == 1) {
    /* Augemente le facteur des axes x*/
    axe_x_fleche_inactif = 0;
    angular_scale_ = angular_scale_ < ANGULAR_SCALE_MAX ? angular_scale_ + 0.02 : ANGULAR_SCALE_MAX;
  }

  /* Devient Non actif */
  if ( joy->axes[AXE_Y_FLECHE] == 0 && axe_y_fleche_inactif == 0) {
    axe_y_fleche_inactif = 1;
  } else if ( joy->axes[AXE_Y_FLECHE] == -1 && axe_y_fleche_inactif == 1) {
      /* Diminue le facteur des axes x*/
    axe_y_fleche_inactif = 0;
    linear_scale_ = linear_scale_ > 0 ? linear_scale_ - 1 : 0;
  } else if ( joy->axes[AXE_Y_FLECHE] == 1 && axe_y_fleche_inactif == 1) {
    /* Augemente le facteur des axes x*/
    axe_y_fleche_inactif = 0;
    linear_scale_ = linear_scale_ < LINEAR_SCALE_MAX ? linear_scale_ + 1 : LINEAR_SCALE_MAX;
  }

  /* Non actif */
  twist.angular.z = -r2_accel * (angular_scale_ * joy->axes[AXE_X_DROITE]) ;
  twist.linear.x  = r2_accel * (linear_scale_ * joy->axes[AXE_Y_GAUCHE]) ;

//ROS_INFO("0:[%d] - 1:[%d] - 2:[%d] - 3:[%d] - 4:[%d] - 5:[%d] - 6:[%d] - \n", joy->buttons[7],joy->buttons[8],joy->buttons[9],joy->buttons[10],joy->buttons[11],joy->buttons[14],joy->buttons[15]);
//ROS_INFO("lecture 1 : [%f]\n s", joy->axes[11]);
//ROS_INFO("lecture 2 : [%f] - [%f]\n s", joy->axes[12],joy->axes[6]);
//ROS_INFO("lecture 3 : [%f]\n s", joy->axes[3]);
//ROS_INFO("lecture 4 : [%f]\n s", joy->axes[4]);
//ROS_INFO("lecture 5 : [%f]\n s", joy->axes[5]);
//ROS_INFO("lecture taile : [%f]\n s", joy->axes[6]);
  if ( twist.angular.z == 0 && twist.linear.x == 0){
    if (send_0 < 5){
      send_0++;
      vel_pub_.publish(twist);
    }
  } else {
    send_0 = 0;
    vel_pub_.publish(twist);
  }
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "cmd_ps4");
  TeleopTurtle teleop_turtle;

  ros::spin();
}
