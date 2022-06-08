#!/usr/bin/env python
from email import message
import serial   
import rospy
from std_msgs.msg import Float32MultiArray
from scara_hardware.srv import Float32MultiArray as FloatArray, Float32MultiArrayResponse

pub = 0
serial_port = 0
position = [0,0,0,0]
velocity = [0,0,0,0]
factor 	 = [2.772/370997,3.821/61992,6.28/80012,0.121/126883]
offset   = [-0.15708,2.29214091,0,0.15]
minimums = [1,10,10,1]
lastCommand = ""

def sending_to_arduino(input):
	global serial_port, lastCommand

	commands = []
	velocity = list(input.data)
	for idv,v in enumerate(velocity):
		direction = 1 if v > 0 else 0
		v = 0 if abs(v) < 0.0001 else v
		magnitude = max(1/abs(v),minimums[idv]) if v != 0 else 0
		commands.append("%.0f,%.0f" % (direction,magnitude))
	command = ",".join(commands)
	if(command != lastCommand):
		rospy.loginfo("Serial | Command sent > "+command)
		serial_port.write((command+'\n').encode())
		lastCommand = command
	

def loop():
	global pub, serial_port, factor, offset, position

	mensaje = serial_port.readline()
	if len(mensaje)>0:
		serial_port.flushInput()
		data = mensaje.strip('\n').strip('\r').split(',')
		
		for idd, d in enumerate(data):
			try:
				datum = int(d)*factor[idd]+offset[idd]
				position[idd] = datum
			except:
				position[idd] = 0

		output_data = Float32MultiArray()
		output_data.data = position
		pub.publish(output_data)

def server(req):
	global position, velocity
	res = Float32MultiArrayResponse() 
	response = []
	for p in position:
		response.append(p)
	for v in velocity:
		response.append(v)
	responseStr = [str(r) for r in response]
	rospy.loginfo("Serial | Position: "+",".join(responseStr))
	res.res = response
	return res

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

	pub = rospy.Publisher('/arduino_position', Float32MultiArray, queue_size=10)
	rospy.Service('/arduino_output', FloatArray, server)
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