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

/**
 * The Auton enumerator is an enumerator used to 
 * store all autonomous routine selections. Whenever I
 * write a new autonomous routine, I can just add that
 * option to this enumerator, and then write the necessary
 * selection code in gui.cpp and autonomous.cpp.
 */
enum class Auton
{
    none,
    test
}; 

/**
 * The telemetry structure is a way to package the values of 
 * a few of the telemetry readings from a motor into a single
 * data type that can be passed between classes and used to 
 * display the telemetry for each motor
 */ 
struct Telemetry
{
    double pos;
    double targetPos;
    double velo;
    double targetVelo;
    double temp;
    double torque;
};

#define GEARSET_GREEN okapi::AbstractMotor::gearset::green 
#define GEARSET_RED okapi::AbstractMotor::gearset::red 
#define GEARSET_BLUE okapi::AbstractMotor::gearset::blue 

//The TankDrive object, representing the robot drivetrain
extern TankDrive drive;

//The okapi::Controller object, which represents the robot controller
extern okapi::Controller controller;

//The Auton enumerator used to store the currently selected autonomous routine
extern Auton autonID;