#pragma once
#include "main.h"
#include "drivecode/objects.hpp"
#include "lemlib/api.hpp"

pros::adi::DigitalOut clampLeft(0);
pros::adi::DigitalOut clampRight(0);
bool clampOn(false);

//pistons extend when clamp is in use

void updateClamp(){
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        clampOn = !clampOn;
        clampLeft.set_value(clampOn);
        clampRight.set_value(clampOn);
    }
    if (climbBegins == true) {
        return;
    }
}