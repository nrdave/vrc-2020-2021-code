#include "main.h"

okapi::Controller controller;
TankDrive drive(13, 11, 10, 3, false, true, false, true, GEARSET_GREEN, 4, 12.75, 60, 0.05, 50);
Intake intake(19, 12, false, true, CONTROLLER_L1, CONTROLLER_L2);
Conveyor conveyor(15, true, GEARSET_GREEN, CONTROLLER_R1, CONTROLLER_R2);
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() 
{
    GUI::initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}