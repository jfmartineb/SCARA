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
        std_msgs::Float32MultiArray joints_pub;
        
    protected:
        hardware_interface::JointStateInterface     joint_state_interface_;
        hardware_interface::PositionJointInterface  position_joint_interface_;
        hardware_interface::EffortJointInterface    effort_joint_interface_;

        joint_limits_interface::PositionJointSaturationInterface positionJointSaturationInterface;
        
        int num_joints_;
        std::string joint_name_;  
        double joint_position_;
        double joint_velocity_;
        double joint_effort_;
        double joint_position_command_;
        double joint_effort_command_;
        double joint_velocity_command_;
        
        ros::NodeHandle nh_;
        ros::Timer non_realtime_loop_;
        ros::Duration elapsed_time_;
        double loop_hz_;
        boost::shared_ptr<controller_manager::ControllerManager> controller_manager_;
};

