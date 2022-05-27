#include <scara_hardware/scara_hardware.h>

ROBOTHardwareInterface::ROBOTHardwareInterface(ros::NodeHandle& nh) : nh_(nh) {
    init();
    controller_manager_.reset(new controller_manager::ControllerManager(this, nh_));
    loop_hz_=3;
    ros::Duration update_freq = ros::Duration(1.0/loop_hz_);
	
	pub = nh_.advertise<std_msgs::Float32MultiArray>("/arduino_input",10);
    client = nh_.serviceClient<scara_hardware::Float32MultiArray>("/arduino_output");

	
    non_realtime_loop_ = nh_.createTimer(update_freq, &ROBOTHardwareInterface::update, this);
}

ROBOTHardwareInterface::~ROBOTHardwareInterface() {
}

void ROBOTHardwareInterface::init() {
    
	//joint_name_=["hombro","codo","muneca","articulacion"];
    
// Create joint state interface
    //hardware_interface::JointStateHandle jointStateHandle(joint_name_, &joint_position_, &joint_velocity_, &joint_effort_);
    //joint_state_interface_.registerHandle(jointStateHandle);

// Create position joint interface
    //hardware_interface::JointHandle jointPositionHandle(jointStateHandle, &joint_position_command_);
    //position_joint_interface_.registerHandle(jointPositionHandle);
    
// Create velocity joint interface
	//hardware_interface::JointHandle jointVelocityHandle(jointStateHandle, &joint_velocity_command_);
    //velocity_joint_interface_.registerHandle(jointVelocityHandle);
    
// Create effort joint interface
    //hardware_interface::JointHandle jointEffortHandle(jointStateHandle, &joint_effort_command_);
	//effort_joint_interface_.registerHandle(jointEffortHandle);
	
// Create Joint Limit interface   
    //joint_limits_interface::JointLimits limits;
    //joint_limits_interface::getJointLimits("junta", nh_, limits);
	//joint_limits_interface::VelocityJointSaturationHandle jointLimitsHandle(jointVelocityHandle, limits);
	//velocityJointSaturationInterface.registerHandle(jointLimitsHandle);
	
/*
If you have more joints then,

    joint_name_= "joint2"
    
// Create joint state interface
    hardware_interface::JointStateHandle jointStateHandle2(joint_name_, &joint_position_2, &joint_velocity_2, &joint_effort_2);
    joint_state_interface_.registerHandle(jointStateHandle);

//create the position/velocity/effort interface according to your actuator 
    hardware_interface::JointHandle jointPositionHandle2(jointStateHandle2, &joint_position_command_2);
    position_joint_interface_.registerHandle(jointPositionHandle2);
    
    hardware_interface::JointHandle jointVelocityHandle2(jointStateHandle2, &joint_velocity_command_2);
    effort_joint_interface_.registerHandle(jointVelocityHandle2);
    
    hardware_interface::JointHandle jointEffortHandle2(jointStateHandle2, &joint_effort_command_2);
	effort_joint_interface_.registerHandle(jointEffortHandle2);
	
//create joint limit interface.
    joint_limits_interface::getJointLimits("joint2", nh_, limits);
	joint_limits_interface::EffortJointSaturationHandle jointLimitsHandle2(jointEffortHandle2, limits);
	effortJointSaturationInterface.registerHandle(jointLimitsHandle2);
	
	Repeat same for other joints
*/

    joint_name_[0] = "hombro";
    joint_name_[1] = "codo";
    joint_name_[2] = "muneca";
    joint_name_[3] = "articulacion";
    
    hardware_interface::JointStateHandle jointStateHandle0(joint_name_[0], &joint_position_[0], &joint_velocity_[0], &joint_effort_[0]);
    joint_state_interface_.registerHandle(jointStateHandle0);
    hardware_interface::JointHandle jointVelocityHandle0(jointStateHandle0, &joint_velocity_command_[0]);
    velocity_joint_interface_.registerHandle(jointVelocityHandle0);

    hardware_interface::JointStateHandle jointStateHandle1(joint_name_[1], &joint_position_[1], &joint_velocity_[1], &joint_effort_[1]);
    joint_state_interface_.registerHandle(jointStateHandle1);
    hardware_interface::JointHandle jointVelocityHandle1(jointStateHandle1, &joint_velocity_command_[1]);
    velocity_joint_interface_.registerHandle(jointVelocityHandle1);

    hardware_interface::JointStateHandle jointStateHandle2(joint_name_[2], &joint_position_[2], &joint_velocity_[2], &joint_effort_[2]);
    joint_state_interface_.registerHandle(jointStateHandle2);
    hardware_interface::JointHandle jointVelocityHandle2(jointStateHandle2, &joint_velocity_command_[2]);
    velocity_joint_interface_.registerHandle(jointVelocityHandle2);

    hardware_interface::JointStateHandle jointStateHandle3(joint_name_[3], &joint_position_[3], &joint_velocity_[3], &joint_effort_[3]);
    joint_state_interface_.registerHandle(jointStateHandle3);
    hardware_interface::JointHandle jointVelocityHandle3(jointStateHandle3, &joint_velocity_command_[3]);
    velocity_joint_interface_.registerHandle(jointVelocityHandle3);
    
// Register all joints interfaces    
    registerInterface(&joint_state_interface_);
    registerInterface(&velocity_joint_interface_);
    //registerInterface(&effort_joint_interface_);
    //registerInterface(&velocityJointSaturationInterface);
}

void ROBOTHardwareInterface::update(const ros::TimerEvent& e) {
    elapsed_time_ = ros::Duration(e.current_real - e.last_real);
    read();
    controller_manager_->update(ros::Time::now(), elapsed_time_);
    write(elapsed_time_);
}

void ROBOTHardwareInterface::read() {

    joint_read.request.req=1.0;
	
	if(client.call(joint_read))
	{
        for(int j=0;j<4;j++){
            joint_position_[j] = joint_read.response.res[j];
	        joint_velocity_[j] = joint_read.response.res[j+4];
        }
	    
	    // ROS_INFO("HW | Current Pos: %.2f, Vel: %.2f",joint_position_,joint_velocity_);
/*
if more than one joint,
        get values for joint_position_2, joint_velocity_2,......
*/	    
	    
	}
	else
	{
        for(int j=0;j<4;j++){
	        joint_position_[j] = 0;
	        joint_velocity_[j] = 0;
        }
	}
    
}

void ROBOTHardwareInterface::write(ros::Duration elapsed_time) {
   
    // velocityJointSaturationInterface.enforceLimits(elapsed_time);    
	
/*
if more than one joint,
    publish values for joint_effort_command_2,......
*/	

    joints_pub.data.clear();
    for(int j=0;j<4;j++){
        joints_pub.data.push_back(joint_velocity_command_[j]);
    }

	ROS_INFO("HW | Commands: %.5f,%.5f,%.5f,%.5f",joint_velocity_command_[0],joint_velocity_command_[1],joint_velocity_command_[2],joint_velocity_command_[3]);
	pub.publish(joints_pub);
		
}



int main(int argc, char** argv)
{
    ros::init(argc, argv, "robot_hardware_interface");
    ros::NodeHandle nh;
    //ros::AsyncSpinner spinner(4);  
    ros::MultiThreadedSpinner spinner(2); // Multiple threads for controller service callback and for the Service client callback used to get the feedback from ardiuno
    ROBOTHardwareInterface ROBOT(nh);
    //spinner.start();
    spinner.spin();
    //ros::spin();
    return 0;
}