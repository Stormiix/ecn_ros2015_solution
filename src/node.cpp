#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Twist.h"
#include <sstream>
#include <math.h>
#include "string"

geometry_msgs::Pose2D currentPose;
geometry_msgs::Pose2D targetPose;

void getCurrent(const geometry_msgs::Pose2D &pose)
{
    currentPose = pose;
}
void getTarget(const geometry_msgs::Pose2D &pose)
{
    targetPose = pose;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot");
    ros::NodeHandle n;
    ros::Publisher cmd_pub = n.advertise<geometry_msgs::Twist>("cmd", 1);
    ros::Subscriber subCurrent = n.subscribe("/current", 1, getCurrent);
    ros::Subscriber subTarget = n.subscribe("/target", 1, getTarget);

    ros::Rate loop_rate(100);
    while (ros::ok())
    {

        double d = 1; // TODO: param
        double kp = 2.7;
        double ka = 2.9;

        double dx = targetPose.x - currentPose.x;
        double dy = targetPose.y - currentPose.y;
        double alpha = atan2(dy, dx) - currentPose.theta;

        // set angle back to [ - pi , pi ]
        while (alpha > M_PI)
            alpha -= 2 * M_PI;
        while (alpha < -M_PI)
            alpha += 2 * M_PI;

        double phi = dx * cos(currentPose.theta) + dy * sin(currentPose.theta) - d;

        double vx = kp * phi;
        double wz = ka * alpha;

        // Create new message
        geometry_msgs::Twist cmd;
        cmd.linear.x = vx;
        cmd.angular.z = wz;

        cmd_pub.publish(cmd);

        loop_rate.sleep();
        ros::spinOnce();
    }

    return 0;
}