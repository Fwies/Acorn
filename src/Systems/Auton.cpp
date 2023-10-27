#include "main.h"
using namespace okapi;
pros::ADIPotentiometer potentiometer (8);
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
	/*chassis.set_slew_min_power(80, 80);
  	chassis.set_slew_distance(7, 7);
 	chassis.set_pid_constants(&chassis.headingPID, 0, 0, 0, 0);
  	chassis.set_pid_constants(&chassis.forward_drivePID, 1, 0, 0, 0);
  	chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 0, 0);
  	chassis.set_pid_constants(&chassis.turnPID, 5, 0.00, 0, 0);
  	chassis.set_pid_constants(&chassis.swingPID, 7, 0, 0, 0); */
}
void testMove() {
}