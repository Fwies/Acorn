#include "main.h"

pros::Motor FLD (17, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor MLD (2, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor BLD (13, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor FRD (14, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor MRD (15, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor BRD (16, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);

pros::Motor_Group leftDrive ({FLD, MLD, BLD});
pros::Motor_Group rightDrive ({FRD, MRD, BRD});




int cubeCurve(int in) {
    int mult = 1;
    if (in < 0) {
        mult = -1;
    }
    int out = in*in*in*in;
    return out/433574.401667 * mult;
}
//bool holding = false;
void lock() {
    leftDrive.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
    rightDrive.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
}
void driveLoop() {
    /*
    if (master.get_analog(ANALOG_LEFT_Y) == 0 && master.get_analog(ANALOG_RIGHT_Y) == 0 && FLD.get_actual_velocity() == 0 && FRD.get_actual_velocity() == 0 && !holding) {
        leftDrive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
        rightDrive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
        holding = true;
        master.rumble("-");
    }
    if (master.get_analog(ANALOG_LEFT_Y) != 0 && master.get_analog(ANALOG_RIGHT_Y) != 0 && holding) {
        leftDrive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
        rightDrive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
        holding = false;
        master.rumble(".");
    }
    */

    leftDrive.move_velocity(4.72440944882 * master.get_analog(ANALOG_LEFT_Y));
    rightDrive.move_velocity(4.72440944882 * master.get_analog(ANALOG_RIGHT_Y));

}