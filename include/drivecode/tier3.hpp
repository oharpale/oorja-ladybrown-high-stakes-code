#pragma once
#include "main.h"
#include "lemlib/api.hpp"

extern pros::adi::DigitalOut ptoPiston;
extern pros::adi::DigitalOut towerSupportLeft;
extern pros::adi::DigitalOut towerSupportRight;


void updateTier3();
void startTier3();
void climbTowers();
void climbDrive();