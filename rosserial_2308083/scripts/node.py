#!/usr/bin/env python

import rospy
from std_msgs.msg import Float16MultiArray
from geometry_msgs.msg import Twist


class node:
    def __init__(self) -> None:
        rospy.init_node("node", anonymous=True)
        self.pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
        rospy.Subscriber("/sensor_data", Float16MultiArray, self.callback)
    def callback(self, info):
        

        array = info.data
        motor_speed = array[0]
        distance = array[1];
        
        
        velocity = Twist()

        if(distance > 20):
            velocity.linear.x = float(motor_speed)
            velocity.angular.z = 0.0;
        
        else:
            velocity.linear.x = 0.0;
            velocity.angular.z = float(motor_speed)
        
        
        try:
            self.pub.publish(velocity)
        except:
            rospy.loginfo("AN ERROR OCCURED")
if __name__=='__main__':
    node = node()
    rospy.spin()