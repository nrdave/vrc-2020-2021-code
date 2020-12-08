#pragma once
#include "api.h"
#include "library.hpp"

class Conveyor
{
    private:
    /**
     * The Okapi MotorGroup object used to control any motors powering the conveyor
     */ 
        okapi::MotorGroup motors;
    /**
    * The buttons on the controller that tell the conveyor to 
    * push up or down an object
     */ 
        okapi::ControllerDigital upButton, downButton;
    /**
     * Telemetry structs (defined in library.hpp) that hold the 
     * telemetry data for each motor. Data is displayed on the GUI
     */ 
        Telemetry telem;
    /**
     * Functions to update the telemetry for the motor group
     */ 
        void updateTelemetry();

    public:
    /**
     * The constructor for a conveyor with 1 motor
     * @param port The port of the motor
     * @param rev A boolean indicating if the motor needs to be reversed
     * @param gearset The gearset of the motors    
     * @param upBtn The button on the controller that tells the conveyor to move objects up
     * @param downBtn The button on the controller that tells the conveyor to move objects up 
     */ 
         Conveyor(int port, bool rev, okapi::AbstractMotor::gearset gearset, 
                 okapi::ControllerDigital upBtn, okapi::ControllerDigital downBtn);    
    /**
     * The constructor for a conveyor with 2 motors
     * @param port1 The port of the first motor
     * @param port2 The port of the second motor
     * @param rev1 A boolean indicating if the first motor is reversed
     * @param rev2 A boolean indicating if the second motor is reversed
     * @param gearset The gearset of the motors    
     * @param upBtn The button on the controller that tells the conveyor to move objects up
     * @param downBtn The button on the controller that tells the conveyor to move objects up
     */ 
         Conveyor(int port1, int port2, bool rev1, bool rev2, 
                 okapi::AbstractMotor::gearset gearset, 
                 okapi::ControllerDigital upBtn, okapi::ControllerDigital downBtn);
    /**
     * The function controlling the conveyor during driver control
     * @param controller The controller object representing the controller, used to get controller inputs
     */ 
        void driver(okapi::Controller controller);
    /**
     * A function to set the motor(s) to move objects up
     */ 
        void moveUp();
    /**
     * A function to set the motor(s) to move objects down
     */ 
        void moveDown();
    /**
     * Functions that return the telemetry data for the motor group
     */ 
        Telemetry getTelemetry();
};