#pragma once
#include "api.h"
#include "library.hpp"
#include <vector>
#include <initializer_list>

class Conveyor
{
    private:
        std::vector<int> motorPorts;
        std::vector<bool> motorReverses;
    /**
    * The buttons on the controller that tell the conveyor to 
    * push up or down an object
     */ 
        pros::controller_digital_e_t upButton, downButton;
    /**
     * Telemetry structs (defined in library.hpp) that hold the 
     * telemetry data for each motor. Data is displayed on the GUI
     */ 
        Telemetry telem;
    /**
     * Functions to update the telemetry for the motor group
     */ 
        //void updateTelemetry();

    public:
    /**
     * The constructor for a conveyor with 1 motor
     * @param ports The ports of the motor(s)
     * @param revs A list of booleans indicating which motors are reversed, each entry in the list refers to the motor port
     *              in the corresponding address in ports
     * @param gearset The gearset of the motors    
     * @param upBtn The button on the controller that tells the conveyor to move objects up
     * @param downBtn The button on the controller that tells the conveyor to move objects up 
     */ 
         Conveyor(std::initializer_list<int> ports, std::initializer_list<bool> revs, 
                    pros::motor_gearset_e_t gearset, pros::controller_digital_e_t upBtn, pros::controller_digital_e_t downBtn);    
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
     * A function to set the motors to stop
     */ 
        void stop();
    /**
     * Functions that return the telemetry data for the motor group
     */ 
        //Telemetry getTelemetry();
};