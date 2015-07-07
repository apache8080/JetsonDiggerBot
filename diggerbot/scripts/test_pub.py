#!/usr/bin/env python
import rospy
from std_msgs.msg import String

def main():
    rospy.init_node('test_talker', anonymous='True')
    pub = rospy.Publisher('hello', String)
    while True:
        try:
            hello_str = 'hello world'
            pub.publish(hello_str)
        except EOFError:
            print
            return

if __name__ == '__main__':
    main()
