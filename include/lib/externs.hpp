#pragma once
#include "okapi/api.hpp"
#include "lib/TankDrive.hpp"

/**
 * This header file contains declarations for objects and
 * values that are accessed in multiple files. For example,
 * the autonID enumerator is used in gui and autonomous, so
 * it must be declared with the extern keyword so that it is
 * initialized in the global scope.
 */

//The TankDrive object, representing the robot drivetrain
extern TankDrive drive;

//The okapi::Controller object, which represents the robot controller
extern okapi::Controller controller;

//The Auton enumerator used to store the currently selected autonomous routine
extern Auton autonID;