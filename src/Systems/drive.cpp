#include "main.h"
#include <chrono>
#include <cmath>
using namespace std;
using namespace std::chrono;
using namespace okapi;
pros::Motor FLD (17, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor MLD (19, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor SLD (13, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor FRD (14, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor MRD (15, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor SRD (18, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_ROTATIONS);

pros::Motor_Group leftDrive ({FLD, MLD, SLD});
pros::Motor_Group rightDrive ({FRD, MRD, SRD});






lemlib::Drivetrain_t drivetrain {
    &leftDrive, // left drivetrain motors
    &rightDrive, // right drivetrain motors
    10.25, // track width
    3.25, // wheel diameter
    360 // wheel rpm
};
 
// left tracking wheel encoder
pros::Imu inertial_sensor(2); // port 2
 
// odometry struct
lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};
 
// forward/backward PID
lemlib::ChassisController_t lateralController {
    11, // kP11
    1, // kD1
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    1, // kP
    1, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};
 
 
// create the chassis
lemlib::Chassis drive(drivetrain, lateralController, angularController, sensors);


void LEMtestMove() {
  drive.calibrate();
    //drive.turnTo(12, 0, 99999, false, 127);

  drive.moveTo(0, -15, 99999, 127);
  drive.turnTo(12, 0, 900, false, 127);
  drive.setPose(0,0,0);
  drive.moveTo(0, -11, 99999, 50);
  drive.moveTo(0, -5, 99999, 127);
  drive.turnTo(5, -10, 900, false, 127);
  ploy();
  drive.setPose(0,0,0);
  drive.moveTo(0, -12, 99999, 127);
  drive.turnTo(-5, -14.5, 900, false, 127);
  ploy();
  drive.setPose(0,0,0);
  drive.turnTo(10, 10, 900, false, 127);
  drive.moveTo(-19,-19, 99999, 127);
  drive.turnTo(-12, -0, 900, false, 127);
  drive.setPose(0,0,0);
  drive.moveTo(0, -18, 99999, 127);
  drive.turnTo(6, -9, 900, false, 127);
}
void LEMtwo(){
    drive.calibrate();
    //drive.turnTo(12, 0, 99999, false, 127);
    flipIntake(1);
    drive.moveTo(0, 41.5, 99999, 127);
    drive.turnTo(12, 44, 900, false, 127);
    flipIntake(0);
    drive.setPose(0, 0, 0);
    drive.moveTo(0, 15, 1000, 127);
    drive.setPose(0, 0, 0);
    drive.moveTo(0, -23, 99999, 127);
    drive.turnTo(-12, -23, 900, false, 127);
    flipIntake(1);
    drive.moveTo(-13, -23, 99999, 127);
    drive.turnTo(-13, 0, 900, false, 50);
    flipIntake(0);
    drive.moveTo(-13, 3, 1000, 127);
    pros::delay(300);
    drive.setPose(0, 0, 0);
    drive.moveTo(0, -5, 99999, 127);
    drive.turnTo(-0.7, -10, 900, false, 127);
    flipIntake(1);
    drive.moveTo(-0.7, -31, 99999, 200);
    drive.setPose(0, 0, 0);
    drive.turnTo(1, -33, 900, false, 127);
    drive.moveTo(1, -33, 2000, 200);
    flipIntake(0);
    drive.setPose(0, 0, 0);
    drive.moveTo(0, -7, 99999, 200);
    drive.turnTo(7, -14, 900, false, 127);

}

void LEMthree(){
    drive.calibrate();
    //leftDrive.set_brake_mode
    //rightDrive.move_relative(-20, 100);

}



/*std::shared_ptr<ChassisController> chassis = ChassisControllerBuilder()
	.withMotors({17, 19, 13}, {14, 15, 18})
	.withDimensions({okapi::AbstractMotor::gearset::blue * 1.6667}, {{3.25_in, 10.5_in},imev5BlueTPR})
    .withGains(
        {0.003, 0.0, 0.000}, // Distance controller gains p 0.003
        {0.0025, 0.005, 0.000}  // Turn controller gains {0.003, 0.005, 0.0003}
        //{0.005, 0.000, 0.00}
    )
	.build();*/



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
        leftDrive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
        rightDrive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
        holding = true;
        master.rumble(".");
    }
    else {
        leftDrive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
        rightDrive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
        holding = false;
        master.rumble("-");
    }
}
std::uint32_t now = pros::millis();
void driveLoop() {
    now = pros::millis();
    pros::lcd::set_text(2, to_string(FLD.get_raw_position(&now)));
    pros::lcd::set_text(3, to_string(MLD.get_raw_position(&now)));
    pros::lcd::set_text(4, to_string(SLD.get_raw_position(&now)));
    pros::lcd::set_text(5, to_string(FRD.get_raw_position(&now)));
    pros::lcd::set_text(6, to_string(MRD.get_raw_position(&now)));
    pros::lcd::set_text(7, to_string(SRD.get_raw_position(&now)));

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
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
        lock();
    }
    leftDrive.move_velocity(4.72440944882 * master.get_analog(ANALOG_LEFT_Y));
    rightDrive.move_velocity(4.72440944882 * master.get_analog(ANALOG_RIGHT_Y));
    if (master.get_analog(ANALOG_LEFT_X)<-100 && master.get_analog(ANALOG_RIGHT_X)> 100){
        if(ployed()){
            ploy();
        }
        if (!holding){
            lock();
        }
        leftDrive.move_velocity(0);
        rightDrive.move_velocity(0);
        tick();
        spin();
        while(master.get_analog(ANALOG_LEFT_X)<-100 && master.get_analog(ANALOG_RIGHT_X)> 100){
            pros::delay(20);
        }
        run();
        lock();
        ploy();
    }

}
void testMoveDrive() {
    /*chassis->setMaxVelocity(300); 
    flipIntake(-1);
    pros::delay(100);
    chassis->turnAngle(-180_deg);
    pros::delay(100);
    chassis->moveDistance(-2.25_ft);
    chassis->moveDistance(1_ft);*/

}
void testTwo(){
    /*chassis->setMaxVelocity(300);
    chassis->moveDistance(3.35_ft);
    chassis->turnAngle(90_deg);

    leftDrive.move_velocity(400);
    rightDrive.move_velocity(400);
    pros::delay(500);
    leftDrive.move_velocity(0);
    rightDrive.move_velocity(0);
    pros::delay(250);
    //chassis->setMaxVelocity(500);
    //chassis->moveDistance(7_in);
    chassis->setMaxVelocity(300);
    chassis->moveDistance(-1.7_ft);
    chassis->turnAngle(-90_deg);
    flipIntake(1);
    chassis->moveDistance(8_in);
    chassis->turnAngle(90_deg);
    chassis->moveDistance(1.85_ft);
    chassis->moveDistance(-12_in);
    chassis->turnAngle(-180_deg);
    chassis->moveDistance(2_ft);
    chassis->moveDistance(-4_in);
    chassis->turnAngle(-190_deg);
    leftDrive.move_velocity(400);
    rightDrive.move_velocity(400);
    pros::delay(2000);
    leftDrive.move_velocity(0);
    rightDrive.move_velocity(0);*/
} 
void testThree() {
    /*leftDrive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    rightDrive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    // skills
    int i = 0;
    while(i <= 2000){
        flyLoop(true);
        pros::delay(20);
        i++;
        if (i > 1500){
            master.rumble(".");
        }
    }
    run();
    chassis->setMaxVelocity(300);
    //leftDrive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    rightDrive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    rightDrive.move_relative(-260, 150);
    pros::delay(750);
    leftDrive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    chassis->moveDistance(-6.25_ft);
    rightDrive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    leftDrive.move_relative(-1175, 150);
    pros::delay(2000);
    rightDrive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    chassis->moveDistance(-4_ft);
    chassis->turnAngle(135_deg);
    chassis->moveDistance(-3_ft);
    chassis->moveDistance(3_ft);
    chassis->turnAngle(-90_deg);
    chassis->moveDistance(-2_ft);
    chassis->turnAngle(90_deg);
    chassis->moveDistance(-3_ft);*/
}

/*chassis->setMaxVelocity(300);
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
    flipIntake(1);
    chassis->moveDistance(2.85_ft);
    pros::delay(250);
    chassis->setMaxVelocity(200);
    chassis->turnAngle(90_deg);
    chassis->setMaxVelocity(400);
    chassis->moveDistance(1.8_ft);
    flipIntake(-1);*/