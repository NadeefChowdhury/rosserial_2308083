#include <ros.h>
#include <geometry_msgs/Twist.h>

// Motor A connections
const int enA = 4;  
const int in1 = 2;
const int in2 = 3;
 
// Motor B connections
const int enB = 7; 
const int in3 = 5;
const int in4 = 6;
 
ros::NodeHandle nh;
void motor_callback( const geometry_msgs::Twist& cmd_msg){
 velocity =  cmd_msg.linear.x;
 rotate = cmd_msg.angular.z;
 analogWrite(enA, velocity*255);
 analogWrite(enB, velocity*255);
 if(velocity > 0){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  }
 if(velocity < 0){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  }
 if(velocity == 0){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  }
 if(rotate > 0){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
 }
 if(rotate < 0){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
 }
}

ros::Subscriber<geometry_msgs::Twist> motor_sub("/cmd_vel", motor_callback);
 
void setup() {
  Serial.begin(9600);
  // Motor control pins are outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
 
  nh.initNode();
  nh.subscribe(motor_sub);

  Serial.begin(9600);
}
 
void loop() {
 nh.spinOnce();

 
}
