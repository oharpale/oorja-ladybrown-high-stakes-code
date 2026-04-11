#pragma once
#include "main.h"
#include "lemlib/api.hpp"

extern pros::Optical opticSort;

extern pros::Motor intake;

void updateTeam();
void redAlliance();
void blueAlliance();
void intakeDirection();
void intakeControls();