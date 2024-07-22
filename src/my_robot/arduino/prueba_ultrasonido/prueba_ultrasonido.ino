#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
//#define USE_USBCON

ros::NodeHandle nh;

sensor_msgs::Range range_msg;
ros::Publisher pub_range("/ultrasound",&range_msg);

int trigger_pin = 9;
int echo_pin = 12;


long range_time;
char frameid[] = "/ultrasound";


void setup() {
  nh.initNode();
  nh.advertise(pub_range);
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 0.1;  
  range_msg.min_range = 0.0;
  range_msg.max_range = 6.47;
}

void loop()
{
  if ( millis() >= range_time ){ 
      range_msg.range = getRange() / 100;
      range_msg.header.stamp = nh.now();
      pub_range.publish(&range_msg);
      range_time =  millis() + 50;
    }    
    nh.spinOnce();
}

long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29.1 / 2;
}

float getRange()
{
  long duration;
  
  //PING is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigger_pin, OUTPUT);
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echo_pin, INPUT);
  duration = pulseIn(echo_pin, HIGH);
  
  // convert the time into a distance
  return microsecondsToCentimeters(duration);
}
