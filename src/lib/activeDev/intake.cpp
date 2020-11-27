#include "main.h"

Intake::Intake(int leftPort, int rightPort, bool leftReversed, bool rightReversed,
               okapi::ControllerDigital inBtn, okapi::ControllerDigital outBtn):
    leftMotor(leftPort, leftReversed), 
    rightMotor(rightPort, rightReversed)
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

void Intake::updateLeftTelemetry()
{
    //Updating all the values in the leftTelemetry struct
    leftTelemetry.pos = roundDouble(leftBase.getPosition(), 2);
    leftTelemetry.targetPos = roundDouble(leftBase.getTargetPosition(), 2);
    leftTelemetry.velo = roundDouble(leftBase.getTargetVelocity(), 2);
    leftTelemetry.targetVelo = roundDouble(leftBase.getTargetVelocity(), 2);
    leftTelemetry.temp = roundDouble(leftBase.getTemperature(), 2);
    leftTelemetry.torque = roundDouble(leftBase.getTorque(), 2);
}

void Intake::updateRightTelemetry()
{
    //Updating all the values in the rightTelemetry struct
    rightTelemetry.pos = roundDouble(rightBase.getPosition(), 2);
    rightTelemetry.targetPos = roundDouble(rightBase.getTargetPosition(), 2);
    rightTelemetry.velo = roundDouble(rightBase.getTargetVelocity(), 2);
    rightTelemetry.targetVelo = roundDouble(rightBase.getTargetVelocity(), 2);
    rightTelemetry.temp = roundDouble(rightBase.getTemperature(), 2);
    rightTelemetry.torque = roundDouble(rightBase.getTorque(), 2);
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