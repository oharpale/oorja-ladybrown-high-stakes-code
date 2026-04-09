#include "main.h"
#include "drivecode/objects.hpp"
#include "lemlib/api.hpp"
#include "drivecode/ladybrown.hpp"
#include "drivecode/objects.hpp"
#include "drivecode/tier3.hpp"

pros::adi::DigitalOut ptoPiston(0);
int armDriveVelocity = 0;

pros::adi::DigitalOut towerSupportLeft(0);
pros::adi::DigitalOut towerSupportRight(0);
bool towersExtended = false;

void updateTier3() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        startTier3();
    }
}

enum climbStates{initiate, tier1, tiers23, end};
climbStates currentClimbState = tier1;

/*lbClimbAngles:
0: after pulling bot up when arm is idle
15: to rest for passive hook hang
30: to pull for tier 1
120: to pull for tiers 2 and 3
*/

//expand is positive
int idleClimbAngle = 0;
int restPassiveHookAngle = 15;
int pullTier1 = 30;
int pullTiers23 = 120;

int currentTier = 0;
bool climbBegins = false;


void startTier3() {
    switch(currentClimbState) {
        case initiate:
            ptoPiston.set_value(false);
            climbTowers();
            climbDrive();
            currentClimbState = tier1;
            climbBegins = true;
            break;
        case tier1:
            currentTier += 1;
            towersExtended = true;
            armDriveVelocity = 600;
            target = pullTier1;
            pros::delay(10);
            armDriveVelocity = -600;
            target = idleClimbAngle;
            pros::delay(10);
            towersExtended = false;
            armDriveVelocity = 600;
            target = restPassiveHookAngle;
            pros::delay(10);
            armDriveVelocity = 0;
            currentClimbState = tiers23;
            break;
        case tiers23:
            currentTier += 1;
            while (currentTier < 4) {
                towersExtended = true;
                armDriveVelocity = 600;
                target = pullTiers23;
                pros::delay(10);
                armDriveVelocity = -600;
                target = idleClimbAngle;
                pros::delay(10);
                towersExtended = false;
                armDriveVelocity = 600;
                target = restPassiveHookAngle;
                pros::delay(10);
                armDriveVelocity = 0;
                currentTier +=1;
            }
            currentClimbState = end;
            break;
        case end:
            break;
    }
    return;
}

void climbTowers() {
    towerSupportLeft.set_value(towersExtended);
    towerSupportRight.set_value(towersExtended);
}

void climbDrive() {
    leftMotors.move_velocity(armDriveVelocity);
    rightMotors.move_velocity(armDriveVelocity);
}