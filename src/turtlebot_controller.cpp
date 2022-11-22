#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"

void turtleCallback(const turtlesim::Pose::ConstPtr& msg)
{
ROS_INFO("Turtle subscriber@[%f, %f, %f]",
msg->x, msg->y, msg->theta);
}

int main (int argc, char **argv)
{
	ros::init(argc, argv, "turtlebot_subscriber");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("my_new_turtle/pose", 1,turtleCallback); 
	ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("my_new_turtle/cmd_vel", 1);
	ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");
	
	turtlesim::Spawn spawn;
	spawn.request.x = 1.0;
	spawn.request.y = 1.0;
	spawn.request.theta = 0.0;
	spawn.request.name = "my_new_turtle";
	
	client.call(spawn);
	
	while (ros::ok()){
		geometry_msgs::Twist my_vel;
		my_vel.linear.x = 0.1;
		pub.publish(my_vel);
		ros::spinOnce();
	}
	return 0;
}

