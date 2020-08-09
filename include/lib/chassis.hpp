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

        /**
         * The chassisPID function is a PID controller for the base. It sets each side of 
         * the base to move a specified length. It is used as the base for all autonomous 
         * functions. Individual functions conduct any calculations needed to get the 
         * needed target values before passing those values into chassisPID. This means
         * that the PID controller for the chassis need only be tuned once
         * 
         * Parameters:
         * leftTarg: The target length to move to, in inches, for the left side of the base
         *           Can be negative to indicate rotating backwards
         * rightTarg: The target length to move to, in inches, for the right side of the base
         *           Can be negative to indicate rotating backwards
         * maxSpeed: the maximum speed the chassis motors can run at (in RPM)
         */
        void chassisPID(float leftTarg, float rightTarg, int maxSpeed); 

        /**
         * The PID constant values, kP for the proportional constant,
         * kI for the integral constant, and kD for the derivative constant
         */ 
        float kP;
        float kI;
        float kD;
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
         * Pconst: the value of the proportional constant in the PID controller
         * Iconst: the value of the integral constant in the PID controller
         * Dconst: the value of the derivative constant in the PID controller
         */ 
        Chassis(int leftMotor, int rightMotor, bool leftReversed, bool rightReversed, 
                okapi::AbstractMotor::gearset gearset, float wheelD, float Pconst, float Iconst, float Dconst);
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
         * Pconst: the value of the proportional constant in the PID controller
         * Iconst: the value of the integral constant in the PID controller
         * Dconst: the value of the derivative constant in the PID controller
         */ 
        Chassis(int leftFrontMotor, int rightFrontMotor, int leftBackMotor, int rightBackMotor, 
                bool leftFrontReversed, bool rightFrontReversed, 
                bool leftBackReversed, bool rightBackReversed,
                okapi::AbstractMotor::gearset gearset, float wD, 
                float Pconst, float Iconst, float Dconst);

        /**
         * The driver function allows control of the chassis during the opcontrol period,
         * with each side of the base bound to one of the controller joysticks
         * 
         * Parameter:
         * controller: the OkapiLib controller object, which represents the robot controller
         */ 
        void driver(okapi::Controller controller);



        /**
         * The setVelocity function manually sets the velocity of each motor group. This has 2 main
         * use cases:
         * 1. More convenient setting of motor group velocities in Chassis member functions
         * 2. In the case of extreme emergency (i.e. all autonomous code has broken for some
         *    reason and the team has a match soon), setVelocity can be used to manually
         *    control the motors in a timer-based autonomous.
         * 
         * Parameters:
         * leftVelo: the velocity to set the leftBase motor group to
         * rightVelo: the velocity to set the rightBase motor group to
         */
        void setVelocity(int leftVelo, int rightVelo); 

        /**
         * The turnAngle function is an autonomous function used to turn the robot
         * to a specific angle, relative to its current position.
         * 
         * Parameters:
         * angle: the angle to which to turn. Clockwise is positive, counterclockwise
         *        is negative. For example, passing in 45 would make the robot turn
         *        45 degrees to the right (clockwise, from an overhead view)
         * maxSpeed: the maximum speed the chassis motors can run at (in RPM)
         */ 
        void turnAngle(float angle, int maxSpeed);

        /**
         * The moveStraight function is an autonomous function used to
         * tell the robot to drive forward or backward a given amount
         * 
         * Parameters: 
         * distance: the distance to travel, in inches. Negative values = backwards
         * maxSpeed: the maximum speed the chassis motors can run at (in RPM)
         */
        void moveStraight(float distance, int maxSpeed); 
};