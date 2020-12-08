#include "main.h"

/**
 * The implementation of the Conveyor class
 * This file contains the source code for the Conveyor class, along with
 * explanations of how each function works
 */ 

Conveyor::Conveyor(int port1, int port2, bool rev1, bool rev2, 
                 okapi::AbstractMotor::gearset gearset, 
                 okapi::ControllerDigital upBtn, okapi::ControllerDigital downBtn):
                 motors({okapi::Motor(port1, rev1, gearset, okapi::AbstractMotor::encoderUnits::degrees), 
                 okapi::Motor(port2, rev2, gearset, okapi::AbstractMotor::encoderUnits::degrees)})

        {
        upButton = upBtn;
        downButton = downBtn;
        }

Conveyor::Conveyor(int port, bool rev, 
                 okapi::AbstractMotor::gearset gearset, 
                 okapi::ControllerDigital upBtn, okapi::ControllerDigital downBtn):
                 motors({okapi::Motor(port, rev, gearset, okapi::AbstractMotor::encoderUnits::degrees)})

        {
        upButton = upBtn;
        downButton = downBtn;
        }
void Conveyor::driver(okapi::Controller controller)
{
    if(controller.getDigital(upButton)) moveUp();
    else if (controller.getDigital(downButton)) moveDown();
    else
    {
        //If neither button is pressed, set the velocity of the motors to 0
        motors.moveVelocity(0);
    }
}

void Conveyor::moveUp()
{
    //Setting the motor group to move at their maximum positive speed
    if(motors.getGearing() == GEARSET_BLUE) motors.moveVelocity(600);
    else if(motors.getGearing() == GEARSET_RED) motors.moveVelocity(100);
    else motors.moveVelocity(200);
}

void Conveyor::moveDown()
{
    //Setting both motors to move at their maximum negative speed
    //Setting the motor group to move at their maximum positive speed
    if(motors.getGearing() == GEARSET_BLUE) motors.moveVelocity(-600);
    else if(motors.getGearing() == GEARSET_RED) motors.moveVelocity(-100);
    else motors.moveVelocity(-200);
}

void Conveyor::updateTelemetry()
{
    telem.pos = motors.getPosition();
    telem.targetPos = motors.getTargetPosition();
    telem.velo = motors.getActualVelocity();
    telem.targetVelo = motors.getTargetVelocity();
    telem.temp = motors.getTemperature();
    telem.torque = motors.getTorque();
}

Telemetry Conveyor::getTelemetry()
{
    updateTelemetry();
    return telem;
}