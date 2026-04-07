#include "main.h"
#include "lemlib/api.hpp"

extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;
extern pros::Motor intake;

extern pros::adi::DigitalOut doinker;

extern lemlib::Drivetrain drivetrain;
extern lemlib::Chassis chassis;

extern pros::Controller controller;

void updateClamp();
void updateDoinker();

