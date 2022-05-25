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

double command;
void set_command( const std_msgs::Float32MultiArray& cmd_msg){
  command = cmd_msg.data[0];
  int angle = command;
  angle = constrain(angle,0,180);
  motor.write(angle);
}

ros::Subscriber<std_msgs::Float32MultiArray> sub("/joints_to_arduino", set_command);

void setup_nh(){
  nh.initNode();
  nh.subscribe(sub);
}

////////////////////////////////////////////////////////////////////////////////////////////

void setup(){
  setup_nh();
  motor.attach(servoPin);
}

void loop(){
  nh.spinOnce();
}
