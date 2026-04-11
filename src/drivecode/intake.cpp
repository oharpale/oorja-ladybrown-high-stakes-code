#pragma once
#include "main.h"
#include "drivecode/objects.hpp"
#include "lemlib/api.hpp"
#include "pros/optical.h"
#include "drivecode/intake.hpp"

pros::Motor intake(0);

bool intakeOn(false);
bool intakeReverse(false);

//SORTING VARIABLES
pros::Optical opticSensor(0);
int potentialRing;
pros::c::optical_rgb_s_t colorSpecs;
bool oppositeRing;
int delayBeforeReverse = 0; //tune
int delayAfterReverse = 0; //tune
int ringDistance = 0; //distance of when the ring is present for potential ring
bool hijackDriver = false;
bool resumeIntake = false;

void updateTeam() {
    opticSensor.set_led_pwm(50);
    if (myColor == 0) { //RED
        pros::Task task_teamColorSort([]{
                while (true) {
                    redAlliance();
                    pros::delay(10);
                }
        });
    }
    if (myColor == 1) { //BLUE
        pros::Task task_teamColorSort([]{
                while (true) {
                    blueAlliance();
                    pros::delay(10);
                }
        });
    }
}

void intakeDirection() {
    if (intakeReverse == true) {
        intakeOn = false;
        intake.move_velocity(-600);
    }
    if (intakeOn == true) {
        intakeReverse = false;
        intake.move_velocity(600);
    }
    if ((intakeOn == false) && (intakeReverse == false)) {
        intake.move_velocity(0);
    }
}

void intakeControls() {
    if (hijackDriver == false) {
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
            intakeOn = !intakeOn;
            intakeReverse = false;
        }
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
            intakeOn = false;
            intakeReverse = !intakeReverse;
        }
    }
    if (climbBegins == true) {
        return;
    }
}

void redAlliance() {
    if (hijackDriver == false) {
        potentialRing = opticSensor.get_proximity(); 

        if (potentialRing > ringDistance) { //should be tuned to determine when a ring is present in the intake
            colorSpecs = opticSensor.get_rgb();
            if (colorSpecs.blue > colorSpecs.red) {
                oppositeRing = true;
            }
        }
    }

    if (oppositeRing == true) {
        hijackDriver = true;
        pros::delay(delayBeforeReverse);
       if (intakeOn == true) {
            resumeIntake = true;
            intakeOn = false;
       }
        intakeReverse = true;
        pros::delay(delayAfterReverse);
        intakeReverse = false;
        oppositeRing = false;
        hijackDriver = false;
        if (resumeIntake == true) {
            intakeOn = true;
            resumeIntake = false;
        }
    }
}

void blueAlliance() {
    if (hijackDriver == false) {
        potentialRing = opticSensor.get_proximity(); 

        if (potentialRing > ringDistance) { //should be tuned to determine when a ring is present in the intake
            colorSpecs = opticSensor.get_rgb();
            if (colorSpecs.red > colorSpecs.blue) {
                oppositeRing = true;
            }
        }
    }

    if (oppositeRing == true) {
        hijackDriver = true;
        pros::delay(delayBeforeReverse);
       if (intakeOn == true) {
            resumeIntake = true;
            intakeOn = false;
       }
        intakeReverse = true;
        pros::delay(delayAfterReverse);
        intakeReverse = false;
        oppositeRing = false;
        hijackDriver = false;
        if (resumeIntake == true) {
            intakeOn = true;
            resumeIntake = false;
        }
    }
}
