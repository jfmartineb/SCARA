/* 
 *  
 *  Para tener las librerias de ROS debemos instalar el paquete de ROS Serial Arduino
 *  
 *  sudo apt-get install ros-melodic-rosserial-arduino
 *  
 *  y seguimos las instrucciones en 
 *  
 *  http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup
 *  
 *  Para poder subir el codigo desde ubuntu debemos cambiar los permisos del puerto COM
 *  
 */


#include <Servo.h>
#define servoPin 2

Servo motor;


////////////////////////////////////////////////////////////////////

#include <ros.h>
#include <std_msgs/Float32MultiArray.h>

ros::NodeHandle  nh;
std_msgs::Float32MultiArray joint_state;

double command;
void set_command( const std_msgs::Float32MultiArray& cmd_msg){
  command = cmd_msg.data[0];
  int angle = command;
  motor.write(angle);
}

ros::Subscriber<std_msgs::Float32MultiArray> sub("/joints_to_arduino", set_command);
ros::Publisher pub("/joint_states_from_arduino", &joint_state);

void setup_nh(){
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);
}

////////////////////////////////////////////////////////////////////////////////////////////

unsigned long now,pubTime;
double pos = 0, vel = 0;

void setup(){
  setup_nh();
  motor.attach(servoPin);
  pubTime = millis();
}

void loop(){
  
  now = millis();

  if ((now - pubTime) > 200)
  {
    joint_state.data_length   = 2;
    joint_state.data[0]       = command;
    joint_state.data[1]       = vel;
    
    pub.publish(&joint_state);
    pubTime = now;
  }

  nh.spinOnce();
  
}
