#!/usr/bin/env python
from email import message
import serial   
import rospy
from std_msgs.msg import Float32MultiArray

pub = 0
serial_port = 0
factor = [1,1,1,1/1e6]
offset = [0,0,0,0]

def sending_to_arduino(input):
	global serial_port

	commands = []
	velocities = list(input.data)
	for v in velocities:
		direction = 1 if v > 0 else 0
		magnitude = abs(v)
		commands.append("%.0f,%.0f" % (direction,magnitude))
	command = ",".join(commands)
	serial_port.write((command+'\n').encode())
	rospy.loginfo("Serial | Command sent > "+command)

def loop():
	global pub, serial_port, factor, offset

	mensaje = serial_port.readline()
	if len(mensaje)>0:
		serial_port.flushInput()
		data = mensaje.strip('\n').strip('\r').split(',')
		
		formated_data = []
		for idd, d in enumerate(data):
			try:
				datum = int(d)*factor[idd]+offset[idd]
				formated_data.append(datum)
			except:
				formated_data.append(0)

		output_data = Float32MultiArray()
		output_data.data = formated_data
		pub.publish(output_data)

def node():

	global pub, serial_port
	port   = rospy.get_param("~port", "/dev/ttyACM0")

	serial_port = serial.Serial(
		port=port, 
		baudrate=115200,
		timeout=0.1)
	serial_port.flushInput()
	serial_port.flushOutput()

	rospy.init_node('serial_node', anonymous=False)

	pub = rospy.Publisher('/arduino_output', Float32MultiArray, queue_size=10)
	rospy.Subscriber("/arduino_input", Float32MultiArray, sending_to_arduino, queue_size=10) 

	rospy.loginfo("Serial | Node started")

	while not rospy.is_shutdown():
		loop()

	serial_port.close()


if __name__ == '__main__':

	try:
		node()
	except rospy.ROSInterruptException:
		pass