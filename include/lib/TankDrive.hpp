#pragma once
#include "okapi/api.hpp"

/**
 * The header file for the TankDrive class, which is used to create objects that 
 * represent a standard tank drive drivetrain design. 
 * 
 * The comments in this header file explain the purpose of each member object or function,
 * while the comments in the respective source file explain the inner workings of each
 * function
 */

//Redefining the okapi gearsets to have a simpler name
#define GREEN okapi::AbstractMotor::gearset::green
#define RED okapi::AbstractMotor::gearset::red
#define BLUE okapi::AbstractMotor::gearset::blue


class TankDrive {
    private:
        /**
         * OkapiLib motor group objects. Each one represents the 
         * motor(s) on one side of the drivetrain
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
         * Variable to hold the width of the drivetrain. This value is used in the turnAngle function
         * 
         * As long as the robot's base is rectangular, the turning point of the robot will always
         * be down the robot's front-facing middle. So, this value will be usable no matter
         * the wheel configuration
         */ 
        float baseWidth;
        /**
         * The drivePID function is a PID controller for the drivetrain. It sets each side of 
         * the drivetrain to move a specified length. It is used as the base for all autonomous 
         * functions. Individual functions conduct any calculations needed to get the 
         * needed target values before passing those values into drivePID. This means
         * that the PID controller for the drivetrain need only be tuned once
         * 
         * @param leftTarg: The target length to move to, in inches, for the left side of the drivetrain
         *           Can be negative to indicate rotating backwards
         * @param rightTarg: The target length to move to, in inches, for the right side of the drivetrain
         *           Can be negative to indicate rotating backwards
         */
        void drivePID(float leftTarg, float rightTarg); 

        /**
         * The PID constant values, kP for the proportional constant,
         * kI for the integral constant, and kD for the derivative constant
         */ 
        float kP;
        float kI;
        float kD;
    public:
        /**
         * One of the constructors for a TankDrive object. This one is for a tank
         * drive with 1 motor powering each side of the drivetrain
         * 
         * @param leftMotor: the motor port of the motor on the left side of the drivetrain
         * @param rightMotor: the motor port of the motor on the right side of the drivetrain
         * @param leftReversed: a boolean to indicate if the left motor needs to be reversed
         * @param rightReversed: a boolean to indicate if the right motor needs to be reversed
         * @param gearset: the motor gearset used in the motors (it is assumed that both 
         *                 motors use the same gearset)
         * @param wD: the diameter of the wheels used
         * @param bR: the distance from the middle of the robot to the wheels
         * @param Pconst: the value of the proportional constant in the PID controller
         * @param Iconst: the value of the integral constant in the PID controller
         * @param Dconst: the value of the derivative constant in the PID controller
         */ 
        TankDrive(int leftMotor, int rightMotor, bool leftReversed, bool rightReversed, 
                okapi::AbstractMotor::gearset gearset, float wD, float bR,
                float Pconst, float Iconst, float Dconst);
        /** 
         * One of the constructors for a TankDrive object. This one is for a tank
         * drive with 2 motors powering each side
         * 
         * @param leftFrontMotor: the motor port of the motor on the left side of the drivetrain
         * @param rightFrontMotor: the motor port of the motor on the right side of the drivetrain
         * @param leftBackMotor: the motor port of the motor on the left side of the drivetrain
         * @param rightBackMotor: the motor port of the motor on the right side of the drivetrain
         * @param leftFrontReversed: a boolean to indicate if the left front motor needs to be reversed
         * @param rightFrontReversed: a boolean to indicate if the right front motor needs to be reversed
         * @param leftBackReversed: a boolean to indicate if the left back motor needs to be reversed
         * @param rightBackReversed: a boolean to indicate if the right back motor needs to be reversed         
         * @param gearset: the motor gearset used in the motors (it is assumed that both 
         *          motors use the same gearset)
         * @param wD: the diameter of the wheels used
         * @param bR: the distance from the middle of the robot to the wheels
         * @param Pconst: the value of the proportional constant in the PID controller
         * @param Iconst: the value of the integral constant in the PID controller
         * @param Dconst: the value of the derivative constant in the PID controller
         */ 
        TankDrive(int leftFrontMotor, int rightFrontMotor, int leftBackMotor, int rightBackMotor, 
                bool leftFrontReversed, bool rightFrontReversed, 
                bool leftBackReversed, bool rightBackReversed,
                okapi::AbstractMotor::gearset gearset, float wD, float bR,
                float Pconst, float Iconst, float Dconst);

        /**
         * The driver function allows control of the drivetrain during the opcontrol period,
         * with each side of the drivetrain bound to one of the controller joysticks
         * 
         * @param controller: the OkapiLib controller object, which represents the robot controller
         */ 
        void driver(okapi::Controller controller);



        /**
         * The setVelocity function manually sets the velocity of each motor group. This really
         * only exists so that in the case of extreme emergency (i.e. all autonomous code has 
         * broken for some reason and the team has a match soon), setVelocity can be used to 
         * manually control the motors in a timer-based autonomous.
         * 
         * @param leftVelo: the velocity to set the leftBase motor group to
         * @param rightVelo: the velocity to set the rightBase motor group to
         */
        void setVelocity(int leftVelo, int rightVelo); 

        /**
         * The turnAngle function is an autonomous function used to turn the robot
         * to a specific angle, relative to its current position.
         * 
         * @param angle: the angle to which to turn. Clockwise is positive, counterclockwise
         *        is negative. For example, passing in 45 would make the robot turn
         *        45 degrees to the right (clockwise, from an overhead view)
         */ 
        void turnAngle(float angle);

        /**
         * The moveStraight function is an autonomous function used to
         * tell the robot to drive forward or backward a given amount
         * 
         * @param distance: the distance to travel, in inches. Negative values = backwards
         */
        void moveStraight(float distance); 
};