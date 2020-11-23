#pragma once
#include "okapi/api.hpp"

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

double roundDouble(double input, int places);

#define GEARSET_GREEN okapi::AbstractMotor::gearset::green 
#define GEARSET_RED okapi::AbstractMotor::gearset::red 
#define GEARSET_BLUE okapi::AbstractMotor::gearset::blue 