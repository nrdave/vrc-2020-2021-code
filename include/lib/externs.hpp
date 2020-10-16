#pragma once
#include "okapi/api.hpp"
#include "lib/chassis.hpp"

/**
 * This header file contains declarations for objects and
 * values that are accessed in multiple files. For example,
 * the Chassis class is used in opcontrol and autonomous, so
 * it must be declared with the extern keyword so that it is
 * initialized in the global scope.
 */ 

/**
 * #define statements for the autonID values, used to improve
 * readability. 
 */ 

//The autonID value to indicate not to run an autonomous routine
#define AUTON_NONE 0
//The autonID value for running a test autonomous routine
#define AUTON_TEST 1
/**
 * These autonID values all follow a pattern:
 * AUTON_<color>_<side>_<number of goals to score on>
 */ 
#define AUTON_BLUE_LEFT_1GOAL 2
#define AUTON_BLUE_LEFT_2GOAL 3
#define AUTON_BLUE_RIGHT_1GOAL 4
#define AUTON_BLUE_RIGHT_2GOAL 5
#define AUTON_RED_LEFT_1GOAL 6
#define AUTON_RED_LEFT_2GOAL 7
#define AUTON_RED_RIGHT_1GOAL 8
#define AUTON_RED_RIGHT_2GOAL 9

//The Chassis object, representing the robot drivetrain
extern Chassis chassis;

//The okapi::Controller object, which represents the robot controller
extern okapi::Controller controller;

//The variable used to store the ID of the currently selected autonomous
extern int autonID;