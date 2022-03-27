#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Float32.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Range.h"
#include "nav_msgs/Odometry.h"

#define frequency_odom_pub 50
#define stop_dist 3

std_msgs::Bool flag_AEB; // bool variable declare
geometry_msgs::Twist cmd_vel_msg;
std_msgs::Float32 delta_range;
std_msgs::Float32 old_sonar_range;
nav_msgs::Odometry delta_pos, past_pos, pos;
//geometry_msgs::Twist velocity;
nav_msgs::Odometry velocity;

float x, y;
float delta_x, delta_y;
float vx, vy;

float aeb_collision_distance = 200;

void odomCallback(const nav_msgs::Odometry& msg)
{
	pos.pose.pose.position.x = msg.pose.pose.position.x;
	pos.pose.pose.position.y = msg.pose.pose.position.y;
	
	delta_pos.pose.pose.position.x = pos.pose.pose.position.x - past_pos.pose.pose.position.x;
	delta_pos.pose.pose.position.y = pos.pose.pose.position.y - past_pos.pose.pose.position.y;
	
	past_pos.pose.pose.position.x = msg.pose.pose.position.x;
	past_pos.pose.pose.position.y = msg.pose.pose.position.y;
	
	velocity.twist.twist.linear.x = delta_pos.pose.pose.position.x * frequency_odom_pub;
	velocity.twist.twist.linear.y = -delta_pos.pose.pose.position.y * frequency_odom_pub; // (-) cause y-axis is reversible
}

void odomCallback_stop(const nav_msgs::Odometry& msg)
{
	
	float old_x, old_y;
	
	old_x = x;
	old_y = y;
	ROS_INFO("%.2lf, %.2lf", msg.pose.pose.position.x, msg.pose.pose.position.y);
	
	x = msg.pose.pose.position.x;
	y = msg.pose.pose.position.y;
	
	delta_x = x - old_x;
	delta_y = y - old_y;
	
	vx = delta_x * frequency_odom_pub;
	vy = delta_y * frequency_odom_pub;
	
	if(x>= stop_dist)
	{
		flag_AEB.data = true;
	}
	
}

void UltraSonarCallback(const sensor_msgs::Range::ConstPtr& msg) 
{
	//ROS_INFO("Sonar Seq: [%d]", msg->header.seq);
	//ROS_INFO("Sonar Range: [%f]", msg->range);
	
	aeb_collision_distance = vx * (0.7 + 0.1) * 0.22778 * 3.5; // 2.5 safety
	if(msg->range <= aeb_collision_distance)
	{
		ROS_INFO("AEB Activation!!!");
		flag_AEB.data = true;
	}
	else
	{
		flag_AEB.data = false;
	}
	
	
	/*delta_range.data = old_sonar_range.data - msg->range;
	
	
	if(delta_range.data < 0)
	{
		delta_range.data *= -1; // absolute value
	}
	ROS_INFO("delta_range = [%f] ", delta_range.data);
	ROS_INFO("--------------------------------");
	ROS_INFO("--------------------------------");
	
	
	
	 old_sonar_range.data = msg->range;*/
	
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
	cmd_vel_msg.linear.x = msg.linear.x; // speed
	cmd_vel_msg.linear.z = msg.linear.z; // angle
	//ROS_INFO("cmd_vel : linear_x [%f]", cmd_vel_msg.linear.x);
	//ROS_INFO("cmd_vel : angular_z [%f]", cmd_vel_msg.linear.z);
}

int main(int argc, char **argv)
 {
	int count = 0;
	ros::init(argc, argv, "aeb_controller");
	ros::NodeHandle n;
	ros::Rate loop_rate(10); // change 10 to 1
	
	std::string odom_sub_topic = "/ackermann_steering_controller/odom";
	
	ros::Publisher pub_aeb_activation_flag = n.advertise<std_msgs::Bool>("/aeb_activation_flag", 1);
	ros::Publisher pub_cmd_vel = n.advertise<geometry_msgs::Twist>("/ackermann_steering_controller/cmd_vel", 10);
	ros::Publisher pub_range_diff = n.advertise<std_msgs::Float32>("/range_diff", 10);
  //ros::Publisher pub_velocity = n.advertise<nav_msgs::Odometry>("/velocity", 10);
	
	ros::Subscriber sub1 = n.subscribe("range", 1000, UltraSonarCallback);
  //ros::Subscriber sub2 = n.subscribe("/RangeSonar1", 1000, UltraSonarCallback2); // sonar`s random value => aeb_controller
	ros::Subscriber cmd_val_sub = n.subscribe("/cmd_vel", 10, CarControlCallback);
    ros::Subscriber sub_odom = n.subscribe(odom_sub_topic, 10, odomCallback_stop);
	
	while (ros::ok()) 
	{
		if ((count % 10) == 0) // == Run per 1sec
		{
			pub_aeb_activation_flag.publish(flag_AEB); 
		}
		
		if (flag_AEB.data == true)
		{
			if(cmd_vel_msg.linear.x > 0) cmd_vel_msg.linear.x = 0; 
			pub_cmd_vel.publish(cmd_vel_msg);
		}
		else
		{
			pub_cmd_vel.publish(cmd_vel_msg);
		}
		
		ROS_INFO("Odom : [%6.3f %6.3f] m | Velocity : [%6.3f %6.3f] m/s", x, y, vx , vy);
		ROS_INFO("Collision Distance : [%6.3f]", aeb_collision_distance);
		
		//pub_range_diff.publish(delta_range);
		//pub_velocity.publish(velocity);
		
		loop_rate.sleep();
		ros::spinOnce();
		++count;
	}
	return 0;
}
