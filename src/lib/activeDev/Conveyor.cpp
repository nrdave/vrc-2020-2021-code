#include "main.h"

/**
 * The implementation of the Conveyor class
 * This file contains the source code for the Conveyor class, along with
 * explanations of how each function works
 */ 

Conveyor::Conveyor(std::initializer_list<int> ports, std::initializer_list<bool> revs, 
                    pros::motor_gearset_e_t gearset, pros::controller_digital_e_t upBtn, pros::controller_digital_e_t downBtn)
        {
        for(int i = 0; i < ports.size(); i++) {
            pros::c::motor_set_gearing(ports[i], gearset);
            motorPorts.push_back(ports[i]);
            if(revs[i]) pros::c::motor_is_reversed(ports[i]);
        }
        upButton = upBtn;
        downButton = downBtn;
        }

void Conveyor::driver(okapi::Controller controller)
{
    if(controller.getDigital(upButton)) moveUp();
    else if (controller.getDigital(downButton)) moveDown();
    else stop();
}

void Conveyor::moveUp()
{
    for(p : motorPorts) {
        pros::motor_move(127);
    }
}

void Conveyor::moveDown()
{
    for(p : motorPorts) {
        pros::motor_move(-127);
    }
}

void Conveyor::stop()
{
    for(p : motorPorts) {
        pros::motor_move(0);
    }
}
/**
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
}*/