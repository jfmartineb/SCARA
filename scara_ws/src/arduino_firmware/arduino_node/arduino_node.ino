/*

    Para tener las librerias de ROS debemos instalar el paquete de ROS Serial Arduino

    sudo apt-get install ros-melodic-rosserial-arduino

    y seguimos las instrucciones en

    http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup

    Para poder subir el codigo desde ubuntu debemos cambiar los permisos del puerto COM

*/

#include <ros.h>
#include <std_msgs/UInt16MultiArray.h>
#include <std_msgs/Int32MultiArray.h>

#define DPulso  34
#define DDir    35
#define DSensor 16

volatile unsigned int DCount     = 0;
volatile unsigned int DPeriod    = 1;
volatile long DPosition   = 0;
volatile bool DVPulso = false;
volatile bool DVDir   = false;

void setup_timer2() { //set timer2 interrupt at 1kHz
  cli();

  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 1khz increments
  //OCR2A = 249;// = (16e6) / (1000*64) - 1 (must be <256)
  OCR2A = 199;// = (16e6) / (250*256) - 1 (must be <256)
  //OCR2A = 155;// = (16e6) / (100*1024) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Prescalers https://microcontrollerslab.com/arduino-timer-interrupts-tutorial/
  // CS = 001 for 1
  // CS = 010 for 8
  // CS = 011 for 32
  // CS = 100 for 64
  // CS = 101 for 128
  // CS = 110 for 256
  // CS = 111 for 1024
  //TCCR2B |= (1 << CS22);
  TCCR2B |= (1 << CS21);
  //TCCR2B |= (1 << CS20);
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);

  sei();//allow interrupts
}
ISR(TIMER2_COMPA_vect) {
  timed_loop();
}
void timed_loop() {
  DCount++;
  if (DCount >= DPeriod && DPeriod > 0) {
    DVPulso = !DVPulso;
    DCount = 0;
    digitalWrite(DDir, !DVDir);
    digitalWrite(DPulso, DVPulso);
    DPosition = DPosition + DVDir * 1 - !DVDir * 1;
  }
}
void setup_robot() {
  pinMode(DSensor, INPUT);
  pinMode(DPulso, OUTPUT);
  pinMode(DDir, OUTPUT);

  while (!digitalRead(DSensor)) {}
  DPosition = 0;
  DPeriod = 0;
}

////////////////////////////////////////////////////////////////////

ros::NodeHandle  nh;

std_msgs::Int32MultiArray joint_positions;

ros::Publisher pub("/joint_positions_from_arduino", &joint_positions);

void set_command( const std_msgs::UInt16MultiArray& cmd_msg) {
  DPeriod = cmd_msg.data[0];
  DVDir   = cmd_msg.data[1] > 0;
}

ros::Subscriber<std_msgs::UInt16MultiArray> sub("/speeds_to_arduino", set_command);

void setup_nh() {
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);
}

////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  setup_nh();
  setup_timer2();
  setup_robot();
}

unsigned long now,last=0;
void loop() {
  nh.spinOnce();

  now = millis();
  if((now - last) > 100){
    joint_positions.data_length = 1;
    joint_positions.data[0] = DPosition;
    pub.publish(&joint_positions);
    last = now;
  }
}
