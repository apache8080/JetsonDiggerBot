#include <ros.h>
#include <diggerbot/DriveVals.h>
#include <std_msgs/String.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"


Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *leftMotor1 = AFMS.getMotor(2);
Adafruit_DCMotor *leftMotor2 = AFMS.getMotor(3);
Adafruit_DCMotor *rightMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor2 = AFMS.getMotor(4);

ros::NodeHandle  nh;
std_msgs::String msg;
ros::Publisher pub("arduinoval", &msg);
boolean leftIsReverse, rightIsReverse;

void drive_motors( const diggerbot::DriveVals& cmd_msgs){
  int leftSpeed = cmd_msgs.speeds[0];
  int rightSpeed = cmd_msgs.speeds[1];
  if(leftSpeed<0){
    leftMotor1->setSpeed(abs(leftSpeed));
    leftMotor2->setSpeed(abs(leftSpeed));
    leftMotor1->run(FORWARD);
    leftMotor2->run(FORWARD);
    leftIsReverse = true;
  }else{
    leftMotor1->setSpeed(abs(leftSpeed));
    leftMotor2->setSpeed(abs(leftSpeed));
    leftMotor1->run(BACKWARD);
    leftMotor2->run(BACKWARD);
    leftIsReverse = false;
  }
  if(rightSpeed<0){
    rightMotor1->setSpeed(abs(rightSpeed));
    rightMotor2->setSpeed(abs(rightSpeed));
    rightMotor1->run(BACKWARD);
    rightMotor2->run(BACKWARD);
    rightIsReverse=true;
  }else{
    rightMotor1->setSpeed(abs(rightSpeed));
    rightMotor2->setSpeed(abs(rightSpeed));
    rightMotor1->run(FORWARD);
    rightMotor2->run(FORWARD);
    rightIsReverse=false;
  }
}


ros::Subscriber<diggerbot::DriveVals> sub("drivevals", drive_motors);


void setup(){
  //pinMode(13, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);
  //servo.attach(9); //attach it to pin 9
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  leftMotor1->setSpeed(0);
  leftMotor1->run(FORWARD);
  leftMotor2->setSpeed(0);
  leftMotor2->run(FORWARD);
  rightMotor1->setSpeed(0);
  rightMotor1->run(FORWARD);
  rightMotor2->setSpeed(0);
  rightMotor2->run(FORWARD);
  // turn on motor
  leftMotor1->run(RELEASE);
  leftMotor2->run(RELEASE);
  rightMotor1->run(RELEASE);
  rightMotor2->run(RELEASE);
}

void loop(){
  if(leftIsReverse && rightIsReverse){
    msg.data = "Reverse";
    pub.publish(&msg);
  }else if(!leftIsReverse && rightIsReverse){
    msg.data = "Right Turn";
    pub.publish(&msg);
  }else if(leftIsReverse && !rightIsReverse){
    msg.data = "Left Turn";
    pub.publish(&msg);
  }else{
    msg.data = "Forward";
    pub.publish(&msg);
  }
  nh.spinOnce();
  delay(1);
}

