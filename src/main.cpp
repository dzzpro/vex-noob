/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\james                                            */
/*    Created:      Thu Sep 30 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Motor1               motor         1               
// Motor2               motor         2               
// Motor3               motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
const double radius=0.4;
const double theta1=M_PI/3.0,theta2=M_PI/6.0;
double gear=100;
const double nonlinerlizeParm = 0.5;//almost liner
const double deadband=0.05;
double normalize(double Value,double range){
  return Value/range;
}
//Value normalized
double dedeadband(double Value){
  return fmax(Value-deadband,0)/(1-deadband);
}
double nonlinerlize(double Value){
  return sin(M_PI/2*nonlinerlizeParm*Value)/sin(M_PI/2*nonlinerlizeParm);
}
void DriveChasis(double Vx, double Vy, double rotate){
  double speed1,speed2,speed3;
  speed1=Vx+rotate*radius;
  speed2=-Vx*cos(theta1)-Vy*sin(theta1)+rotate*radius;
  speed3=-Vx*sin(theta2)+Vy*cos(theta2)+rotate*radius;
  Motor1.spin(directionType::fwd, speed3*gear, velocityUnits::pct);
  Motor2.spin(directionType::fwd, speed1*gear, velocityUnits::pct);
  Motor3.spin(directionType::fwd, speed2*gear, velocityUnits::pct);
}
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(true){
    double Vx, Vy, rotate;
    Vx=Controller1.Axis4.value();
    Vy=Controller1.Axis3.value();
    rotate=Controller1.Axis1.value();
    Vx=nonlinerlize(normalize(Controller1.Axis4.value(),128.0));
    Vy=nonlinerlize(normalize(Controller1.Axis3.value(),128.0));
    rotate=nonlinerlize(normalize(Controller1.Axis1.value(),128.0));
    if(Controller1.ButtonL1.pressing()) gear=50.0; else gear=100.0; 
    DriveChasis(Vx,Vy,rotate);
  }
}
