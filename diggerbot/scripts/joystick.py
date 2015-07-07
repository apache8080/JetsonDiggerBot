#!/usr/bin/env python

import rospy

#try:
from sensor_msgs.msg import Joy
#from std_msgs.msg import Int16MultiArray
#from diggerbot.msg import JoyVals
#except ImportError:
 #   from joy.msg import Joy

def main():
	rospy.init_node('joystick')
	joy = rospy.Subscriber('joy', Joy, joyCallback)
	try:
        	rospy.spin()
	except rospy.ROSInterruptException: pass
		
	
def joyCallback(joy):
	buttons=joy.buttons
	#joy_value_pub = rospy.Publisher("joyval", JoyVals)
	#print buttons
	#joy_vals=JoyVals
	joy_buttons_pressed=[]
	for b in range(len(buttons)):
		if buttons[b]==1:
			print 'button: '+str(b)+' was pressed'
			joy_buttons_pressed.append(b)
	print 'Joy1 Y-axis: '+str(joy.axes[1])+' Joy2 X-axis: '+str(joy.axes[2])
	#joy_vals.button_vals = joy_buttons_pressed	
	#joy_vals.joystick_vals = [joy.axes[1],joy.axes[2]]
	#joy_value_pub.publish(joy_vals)

if __name__ == '__main__':
	main()
