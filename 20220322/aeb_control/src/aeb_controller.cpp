#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Float32.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Range.h"
#include "nav_msgs/Odometry.h"


std_msgs::Bool flag_AEB; // bool variable declare
geometry_msgs::Twist cmd_vel_msg;

std_msgs::Float32 delta_range;
std_msgs::Float32 old_sonar_range;
nav_msgs::Odometry delta_pos, past_pos, pos;
//geometry_msgs::Twist velocity;
nav_msgs::Odometry velocity;

void odomCallback(const nav_msgs::Odometry& msg)
{
	pos.pose.pose.position.x = msg.pose.pose.position.x;
	pos.pose.pose.position.y = msg.pose.pose.position.y;
	
	delta_pos.pose.pose.position.x = pos.pose.pose.position.x - past_pos.pose.pose.position.x;
	delta_pos.pose.pose.position.y = pos.pose.pose.position.y - past_pos.pose.pose.position.y;
	
	past_pos.pose.pose.position.x = msg.pose.pose.position.x;
	past_pos.pose.pose.position.y = msg.pose.pose.position.y;
	
	velocity.twist.twist.linear.x = delta_pos.pose.pose.position.x / 0.02;
	velocity.twist.twist.linear.y = -delta_pos.pose.pose.position.y / 0.02; // (-) cause y-axis is reversible
	
	
}

void UltraSonarCallback(const sensor_msgs::Range::ConstPtr& msg) 
{
	ROS_INFO("Sonar Seq: [%d]", msg->header.seq);
	ROS_INFO("Sonar Range: [%f]", msg->range);
	
	if(msg->range <= 1)
	{
		ROS_INFO("AEB Activation!!!");
		flag_AEB.data = true;
	}
	else
	{
		flag_AEB.data = false;
	}
	
	delta_range.data = old_sonar_range.data - msg->range;
	
	
	if(delta_range.data < 0)
	{
		delta_range.data *= -1; // absolute value
	}
	ROS_INFO("delta_range = [%f] ", delta_range.data);
	ROS_INFO("--------------------------------");
	ROS_INFO("--------------------------------");
	
	
	
	 old_sonar_range.data = msg->range;
	
}

void UltraSonarCallback2(const sensor_msgs::Range::ConstPtr& msg) 
{
	ROS_INFO("Sonar Seq: [%d]", msg->header.seq);
	ROS_INFO("Sonar Range: [%f]", msg->range);
	
	if(msg->range <= 1.0)
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

void RangeDiffCallback(const sensor_msgs::Range::ConstPtr& msg)
{
	
	
}

int main(int argc, char **argv)
 {
	int count = 0;
	
	ros::init(argc, argv, "aeb_controller");
	
	ros::NodeHandle n;
	
	std::string odom_sub_topic = "/ackermann_steering_controller/odom";
	
	ros::Publisher pub_aeb_activation_flag = n.advertise<std_msgs::Bool>("/aeb_activation_flag", 1); // bool(x) Bool(o) in 1byte
	ros::Publisher pub_cmd_vel = n.advertise<geometry_msgs::Twist>("/ackermann_steering_controller/cmd_vel", 10);
	ros::Publisher pub_range_diff = n.advertise<std_msgs::Float32>("/range_diff", 10);
	ros::Publisher pub_velocity = n.advertise<nav_msgs::Odometry>("/velocity", 10);
	
	ros::Rate loop_rate(10); // change 10 to 1
	
	
	ros::Subscriber sub1 = n.subscribe("range", 1000, UltraSonarCallback); // gazebo`s value => aeb_controller
	//ros::Subscriber sub2 = n.subscribe("/RangeSonar1", 1000, UltraSonarCallback2); // sonar`s random value => aeb_controller
	ros::Subscriber cmd_val_sub = n.subscribe("/cmd_vel", 10, CarControlCallback);
	ros::Subscriber sub_odom = n.subscribe(odom_sub_topic, 10, odomCallback);
	
	while (ros::ok()) 
	{
		if ((count % 10) == 0) // == Run per 1sec
		{
			pub_aeb_activation_flag.publish(flag_AEB); 
		}
		
		if (flag_AEB.data == true)
		{
			cmd_vel_msg.linear.x = 0; 
			pub_cmd_vel.publish(cmd_vel_msg);
		}
		else
		{
			pub_cmd_vel.publish(cmd_vel_msg);
		}
		
		pub_range_diff.publish(delta_range);
		pub_velocity.publish(velocity);
		
		loop_rate.sleep();
		ros::spinOnce(); // Once Callback function runs, Stop
		++count;
	}
	return 0;
}
