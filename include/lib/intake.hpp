#pragma once
#include "api.h"
#include "library.hpp"

/**
 * The header file for the Intake class, which is used to create objects representing
 * any form of intake, a mechanism that pulls in objects.
 * 
 * The comments in this header file explain the purpose of each member object or function,
 * while the comments in the respective source file explain the inner workings of each
 * function
 */ 

class Intake
{
    private:
    /**
     * PROS Motor objects. Each one corresponds to the motor
     * on each intake
     */ 
        pros::Motor leftMotor, rightMotor;
    /**
     * Telemetry structs (defined in library.hpp) used to hold telemetry data
     * for each motor
     */ 
        Telemetry leftTelemetry, rightTelemetry;
   /**
    * The buttons on the controller that tell the intake to 
    * take in or push out an object
    */ 
        okapi::ControllerDigital inButton, outButton;
    /**
     * Functions to update the telemetry data for each motor
     */ 
        void updateLeftTelemetry();
        void updateRightTelemetry();
    public:
    /**
     * The constructor for the Intake class
     * @param leftPort The port of the left motor
     * @param rightPort The port of the right motor
     * @param leftReversed A boolean indicating whether the left motor is reversed 
     * @param rightReversed A boolean indicating whether the right motor is reversed 
     * @param inBtn The button on the controller to press to tell the intakes to take in an object
     * @param outBtn The button on the controller to press to tell the intakes to push out an object
     */ 
        Intake(int leftPort, int rightPort, bool leftRev, bool rightRev, 
               okapi::ControllerDigital inBtn, okapi::ControllerDigital outBtn);
    /**
     * The function used to control the intakes during opcontrol
     * @param controller The controller object representing the v5 controller
     */ 
        void driver(okapi::Controller controller);
    /**
     * A function to set the motors to take out an object
     */ 
        void in();
    /**
     * A function to set the motors to push out an object
     */ 
        void out();
    /**
     * Functions to retrieve telemetry data for each motor
     * @return The telemetry data for the given motor (left or right)
     */ 
        Telemetry getLeftTelemetry();
        Telemetry getRightTelemetry();
};