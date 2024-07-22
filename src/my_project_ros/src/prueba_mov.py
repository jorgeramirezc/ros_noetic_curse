#!/usr/bin/env python3
"""
Script to move a differential mobile robot in a circle
"""
import rospy
from geometry_msgs.msg import Twist

def move_circle():
  
  rospy.init_node("movement", anonymous=True)

  # Create a publisher which can publish messages and move the robot
  pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
  
  # Create a Twist message and add linear x and angular z values
  move_cmd = Twist()
  move_cmd.linear.x = 1.0
  move_cmd.angular.z = 1.0
  
  # Save current time and set publish rate at 10 Hz
  now = rospy.Time.now()
  rate = rospy.Rate(10)
  
  # For the next 6 seconds publish cmd_vel move commands 
  #while not rospy.is_shutdown():
  while rospy.Time.now() < now + rospy.Duration.from_sec(6):
    pub.publish(move_cmd)
    rate.sleep()
  
  move_cmd.linear.x = 0.0
  move_cmd.angular.z = 0.0 
  
  
    
if __name__ == '__main__':
  try:
    move_circle()
  except rospy.ROSInterruptException:
    pass
