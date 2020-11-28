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
    leftTelemetry.pos = leftMotor.getPosition();
    leftTelemetry.targetPos = leftMotor.getTargetPosition();
    leftTelemetry.velo = leftMotor.getTargetVelocity();
    leftTelemetry.targetVelo = leftMotor.getTargetVelocity();
    leftTelemetry.temp = leftMotor.getTemperature();
    leftTelemetry.torque = leftMotor.getTorque();
}

void Intake::updateRightTelemetry()
{
    //Updating all the values in the rightTelemetry struct
    rightTelemetry.pos = rightMotor.getPosition();
    rightTelemetry.targetPos = rightMotor.getTargetPosition();
    rightTelemetry.velo = rightMotor.getTargetVelocity();
    rightTelemetry.targetVelo = rightMotor.getTargetVelocity();
    rightTelemetry.temp = rightMotor.getTemperature();
    rightTelemetry.torque = rightMotor.getTorque();
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