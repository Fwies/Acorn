#include "main.h"
pros::Motor fly(7, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_ROTATIONS);
bool flying = false;
void run(){
    if (flying == false) {
        flying = true; 
        fly.move_voltage(12000);
    }
    else {
        flying = false;
        fly.move_voltage(0); 
    }
}
void flyLoop(){
    if(master.get_digital_new_press(DIGITAL_L1)){
        if (flying){
            flying = false;
            fly.move_voltage(0); 
        }
        else{
            flying = true;
            
            fly.move_voltage(12000);
        }
    }
}