#include <controller_manager/controller_manager.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/robot_hw.h>
#include <joint_limits_interface/joint_limits.h>
#include <joint_limits_interface/joint_limits_interface.h>
#include <joint_limits_interface/joint_limits_rosparam.h>
#include <joint_limits_interface/joint_limits_urdf.h>
#include <boost/scoped_ptr.hpp>
#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <scara_hardware/Float32MultiArray.h>
#include <angles/angles.h>

class ROBOTHardwareInterface : public hardware_interface::RobotHW 
{
	public:
        ROBOTHardwareInterface(ros::NodeHandle& nh);
        ~ROBOTHardwareInterface();
        void init();
        void update(const ros::TimerEvent& e);
        void read();
        void write(ros::Duration elapsed_time);
        ros::Publisher pub;
        ros::ServiceClient client;
        std_msgs::Float32MultiArray joints_pub;
        scara_hardware::Float32MultiArray joint_read;

        
    protected:
        hardware_interface::JointStateInterface     joint_state_interface_;
        hardware_interface::PositionJointInterface  position_joint_interface_;
        hardware_interface::VelocityJointInterface  velocity_joint_interface_;
        hardware_interface::EffortJointInterface    effort_joint_interface_;

        joint_limits_interface::PositionJointSaturationInterface positionJointSaturationInterface;
        joint_limits_interface::VelocityJointSaturationInterface velocityJointSaturationInterface;

        int num_joints_;
        std::string joint_name_[4];  
        double joint_position_[4];
        double joint_velocity_[4];
        double joint_effort_[4];
        double joint_position_command_[4];
        double joint_effort_command_[4];
        double joint_velocity_command_[4];
        
        ros::NodeHandle nh_;
        ros::Timer non_realtime_loop_;
        ros::Duration elapsed_time_;
        double loop_hz_;
        boost::shared_ptr<controller_manager::ControllerManager> controller_manager_;
};

