#pragma once
#include "lib/TankDrive.hpp"
#include "lib/intake.hpp"
#include "lib/Conveyor.hpp"

/**
 * This header file contains declarations for objects and
 * values that are accessed in multiple files. For example,
 * the autonID enumerator is used in gui and autonomous, so
 * it must be declared with the extern keyword so that it is
 * initialized in the global scope.
 */

//The TankDrive object, representing the robot drivetrain
extern TankDrive drive;

//The Intake object, representing the robot's intakes
extern Intake intake;

//The Conveyor object, representing the conveyor that moves balls up and scores them
extern Conveyor conveyor;

//The Auton enumerator used to store the currently selected autonomous routine
extern Auton autonID;