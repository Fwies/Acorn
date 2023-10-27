#include "main.h"

pros::Motor intake(20, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_ROTATIONS);

int pressed = 0;
bool going = false;
void flipIntake(){
    if (going){
        going = false;
        intake.move_voltage(0);
    }
    else{
        going = true;
        intake.move_voltage(12000);
    }
}
void intakeLoop(){



    if(master.get_digital_new_press(DIGITAL_R1)){
        if (pressed == 1) {
            pressed=0;
        }
        else{
            pressed = 1;
        }
    }
    if(master.get_digital_new_press(DIGITAL_R2)){
        if (pressed == -1) {
            pressed=0;
        }
        else{
            pressed = -1;
        }
    }
    if (pressed == 1) {
        intake.move_voltage(12000);
    }
    else if (pressed == -1) {
        intake.move_voltage(-12000);
    }
    else {
        intake.move_voltage(0);
    }
    /*
    if(master.get_digital(DIGITAL_R1)){
        intake.move_voltage(12000);
    }
    else if(master.get_digital(DIGITAL_R2)){
        intake.move_voltage(-12000);
    }
    else{
        intake.move_voltage(0);
    }
    */
}