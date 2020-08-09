/**
 * The implementation of the Chassis class
 * This file contains the source code for the chassis class, along with
 * explanations of how each function works
 */ 

#include "main.h"

Chassis::Chassis(int leftMotor, int rightMotor, 
                 bool leftReversed, bool rightReversed, 
                 okapi::AbstractMotor::gearset gearset, float wD,
                 float Pconst, float Iconst, float Dconst):
                 rightBase({okapi::Motor(rightMotor, rightReversed, 
                    gearset, okapi::AbstractMotor::encoderUnits::degrees)}),                 
                 leftBase({okapi::Motor(leftMotor, leftReversed, 
                    gearset, okapi::AbstractMotor::encoderUnits::degrees)})
{
    /**
     * The Chassis Constructor needs to instantiate the
     * rightBase and leftBase objects, which must be done through
     * the constructor initializer list. Then, it sets the wheelDiameter 
     * and PID constant variables to the passed in values
     */ 
    wheelDiameter = wD;
    kP = Pconst;
    kI = Iconst;
    kD = Dconst;
}

Chassis::Chassis(int leftFrontMotor, int rightFrontMotor, int leftBackMotor, int rightBackMotor, 
                bool leftFrontReversed, bool rightFrontReversed, bool leftBackReversed, bool rightBackReversed,
                okapi::AbstractMotor::gearset gearset, float wD, 
                float Pconst, float Iconst, float Dconst):
                 rightBase({okapi::Motor(rightFrontMotor, rightFrontReversed, 
                                gearset, okapi::AbstractMotor::encoderUnits::degrees), 
                            okapi::Motor(rightBackMotor, rightBackReversed, 
                                gearset, okapi::AbstractMotor::encoderUnits::degrees)}),                 
                 leftBase({okapi::Motor(leftFrontMotor, leftFrontReversed, 
                                gearset, okapi::AbstractMotor::encoderUnits::degrees),
                           okapi::Motor(leftBackMotor, leftBackReversed, 
                                gearset, okapi::AbstractMotor::encoderUnits::degrees)})
{
    /**
     * The Chassis Constructor needs to instantiate the
     * rightBase and leftBase objects, which must be done through
     * the constructor initializer list. Then, it sets the wheelDiameter 
     * and PID constant variables to the passed in values
     */ 
    wheelDiameter = wD;
    kP = Pconst;
    kI = Iconst;
    kD = Dconst;
}

void Chassis::driver(okapi::Controller controller) {
    /**
     * The driver function uses the okapi controller object to get the values of
     * the Y axes on each controller joystick. Then, each base motor group is set 
     * to the value of its corresponding joystick. Since the getAnalog function
     * returns a value between -1 and 1, the controllerSet function is used to 
     * set the motors, as it accepts values in that range
     */ 
    leftBase.controllerSet(controller.getAnalog(okapi::ControllerAnalog::leftY));
    rightBase.controllerSet(controller.getAnalog(okapi::ControllerAnalog::rightY));
}

void Chassis::chassisPID(float leftTarg, float rightTarg, int maxSpeed)
{
    /**
     * Convert leftTarg and rightTarg from inches to travel to degrees for the
     * wheels to rotate
     * The distance the wheel travels (if it isn't slipping) over 1 full rotation is
     * equal to its circumference. So, for a wheel with a diameter of 4 inches, it would
     * travel 4*pi inches over 1 full rotation.
     * So, the conversion factor between inches to travel and degrees to rotate is
     * 360 degrees/(wheel diameter * pi), as wheel diameter times pi is the inches traveled
     * over 1 rotation, while 360 degrees is degrees rotated over 1 rotation
     */ 
    leftTarg *= 360/(wheelDiameter * 3.1415);
    rightTarg *= 360/(wheelDiameter * 3.1415);
    //Reset the encoders of each motor group to 0
    leftBase.tarePosition();
    rightBase.tarePosition();
    //Declare or initialize all variables used in the loop
    float leftError;
    float rightError;
    float leftOutput;
    float rightOutput;
    //Integral variables are initiated so that the += operator can be used throughout the while loop
    float leftIntegral = 0;
    float rightIntegral = 0;
    float leftDerivative;
    float rightDerivative;
    //Previous error will be equal to the current error, but it is cleaner to set the current error in the while loop
    float leftPrevError = leftTarg - leftBase.getPosition();
    float rightPrevError = rightTarg - rightBase.getPosition();
    //Enter a while loop that runs until both sides are within 20 degrees of target rotation
    while(abs(leftError) > 20 && abs(rightError) > 20)
    {
        //Calculate the error
        leftError = leftTarg - leftBase.getPosition(); 
        rightError = rightTarg - rightBase.getPosition();

        //Calculate the integral
        leftIntegral += leftError;
        rightIntegral += rightError;

        //Calculate the derivative
        leftDerivative = leftError - leftPrevError;
        rightDerivative = rightError - rightPrevError;

        //Set the previous error
        leftPrevError = leftError;
        rightPrevError = rightError;

        //Set the output values
        leftOutput = leftError * kP + leftIntegral * kI + leftDerivative * kD;
        rightOutput = rightError * kP + rightIntegral * kI + rightDerivative * kD;
        /**
         * Ensure that the output velocities are not greater than the 
         * upper speed bound passed in
         */ 
        if(abs(leftOutput) > maxSpeed)
            if(leftOutput < 0) leftOutput = -maxSpeed;
            else leftOutput = maxSpeed;
        if(abs(rightOutput) > maxSpeed)
            if(rightOutput < 0) rightOutput = -maxSpeed;
            else rightOutput = maxSpeed;
        //Set the motor group velocities to the output speeds
        setVelocity(leftOutput, rightOutput);

        pros::delay(15);
    }
}

void Chassis::setVelocity(int leftVelo, int rightVelo)
{
    /**
     * As noted in chassis.hpp, setVelocity simply encapsulates
     * the okapi moveVelocity function into a cleaner package,
     * while also allowing manual velocity setting in an
     * autonomous routine
     */ 
    leftBase.moveVelocity(leftVelo);
    rightBase.moveVelocity(rightVelo);
}

void Chassis::moveStraight(float distance, int maxSpeed)
{
    /**
     * The moveStraight function just slightly simplifies the chassisPID
     * function, cutting down on a paramter. This is purely added for
     * convenience/readability. Although not having this function wouldn't
     * change anything signifigant, I wanted to keep the chassisPID function
     * private, as, in my mind, it makes sense for an object's PID controller
     * to be kept private.
     */ 
    chassisPID(distance, distance, maxSpeed);
}