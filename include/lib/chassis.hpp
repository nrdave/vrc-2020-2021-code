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
         * OkapiLib motor group objects. Each one represents the 
         * motor(s) on one side of the base
         */
        okapi::MotorGroup rightBase;

        okapi::MotorGroup leftBase;

        /**
         * Variable to store the diameter of the wheel
         * This value is used to convert values passed in for
         * autonomous functions from inches to degrees to rotate for
         */ 
        float wheelDiameter;
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
         * wD: the diameter of the wheels used
         */ 
        Chassis(int leftMotor, int rightMotor, bool leftReversed, bool rightReversed, 
                okapi::AbstractMotor::gearset gearset, float wD);
        /** 
         * One of the constructors for a chassis object. This one is for a tank
         * drive with 2 motors powering each side
         * 
         * Parameters:
         * leftFrontMotor: the motor port of the motor on the left side of the base
         * rightFrontMotor: the motor port of the motor on the right side of the base
         * leftBackMotor: the motor port of the motor on the left side of the base
         * leftFrontReversed: a boolean to indicate if the left front motor needs to be reversed
         * rightFrontReversed: a boolean to indicate if the right front motor needs to be reversed
         * leftBackReversed: a boolean to indicate if the left back motor needs to be reversed
         * rightBackReversed: a boolean to indicate if the right back motor needs to be reversed         
         * rightBackMotor: the motor port of the motor on the right side of the base
         * gearset: the motor gearset used in the motors (it is assumed that both 
         *          motors use the same gearset)
         * wD: the diameter of the wheels used
         */ 
        Chassis(int leftFrontMotor, int rightFrontMotor, int leftBackMotor, int rightBackMotor, 
                bool leftFrontReversed, bool rightFrontReversed, 
                bool leftBackReversed, bool rightBackReversed,
                okapi::AbstractMotor::gearset gearset, float wD);

        /**
         * The driver function allows control of the chassis during the opcontrol period,
         * with each side of the base bound to one of the controller joysticks
         * 
         * Parameter:
         * controller: the OkapiLib controller object, which represents the robot controller
         */ 
        void driver(okapi::Controller controller);

        /**
         * The chassisPID function is a PID controller for the base. It sets each side of 
         * the base to move a specified length. It is used as the base for all autonomous 
         * functions. Individual functions conduct any calculations needed to get the 
         * needed target values before passing those values into chassisPID. This means
         * that the PID controller for the chassis need only be tuned once, but used in all
         * autonomous functions
         * 
         * Parameters:
         * leftTarg: The target length to move to, in inches, for the left side of the base
         *           Can be negative to indicate rotating backwards
         * rightTarg: The target length to move to, in inches, for the right side of the base
         *           Can be negative to indicate rotating backwards
         * maxVelo: The maximum velocity each motor group can reach. Used to limit the robot's
         *          speed in autonomous, to minimize overshooting
         */
        void chassisPID(float leftTarg, float rightTarg, int maxVelo); 
};