#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"

void turtleCallback(const turtlesim::Pose::ConstPtr& msg)
{
ROS_INFO("Turtle subscriber@[%f, %f, %f]",
msg->x, msg->y, msg->theta);
}

int main (int argc, char **argv)
{
	ros::init(argc, argv, "turtlebot_subscriber");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("turtle1/pose", 1,turtleCallback); 
	ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);
	while (ros::ok()){
		geometry_msgs::Twist my_vel;
		my_vel.linear.x = 0.1;
		pub.publish(my_vel);
		ros::spinOnce();
	}
	return 0;
}

