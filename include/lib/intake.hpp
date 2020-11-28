#pragma once
#include "api.h"
#include "library.hpp"
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
        Intake(int leftPort, int rightPort, bool leftReversed, bool rightReversed, 
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