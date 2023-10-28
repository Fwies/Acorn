#include "main.h"
#include <chrono>
#include <cmath>
using namespace std;
using namespace std::chrono;
using namespace okapi;
pros::Motor FLD (17, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor MLD (19, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor BLD (13, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor FRD (14, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor MRD (15, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor BRD (16, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);

pros::Motor_Group leftDrive ({FLD, MLD, BLD});
pros::Motor_Group rightDrive ({FRD, MRD, BRD});

std::shared_ptr<ChassisController> chassis = ChassisControllerBuilder()
	.withMotors({17,19, 13}, {14, 15, 16})
	.withDimensions({okapi::AbstractMotor::gearset::blue * 1.6667}, {{3.25_in, 10.5_in},imev5BlueTPR})
    .withGains(
        {0.003, 0.0, 0.000}, // Distance controller gains
        {0.0025, 0.005, 0.000}  // Turn controller gains
    )
	.build();



int cubeCurve(int in) {
    int mult = 1;
    if (in < 0) {
        mult = -1;
    }
    int out = in*in*in*in;
    return out/433574.401667 * mult;
}
bool holding = false;
void lock() {
    if (holding == false){
        leftDrive.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
        rightDrive.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
        holding = true;
    }
    else {
        leftDrive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
        rightDrive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
        holding = false;
    }
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
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
        lock();
    }
    leftDrive.move_velocity(4.72440944882 * master.get_analog(ANALOG_LEFT_Y));
    rightDrive.move_velocity(4.72440944882 * master.get_analog(ANALOG_RIGHT_Y));

}
void testMoveDrive() {
    chassis->setMaxVelocity(300);
    //chassis->moveDistance(3_ft);
    //flipIntake();
    chassis->turnAngle(40_deg);
    chassis->moveDistance(2.5_ft);
    chassis->turnAngle(-40_deg);
    chassis->moveDistance(7_in);
    pros::delay(250);
    chassis->moveDistance(-9_in);
    chassis->turnAngle(-90_deg);
    chassis->moveDistance(3_ft);
    chassis->turnAngle(90_deg);
    flipIntake();
    chassis->moveDistance(2.85_ft);
    pros::delay(250);
    chassis->setMaxVelocity(200);
    chassis->turnAngle(90_deg);
    chassis->setMaxVelocity(400);
    chassis->moveDistance(1.8_ft);
    flipIntake();
}
void testTwo(){
    // other auton
}