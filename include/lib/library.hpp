#pragma once
#include "okapi/api.hpp"
/**
 * library.hpp includes a few type definitions, as well as macros, 
 * that I use throughout my code.
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
    test,
    midleft,
    midright,
    left,
    right
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

//Creating macros for the motor gearsets
#define GEARSET_GREEN okapi::AbstractMotor::gearset::green 
#define GEARSET_RED okapi::AbstractMotor::gearset::red 
#define GEARSET_BLUE okapi::AbstractMotor::gearset::blue 

//Creating macros for Controller buttons
//Trigger button macros
#define CONTROLLER_L1 okapi::ControllerDigital::L1
#define CONTROLLER_L2 okapi::ControllerDigital::L2
#define CONTROLLER_R1 okapi::ControllerDigital::R1
#define CONTROLLER_R2 okapi::ControllerDigital::R2
//A-B-X-Y Macros
#define CONTROLLER_A okapi::ControllerDigital::A
#define CONTROLLER_B okapi::ControllerDigital::B
#define CONTROLLER_X okapi::ControllerDigital::X
#define CONTROLLER_Y okapi::ControllerDigital::Y
//D-Pad macros
#define CONTROLLER_DPAD_UP okapi::ControllerDigital::up
#define CONTROLLER_DPAD_DOWN okapi::ControllerDigital::down
#define CONTROLLER_DPAD_LEFT okapi::ControllerDigital::left
#define CONTROLLER_DPAD_RIGHT okapi::ControllerDigital::right
//Joystick Macros
#define CONTROLLER_JOYSTICK_LEFT_Y okapi::ControllerAnalog::leftY
#define CONTROLLER_JOYSTICK_LEFT_X okapi::ControllerAnalog::leftX
#define CONTROLLER_JOYSTICK_RIGHT_Y okapi::ControllerAnalog::rightY
#define CONTROLLER_JOYSTICK_RIGHT_X okapi::ControllerAnalog::rightX

