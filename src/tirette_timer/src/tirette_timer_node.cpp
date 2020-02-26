#include <ros/ros.h>
#include <bcm2835.h>
#include <stdio.h>

#define PIN RPI_GPIO_P1_11// Valeur pour le moment arbitraire, A CHANGER


void callback1(const ros::TimerEvent&)
{

    ros::Duration(1.0).sleep();
    return;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "test_tirette_timer");
  ros::NodeHandle n;



  /* Toutes les 5 secondes on aura la fonction callback1 qui sera appelee */
  ros::Timer timer1 = n.createTimer(ros::Duration(5.0), callback1);

  ros::spin();

  return 0;
}
