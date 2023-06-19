#include "main.h"

pros::Motor FLD (1, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor MLD (2, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor BLD (3, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor FRD (4, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor MRD (5, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor BRD (6, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);

pros::Motor_Group leftDrive ({FLD, MLD, BLD});
pros::Motor_Group rightDrive ({FRD, MRD, BRD});

int cubeCurve(int in) {
    int out = in*in*in;
    return out/3413.97166667;
}
bool holding = false;
void driveLoop() {
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
    leftDrive.move_velocity(cubeCurve(master.get_analog(ANALOG_LEFT_Y)));
    rightDrive.move_velocity(cubeCurve(master.get_analog(ANALOG_RIGHT_Y)));
}