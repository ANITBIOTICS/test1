#include "main.h"

	Motor Left1(12);
	Motor Right1(-6);
	Imu inertial(21);





/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}


void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}


void disabled() {}


void competition_initialize() {}


void autonomous() {
	
	drivencoder(5,1.1);	



	// drivetime(100,300);
	// delay(1000);
	// turntime(100,170);
	// delay(1000);
	// drivetime(100,300);
	// delay(1000);
	// turntime(100,170);
	// delay(1000);
	// drivetime(100,300);
	// delay(1000);
	// turntime(100,170);
	// delay(1000);
	// drivetime(100,300);
}



/**                  void autonomous() {
	drivetime()
	turntime()
}
                                                         
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	Controller master(E_CONTROLLER_MASTER);

	while (true) {
		int forward = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_LEFT_X);

		Powerdrive(forward, turn);

		if(master.get_digital(DIGITAL_B))	{
			autonomous();
		}


		delay(20); // Run for 20 ms then update
	}
}