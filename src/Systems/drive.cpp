#include "main.h"

pros::Motor FLD (1, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor MLD (2, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor BLD (3, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor FRD (4, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor MRD (5, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor BRD (6, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);

pros::Motor_Group leftDrive ({FLD, MLD, BLD});
pros::Motor_Group rightDrive ({FRD, MRD, BRD});

int curve(int in) {
    int out = in*in*in;
    return out/3413.97166667;
}

void driveLoop() {
    leftDrive.move_velocity(curve(master.get_analog(ANALOG_LEFT_Y)));
    rightDrive.move_velocity(curve(master.get_analog(ANALOG_RIGHT_Y)));
}