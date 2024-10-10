#include <ros.h>
#include <std_msgs/Float16MultiArray.h>

ros::NodeHandle  nh;

std_msgs::Float16MultiArray sensor_array;
ros::Publisher pub( "/sensor_data", &sensor_array);

int initial_array;

int pot_pin = 5;
int trig = 2;
int echo = 4;

long duration;
int distance;
void setup()
{
  pinMode(pot_pin, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  nh.initNode();
  nh.advertise(pub);
  
  Serial.begin(9600);
  
}




void loop()
{
  pot_value = analogRead(pot_pin);
  pot_input = map(pot_value, 0, 1023, 0, 1);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  duration = pulseIn(echo, HIGH);
  
  distance = duration * 0.034 / 2;
  initial_array = [pot_input, distance];
  sensor_array.data = initial_array;
  pub.publish( &sensor_array );

  nh.spinOnce();
}
