#include "main.h"

/**
 * The implementation of the Conveyor class
 * This file contains the source code for the Conveyor class, along with
 * explanations of how each function works
 */ 

Conveyor::Conveyor(std::initializer_list<int> ports, std::initializer_list<bool> revs, 
                    pros::motor_gearset_e_t gearset, pros::controller_digital_e_t upBtn, pros::controller_digital_e_t downBtn)
        {
        motorPorts = ports;
        std::vector<bool> motorRevs = revs;
        for(int i = 0; i < motorPorts.size(); i++) {
            pros::c::motor_set_gearing(motorPorts[i], gearset);
            if(motorRevs[i]) pros::c::motor_is_reversed(motorPorts[i]);
        }
        upButton = upBtn;
        downButton = downBtn;
        }

void Conveyor::driver(pros::controller_id_e_t controller)
{
    if(pros::c::controller_get_digital(controller, upButton)) moveUp();
    else if (pros::c::controller_get_digital(controller, downButton)) moveDown();
    else stop();
}

void Conveyor::moveUp()
{
    for(int p : motorPorts) {
        pros::c::motor_move(p, 127);
    }
}

void Conveyor::moveDown()
{
    for(int p : motorPorts) {
        pros::c::motor_move(p, -127);
    }
}

void Conveyor::stop()
{
    for(int p : motorPorts) {
        pros::c::motor_move(p, 0);
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