#include "main.h"
using namespace okapi;

// forward/backward PID


lemlib::Drivetrain_t drivetrain {
    &leftDrive, // left drivetrain motors
    &rightDrive, // right drivetrain motors
    10.25, // track width
    3.25, // wheel diameter
    360 // wheel rpm
};

// left tracking wheel encod
 
// left tracking wheel
 
// inertial sensor
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
    3, // kP
    1, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};

// turning PID
lemlib::ChassisController_t angularController {
    01, // kP
    0, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    40 // slew rate
};
 

// create the chassis

lemlib::Chassis drive(drivetrain, lateralController, angularController, sensors);


/*std::shared_ptr<ChassisController> chassis = ChassisControllerBuilder()
	.withMotors({17,19, 13}, {14, 15, 16})
	.withDimensions({okapi::AbstractMotor::gearset::blue*0.1}, {{3.25_in, 10.5_in},imev5BlueTPR})
	.build();*/
	

/*Drive Chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-17, -2, -13}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{14, 15, 16}

  // IMU Port
  ,9

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  ,3.25

  // Cartridge RPM
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,0.3
);*/

void autonInit(){
  
  drive.calibrate(); // calibrate the chassis
  //inertial_sensor.reset(true);
  drive.setPose(0, 0, 0);
	
}
void testMove() {
  
  drive.turnTo(30, 0, 9999, 50);
}