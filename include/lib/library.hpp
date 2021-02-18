#pragma once
/**
 * library.hpp includes a few type definitions 
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
    skills,
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

