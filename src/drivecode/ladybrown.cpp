#include "main.h"
#include "drivecode/objects.hpp"
#include "lemlib/api.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "drivecode/ladybrown.hpp"

pros::MotorGroup ladybrown({0,-0},pros::MotorGearset::red);
pros::Rotation lbRotation(0);

const int numStates = 3;
int states[numStates] = {0, 30, 180};
int currentState = states[0];
int target = states[0];

//PID variables
double lb_kP = 0;
double lb_kD = 0;
double lb_kI = 0;
double lb_windUpRange = 0;
double lb_prevError = 0;
double lb_derivative = 0;
double lb_accumulatedError = 0;

/* State Details:
0: 0 degrees for resting position
1: 30 degrees for loading position
2: 180 degrees for scoring position

Note: the ladybrown starts at the resting position

CONTROLS:
R1 - 
R2 - immediately return ladybrown to resting position

*/
void updateLadybrownPID() {
    double lb_error = target - lbRotation.get_position();
    
    lb_derivative = lb_error - lb_prevError;
    lb_prevError = lb_error;

    if (abs(lb_error) < lb_windUpRange) {
        lb_accumulatedError += lb_error;
    }
    else {
        lb_accumulatedError = 0;
    }

    double lb_velocity = ((lb_kP * lb_error) + (lb_kD * lb_derivative) + (lb_kI * lb_accumulatedError));
    ladybrown.move(lb_velocity);
}

void updateLadybrownControls() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
        target = states[0];
    }
}