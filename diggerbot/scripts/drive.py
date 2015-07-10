#!/usr/bin/env python

import rospy
from diggerbot.msg import JoyVals, DriveVals

def main():
    rospy.init_node('drive_controller')
    joy = rospy.Subscriber('joyvals', JoyVals, drive_callback)
    try:
        rospy.spin()
    except rospy.ROSInterruptException:pass

def drive_callback(joy):
    drive_value_pub = rospy.Publisher('drivevals', DriveVals)
    drive_vals = DriveVals()
    
    throttle = joy.joystick_vals[0]
    turn = joy.joystick_vals[1]
    
    speeds = arcade_drive(throttle, turn)
    drive_vals.speeds = speeds
    drive_value_pub.publish(drive_vals)

def arcade_drive(throttle, turn):
    speeds = []
    
    left_speed = throttle + turn
    right_speed = throttle - turn
    
    skimmed_left_speed = left_speed + skim(left_speed)
    skimmed_right_speed = right_speed + skim(right_speed)

    speeds.append(get_arduino_speed(skimmed_left_speed))
    speeds.append(get_arduino_speed(skimmed_right_speed))
    
    return speeds

def skim(speed):
    gain = 0.3

    if speed > 1.0:
        return -((speed - 1.0) * gain)
    elif speed < -1.0:
        return -((speed + 1.0) * gain)
    else:
        return 0.0

def get_arduino_speed(speed):
    return int(255.0*speed)

if __name__ == '__main__':
    main()
