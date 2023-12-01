#include "main.h"
pros::Motor fly(8, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
bool flying = false;
void run(){
    if (flying == false) {
        flying = true; 
        fly.move_velocity(-470);
    }
    else {
        flying = false;
        fly.move_voltage(0); 
    }
}
void flyLoop(bool go){
    pros::lcd::set_text(0, to_string(fly.get_voltage()));
    if (go){
        flying = true;
    }
    if (flying){
        fly.move_velocity(-470);
    }
    else{
        fly.move_velocity(0);
    }
    if(master.get_digital_new_press(DIGITAL_L1)){
        if (flying){
            flying = false;
            //fly.move_voltage(0); 
        }
        else{
            flying = true;
            
            //fly.move_velocity(-530);
        }
    }
}