#include "ros/ros.h"
#include "std_msgs/String.h"
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port

#include <sstream>

#define CHAR1_PER		0x00
#define CHAR2_PER		0x02
#define COLON			0x04
#define CHAR3_PER		0x06
#define CHAR4_PER		0x08

int main(int argc, char **argv)
{
  /* ROS init */
  ros::init(argc, argv, "displayer");
  ros::NodeHandle n;

  unsigned char buffer[60] = {0};

  int fd, addr;

  /* Open i2c device */
  fd = open("/dev/i2c-1", O_RDWR);
  if (fd < 0) {
    /* ERROR */
    return -1;
  }

  /* Set i2c slave address */
  addr = 0x70;
  if (ioctl(fd, I2C_SLAVE, addr) < 0) {  
  	/* ERROR */
  	return -1;
  }

  /* Clear displayer */
  buffer[0] = CHAR1_PER;
  buffer[1] = 0x00;
  if (write(fd, CHAR1_PER, 2)) {
  	/* ERROR */
  }

  /* Closes device */
  close(fd);
  
  return 0;
}
