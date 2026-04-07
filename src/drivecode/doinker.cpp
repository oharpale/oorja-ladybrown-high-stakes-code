#include "main.h"
#include "drivecode/objects.hpp"
#include "lemlib/api.hpp"

pros::adi::DigitalOut doinker(0);
bool doinkerExtended(false);

void updateDoinker(){
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        doinkerExtended = !doinkerExtended;
    }
    if (doinkerExtended == true) {
        doinker.set_value(true);
    }
    if (doinkerExtended == false) {
        doinker.set_value(false);
    }
}