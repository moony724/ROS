#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Int8.h"
#include "sensor_msgs/Range.h"
#define LIMIT 5

std_msgs::Float64 range_avg;
int cnt;
float val[LIMIT], sum;

void Range_AvgCallback(const sensor_msgs::Range::ConstPtr& msg) 
{
	range_avg.data = 0.0;
	sum = 0.0;
	cnt++;
	switch(cnt)
	{
		case 1:
		val[0] = msg->range; break;
		case 2:
		val[1] = msg->range; break;
		case 3:
		val[2] = msg->range; break;
		case 4:
		val[3] = msg->range; break;
		case 5:
		val[4] = msg->range; break;
	}
	if(cnt > LIMIT) cnt = 0;
	
	//ROS_INFO("1: %f",val[0]);
	//ROS_INFO("2: %f",val[1]);
	//ROS_INFO("3: %f",val[2]);
	//ROS_INFO("4: %f",val[3]);
	//ROS_INFO("5: %f",val[4]);
	
	for(int i = 0; i < LIMIT; i++)
	{
		sum += val[i];
	}
	range_avg.data = sum / LIMIT;
}

int main(int argc, char **argv)
 {
	int count = 0;
	ros::init(argc, argv, "sonar_avg_filter_node");
	ros::NodeHandle n;
	ros::Rate loop_rate(10);
	
	ros::Publisher pub_range_avg = n.advertise<std_msgs::Float64>("/range_avg", 10);
	ros::Subscriber sub_range = n.subscribe("range", 1000, Range_AvgCallback);
  
	while (ros::ok()) 
	{
		pub_range_avg.publish(range_avg);
		
		loop_rate.sleep();
		ros::spinOnce();
		++count;
	}
	return 0;
}
