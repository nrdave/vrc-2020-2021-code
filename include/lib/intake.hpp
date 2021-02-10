#pragma once
#include "api.h"
#include "library.hpp"
#include <vector>
#include <initializer_list>
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
     * A vector of ints that stores the ports for the intakes. Since all
     * intake motors should run to either intake/expel objects, there's no
     * need to separate the ports for the left/right side
     */ 
        std::vector<int> motorPorts;
    /**
     * Telemetry structs (defined in library.hpp) used to hold telemetry data
     * for each motor
     */ 
        Telemetry leftTelemetry, rightTelemetry;
   /**
    * The buttons on the controller that tell the intake to 
    * take in or push out an object
    */ 
        pros::controller_digital_e_t inButton, outButton;
    /**
     * Functions to update the telemetry data for each motor
     */ 
        void updateLeftTelemetry();
        void updateRightTelemetry();
    public:
    /**
     * The constructor for a conveyor with 1 motor
     * @param ports The ports of the motor(s)
     * @param revs A list of booleans indicating which motors are reversed, each entry in the list refers to the motor port
     *              in the corresponding address in ports
     * @param gearset The gearset of the motors    
     * @param upBtn The button on the controller that tells the intakes to intake objects
     * @param downBtn The button on the controller that tells the intakes to expel objects
     */ 
        Intake(std::initializer_list<int> ports, std::initializer_list<bool> revs, 
               pros::motor_gearset_e_t gearset, pros::controller_digital_e_t inBtn, pros::controller_digital_e_t outBtn);
    /**
     * The function controlling the conveyor during driver control
     * @param controller The ID of the controller to get input from
     */ 
        void driver(pros::controller_id_e_t controller);
    /**
     * A function to set the motors to take out an object
     */ 
        void in();
    /**
     * A function to set the motors to push out an object
     */ 
        void out();
    /**
     * A function to set the motors to not move
     */
        void stop(); 
    /**
     * Functions to retrieve telemetry data for each motor
     * @return The telemetry data for the given motor (left or right)
     */ 
        Telemetry getLeftTelemetry();
        Telemetry getRightTelemetry();
};