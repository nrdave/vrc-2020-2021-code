#include "main.h"

/**
 * The implementation of the Conveyor class
 * This file contains the source code for the Conveyor class, along with
 * explanations of how each function works
 */ 

Conveyor::Conveyor(int lowerPort, int upperPort, bool lowerRev, bool upperRev, 
                 pros::motor_gearset_e gearset, 
                 okapi::ControllerDigital upBtn, okapi::ControllerDigital downBtn):
                lowerMotor(lowerPort, gearset, lowerRev), 
                upperMotor(upperPort, gearset, upperRev)
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
        upperMotor.move(0);
        lowerMotor.move(0);
    }
}

void Conveyor::moveUp()
{
    //Setting both motors to move at their maximum positive speed
    upperMotor.move(127);
    lowerMotor.move(127);
}

void Conveyor::moveDown()
{
    //Setting both motors to move at their maximum negative speed
    upperMotor.move(-127);
    lowerMotor.move(-127);
}

void Intake::updateLowerTelemetry()
{
    //Updating all the values in the lowerTelemetry struct
    lowerTelemetry.pos = lowerMotor.get_position();
    lowerTelemetry.targetPos = lowerMotor.get_target_position();
    lowerTelemetry.velo = lowerMotor.get_actual_velocity();
    lowerTelemetry.targetVelo = lowerMotor.get_target_velocity();
    lowerTelemetry.temp = lowerMotor.get_temperature();
    lowerTelemetry.torque = lowerMotor.get_torque();
}

void Intake::updateUpperTelemetry()
{
    //Updating all the values in the upperTelemetry struct
    upperTelemetry.pos = upperMotor.get_position();
    upperTelemetry.targetPos = upperMotor.get_target_position();
    upperTelemetry.velo = upperMotor.get_actual_velocity();
    upperTelemetry.targetVelo = upperMotor.get_target_velocity();
    upperTelemetry.temp = upperMotor.get_temperature();
    upperTelemetry.torque = upperMotor.get_torque();
}

Telemetry Intake::getLowerTelemetry()
{
    //Updating lowerTelemetry before returning it
    updatelowerTelemetry();
    return lowerTelemetry;
}

Telemetry Intake::getUpperTelemetry()
{
    //Updating upperTelemetry before returning it
    updateUpperTelemetry();
    return upperTelemetry;
}