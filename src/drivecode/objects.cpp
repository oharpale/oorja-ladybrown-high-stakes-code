#include "main.h"
#include "drivecode/objects.hpp"
#include "lemlib/api.hpp"

/* TEAM ALLIANCE COLOR update before each match
Red: 0
Blue: 1
*/

int myColor = 0;

lemlib::Drivetrain drivetrain(
    &leftMotors,    
    &rightMotors,      
    10,             
    2.75, 
    450,                
    2                      
);

lemlib::ControllerSettings lateralController(
    0, // kP
    0, // kI
    0, // kD
    0, // anti-windup
    0, // small error range
    0, // small error timeout
    0, // large error range
    0, // large error timeout
    0 // max acceleration (slew)
);

lemlib::ControllerSettings angularController(
    0, // kP
    0, // kI
    0, // kD
    0, // anti-windup
    0, // small error range
    0, // small error timeout
    0, // large error range
    0, // large error timeout 
    0 // max acceleration (slew)
);

lemlib::OdomSensors odometrySensors(
    0, //vertical tracking wheel 1
    0, //vertical tracking wheel 2
    0, //horizontal tracking wheel 1
    0, //horizontal tracking wheel 2
    0 //inertial sensor
);

lemlib::Chassis chassis(
    drivetrain, //drivetrain
    lateralController, //lateral PID
    angularController, //angular PID
    odometrySensors
);