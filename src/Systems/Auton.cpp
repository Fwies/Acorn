#include "main.h"
using namespace okapi;

lemlib::Drivetrain_t drivetrain {
    &leftDrive, // left drivetrain motors
    &rightDrive, // right drivetrain motors
    10.25, // track width
    3.25, // wheel diameter
    360 // wheel rpm
};
 
// left tracking wheel encoder
pros::Imu inertial_sensor(6); // port 2
 
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
    1, // kP11
    0, // kD0
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    2 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    1, // kP
    0, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    40 // slew rate
};
 
 
// create the chassis
lemlib::Chassis drive(drivetrain, lateralController, angularController, sensors);

void autonInit(){
}
void testMove() {
  drive.calibrate();
  drive.turnTo(30, 0, 99999,false, 30);
}