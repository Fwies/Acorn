#include "main.h"
pros::Motor fly(8, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
bool flying = false;
void run(){
    if (flying == false) {
        flying = true; 
        fly.move_velocity(570);
    }
    else {
        flying = false;
        fly.move_voltage(0); 
    }
}
void spin(){
    fly.move_velocity(570);
    flying = true;
}
bool ticked = false;
void tick(){
    if (!ticked){
        
        ticked = true;
        fly.move_relative(-0.5, 50);
        pros::delay(400);
    }
}
void flyLoop(bool go){
    pros::lcd::set_text(0, to_string(fly.get_voltage()));
    if (go){
        flying = true;
    }
    if (flying){
        fly.move_velocity(570);
    }

    if(master.get_digital_new_press(DIGITAL_L1)){
        if (ticked){
            if (flying){
                flying = false;
                fly.move_voltage(0); 
                master.rumble("-");
            }
            else{
                flying = true;
                master.rumble(".");
                //fly.move_velocity(-530);
            }
        }
        else {
            master.rumble(".-");
        }
    }
    if(master.get_digital_new_press(DIGITAL_Y) && !ticked){
        master.rumble(".");
        ticked = true;
        fly.move_relative(-0.5, 50);
    }
}