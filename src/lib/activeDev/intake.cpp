#include "main.h"

/**
 * The implementation of the Intake class
 * This file contains the source code for the Intake class, along with
 * explanations of how each function works
 */ 

Intake::Intake(std::initializer_list<int> ports, std::initializer_list<bool> revs, 
               pros::motor_gearset_e_t gearset, pros::controller_digital_e_t inBtn, pros::controller_digital_e_t outBtn) {
    motorPorts = ports;
    std::vector<bool> motorRevs = revs;
    for(int i = 0; i < motorPorts.size(); i++) {
        pros::c::motor_set_gearing(motorPorts[i], gearset);
        if(motorRevs[i]) pros::c::motor_is_reversed(motorPorts[i]);
    }
    inButton = inBtn;
    outButton = outBtn;
}

void Intake::driver(pros::controller_id_e_t controller) {
    if(pros::c::controller_get_digital(controller, inButton)) in();
    else if(pros::c::controller_get_digital(controller, outButton)) out();
    else stop();   
}

void Intake::in() {
    for(int p : motorPorts) {
        pros::c::motor_move(p, 127);
    }
}

void Intake::out() {
    for(int p : motorPorts) {
        pros::c::motor_move(p, -127);
    }
}

void Intake::stop() {
    for(int p : motorPorts) {
        pros::c::motor_move(p, 0);
    }
}
/**
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
}*/