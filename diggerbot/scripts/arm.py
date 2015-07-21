#!/usr/bin/env python

import os
import rospy
from diggerbot.msg import JoyVals
from time import sleep

is_pressed = False
os.chdir("/home/ubuntu/catkin_ws/src/diggerbot/scripts")
def main():
    rospy.init_node('arm_controller')
    joy = rospy.Subscriber('joyvals', JoyVals, arm_callback)
    try:
        rospy.spin()
    except rospy.ROSInterruptException: pass

def arm_callback(joy):
    global is_pressed
    buttons_pressed = joy.button_vals
    b = 14
    button_press = b in buttons_pressed
    print is_pressed
    if button_press == True and is_pressed == False:
        is_pressed = True
    elif button_press == False and is_pressed == True:
        print "button released"
        is_pressed = False
        arm_dig_movement()

def arm_dig_movement():
    arm_command='./sendUART2 send "1"'
    os.system(arm_command)
    

if __name__ == '__main__':
    main()
