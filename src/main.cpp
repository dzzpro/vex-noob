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
const double radius=1.0;
const double theta1=M_PI/3.0,theta2=M_PI/6.0;
void DriveChasis(double Vx, double Vy, double rotate){
  double speed1,speed2,speed3;
  speed1=Vx+rotate*radius;
  speed2=-Vx*cos(theta1)-Vy*sin(theta1)+rotate*radius;
  speed3=-Vx*sin(theta2)+Vy*cos(theta2)+rotate*radius;
  Motor1.spin(directionType::fwd, speed3, velocityUnits::rpm);
  Motor2.spin(directionType::fwd, speed1, velocityUnits::rpm);
  Motor3.spin(directionType::fwd, speed2, velocityUnits::rpm);
  return;
}
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(true){
    double Vx, Vy, rotate;
    Vx=Controller1.Axis4.value();
    Vy=Controller1.Axis3.value();
    rotate=Controller1.Axis1.value();
    DriveChasis(Vx,Vy,rotate);
  }
}
