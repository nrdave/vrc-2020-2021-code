#pragma once
#include "api.h"
#include "library.hpp"

class Conveyor
{
    private:
    /**
     * The PROS Motor objects, representing the 2 motors on the conveyor.
     * lowerMotor refers to the motor closer to the base, while upperMotor
     * is the motor closer to the top of the robot
     */ 
        pros::Motor lowerMotor, upperMotor;
    /**
    * The buttons on the controller that tell the conveyor to 
    * push up or down an object
     */ 
        okapi::ControllerDigital upButton, downButton;
    /**
     * Telemetry structs (defined in library.hpp) that hold the 
     * telemetry data for each motor. Data is displayed on the GUI
     */ 
        Telemetry upperTelemetry, lowerTelemetry;
    /**
     * Functions to update the telemetry for each motor
     */ 
        void updateLowerTelemetry();
        void updateUpperTelemetry();

    public:
    /**
     * The constructor for the conveyor
     * @param lowerPort The port of the lower motor
     * @param upperPort The port of the upper motor
     * @param lowerRev A boolean indicating if the lower motor is reversed
     * @param upperRev A boolean indicating if the upper motor is reversed
     * @param upBtn The button on the controller that tells the conveyor to move objects up
     * @param downBtn The button on the controller that tells the conveyor to move objects up
     */ 
        Conveyor(int lowerPort, int upperPort, bool lowerRev, bool upperRev, 
                 pros::motor_gearset_e gearset, 
                 okapi::ControllerDigital upBtn, okapi::ControllerDigital downBtn);
    /**
     * The function controlling the conveyor during driver control
     * @param controller The controller object representing the controller, used to get controller inputs
     */ 
        void driver(okapi::Controller controller);
    /**
     * A function to set the motors to move objects up
     */ 
        void moveUp();
    /**
     * A function to set the motors to move objects down
     */ 
        void moveDown();
    /**
     * Functions that return the telemetry data for each motor
     */ 
        Telemetry getLowerTelemetry();
        Telemetry getUpperTelemetry();
};