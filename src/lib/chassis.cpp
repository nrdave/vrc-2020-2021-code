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
    
}