#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Range.h"

std_msgs::Bool flag_AEB; // bool variable declare
geometry_msgs::Twist cmd_vel_msg;

void UltraSonarCallback(const sensor_msgs::Range::ConstPtr& msg)
{
	ROS_INFO("Sonar Seq: [%d]", msg->header.seq);
	ROS_INFO("Sonar Range: [%f]", msg->range);

	if (msg->range <= 1.0)
	{
		ROS_INFO("AEB Activation!!!");
		flag_AEB.data = true;
	}
	else
	{
		flag_AEB.data = false;
	}
}

void UltraSonarCallback2(const sensor_msgs::Range::ConstPtr& msg)
{
	ROS_INFO("Sonar Seq: [%d]", msg->header.seq);
	ROS_INFO("Sonar Range: [%f]", msg->range);

	if (msg->range <= 1.0)
	{
		ROS_INFO("AEB Activation!!!");
		flag_AEB.data = true;
	}
	else
	{
		flag_AEB.data = false;
	}
}

void CarControlCallback(const geometry_msgs::Twist& msg)
{
	ROS_INFO("cmd_vel : linear_x [%f]", msg.linear.x);

	cmd_vel_msg = msg;
	ROS_INFO("cmd_vel : linear_x [%f]", cmd_vel_msg.linear.x);
}

/*void UltraSonarCallback3(const sensor_msgs::Range::ConstPtr& msg)
{

	if(flag_AEB.data == true)
	{
		ROS_INFO("Value : TRUE!!");
	}
	else
	{
		ROS_INFO("Value : FALSE!!");
	}
}*/

int main(int argc, char** argv)
{
	int count = 0;

	ros::init(argc, argv, "aeb_controller");

	ros::NodeHandle n;

	ros::Publisher pub_aeb_activation_flag = n.advertise<std_msgs::Bool>("/aeb_activation_flag", 1); // bool(x) Bool(o) in 1byte
	ros::Publisher pub_cmd_vel = n.advertise<geometry_msgs::Twist>("/ackermann_steering_controller/cmd_vel", 10);

	ros::Rate loop_rate(10); // change 10 to 1


	ros::Subscriber sub1 = n.subscribe("range", 1000, UltraSonarCallback); // gazebo`s value => aeb_controller
	//ros::Subscriber sub2 = n.subscribe("/RangeSonar1", 1000, UltraSonarCallback2); // sonar`s random value => aeb_controller
	//ros::Subscriber sub3 = n.subscribe("/aeb_warning", 1000, UltraSonarCallback3);
	ros::Subscriber cmd_val_sub = n.subscribe("/cmd_vel", 10, CarControlCallback);

	while (ros::ok())
	{
		if ((count % 10) == 0) // == Run per 1sec
		{
			pub_aeb_activation_flag.publish(flag_AEB);
		}

		if (flag_AEB.data == true)
		{
			cmd_vel_msg.linear.x = 0; // this makes a car unmovable
			pub_cmd_vel.publish(cmd_vel_msg);
		}
		else
		{
			pub_cmd_vel.publish(cmd_vel_msg);
		}


		loop_rate.sleep();
		ros::spinOnce(); // Once Callback function runs, Stop
		++count;
	}
	return 0;
}
