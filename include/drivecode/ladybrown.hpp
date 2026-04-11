#pragma once
#include "main.h"
#include "lemlib/api.hpp"

extern pros::MotorGroup ladybrown;

void updateLadybrownControls();
void updateLadybrownPID();

extern int target;