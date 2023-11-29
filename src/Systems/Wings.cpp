#include "main.h"
pros::ADIDigitalOut piston (8);
bool deployed = true;
void wingLoop(){
    if (master.get_digital_new_press(DIGITAL_L2)){
        piston.set_value(deployed);
        deployed = !deployed;
    }
}