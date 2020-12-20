#include "main.h"

/**
 * The implementation of the Intake class
 * This file contains the source code for the Intake class, along with
 * explanations of how each function works
 */ 

Intake::Intake(int leftPort, int rightPort, bool leftRev, bool rightRev,
               okapi::ControllerDigital inBtn, okapi::ControllerDigital outBtn):
    leftMotor(leftPort, leftRev), 
    rightMotor(rightPort, rightRev)
    {
        outButton = outBtn;
        inButton = inBtn;
    }

void Intake::driver(okapi::Controller controller)
{
    if(controller.getDigital(inButton)) in();
    else if(controller.getDigital(outButton)) out();
    else
    {
        leftMotor.move(0);
        rightMotor.move(0);
    }
    
}

void Intake::in()
{
    leftMotor.move(127);
    rightMotor.move(127);
}

void Intake::out()
{
    leftMotor.move(-127);
    rightMotor.move(-127);
}

void Intake::stop()
{
    leftMotor.move(0);
    rightMotor.move(0);
}

void Intake::updateLeftTelemetry()
{
    //Updating all the values in the leftTelemetry struct
    leftTelemetry.pos = leftMotor.get_position();
    leftTelemetry.targetPos = leftMotor.get_target_position();
    leftTelemetry.velo = leftMotor.get_actual_velocity();
    leftTelemetry.targetVelo = leftMotor.get_target_velocity();
    leftTelemetry.temp = leftMotor.get_temperature();
    leftTelemetry.torque = leftMotor.get_torque();
}

void Intake::updateRightTelemetry()
{
    //Updating all the values in the rightTelemetry struct
    rightTelemetry.pos = rightMotor.get_position();
    rightTelemetry.targetPos = rightMotor.get_target_position();
    rightTelemetry.velo = rightMotor.get_actual_velocity();
    rightTelemetry.targetVelo = rightMotor.get_target_velocity();
    rightTelemetry.temp = rightMotor.get_temperature();
    rightTelemetry.torque = rightMotor.get_torque();
}

Telemetry Intake::getLeftTelemetry()
{
    updateLeftTelemetry();
    return leftTelemetry;
}

Telemetry Intake::getRightTelemetry()
{
    updateRightTelemetry();
    return rightTelemetry;
}