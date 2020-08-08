#pragma once
#include "okapi/api.hpp"

/**
 * The header file for the Chassis class, which is used to create objects that 
 * represent a standard tank drive base design. 
 * 
 * The comments in this header file explain the purpose of each member object or function,
 * while the comments in the respective source file explain the inner workings of each
 * function
 */

//Redefining the okapi gearsets to have a simpler name
#define GREEN okapi::AbstractMotor::gearset::green
#define RED okapi::AbstractMotor::gearset::red
#define BLUE okapi::AbstractMotor::gearset::blue

class Chassis {
    private:
        /**
         * OkapiLib motor group objects. Each one represents one half of the base
         */
        okapi::MotorGroup rightBase;

        okapi::MotorGroup leftBase;
    public:
        /**
         * One of the constructors for a chassis object. This one is for a tank
         * drive with 1 motor powering each side
         * 
         * Parameters:
         * leftMotor: the motor port of the motor on the left side of the base
         * rightMotor: the motor port of the motor on the right side of the base
         * leftReversed: a boolean to indicate if the left motor needs to be reversed
         * rightReversed: a boolean to indicate if the right motor needs to be reversed
         * gearset: the motor gearset used in the motors (it is assumed that both 
         * motors use the same gearset)
         */ 
        Chassis(int leftMotor, int rightMotor, bool leftReversed, bool rightReversed, okapi::AbstractMotor::gearset gearset);
        /** 
         * One of the constructors for a chassis object. This one is for a tank
         * drive with 2 motors powering each side
         * 
         * Parameters:
         * leftFrontMotor: the motor port of the motor on the left side of the base
         * rightFrontMotor: the motor port of the motor on the right side of the base
         * leftBackMotor: the motor port of the motor on the left side of the base
         * rightBackMotor: the motor port of the motor on the right side of the base
         * gearset: the motor gearset used in the motors (it is assumed that both 
         *          motors use the same gearset)
         */ 
        Chassis(int leftFrontMotor, int rightFrontMotor, int leftBackMotor, int rightBackMotor, 
                bool leftFrontReversed, bool rightFrontReversed, bool leftBackReversed, bool rightBackReversed,
                okapi::AbstractMotor::gearset gearset);

        /**
         * The function to control the chassis during the opcontrol period
         * 
         * Parameter:
         * controller: the OkapiLib controller object, which represents the robot controller
         */ 
        void driver(okapi::Controller controller);
};