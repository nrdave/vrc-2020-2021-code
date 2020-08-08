/**
 * The implementation of the Chassis class
 * This file contains the source code for the chassis class, along with
 * explanations of how each function works
 */ 

#include "main.h"

Chassis::Chassis(int leftMotor, int rightMotor, 
                 bool leftReversed, bool rightReversed, 
                 okapi::AbstractMotor::gearset gearset, float wD):
                 rightBase({okapi::Motor(rightMotor, rightReversed, 
                    gearset, okapi::AbstractMotor::encoderUnits::degrees)}),                 
                 leftBase({okapi::Motor(leftMotor, leftReversed, 
                    gearset, okapi::AbstractMotor::encoderUnits::degrees)})
{
    /**
     * The Chassis Constructor needs to instantiate the
     * rightBase and leftBase objects, which must be done through
     * the constructor initializer list. Then, it sets the wheelDiameter variable
     * to the passed in value
     */ 
    wheelDiameter = wD;
}

Chassis::Chassis(int leftFrontMotor, int rightFrontMotor, int leftBackMotor, int rightBackMotor, 
                bool leftFrontReversed, bool rightFrontReversed, bool leftBackReversed, bool rightBackReversed,
                okapi::AbstractMotor::gearset gearset, float wD):
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
     * the constructor initializer list. Then, it sets the wheelDiameter variable
     * to the passed in value
     */ 
    wheelDiameter = wD;
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

void Chassis::chassisPID(float leftTarg, float rightTarg, int maxVelo)
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
    //Calculate the initial error
    float leftError = leftTarg - leftBase.getPosition(); 
    float rightError = rightTarg - rightBase.getPosition();
    //Enter a while loop that runs until both sides are within 20 degrees of target rotation
    while(abs(leftError) > 20 && abs(rightError) > 20)
    {

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
