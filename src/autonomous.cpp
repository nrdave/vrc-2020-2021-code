#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    drive.moveStraight(3);
    conveyor.moveUp();
    pros::delay(500);
    conveyor.stop();
    pros::delay(50);
    switch(autonID)
    {
        case Auton::test:
            break;
        case Auton::left:
            drive.moveStraight(15);
            drive.turnAngle(-128);
            intake.in();
            conveyor.moveUp();
            drive.moveStraight(23);
            pros::delay(1500);
            drive.moveStraight(7.5);
            pros::delay(2000);
            intake.stop();
            pros::delay(1000);
            conveyor.stop();
            drive.moveStraight(-8);
            intake.out();
            pros::delay(2000);
            intake.stop();
            break;
        case Auton::midleft:
            drive.moveStraight(12);
            drive.turnAngle(90);
            drive.moveStraight(16.75);            
            drive.turnAngle(95);
            drive.moveStraight(15.25);
            conveyor.moveUp();
            pros::delay(3000);
            conveyor.stop();
            intake.out();
            drive.moveStraight(-8);
            intake.stop();
            drive.turnAngle(90);
            intake.in();
            drive.moveStraight(40);
            intake.stop();
            //drive.turnAngle(-45);
            break;
        case Auton::right:
            drive.moveStraight(15);
            drive.turnAngle(128);
            intake.in();
            conveyor.moveUp();
            drive.moveStraight(23);
            pros::delay(1500);
            drive.moveStraight(7.5);
            pros::delay(4000);
            conveyor.stop();
            drive.moveStraight(-8);
            intake.out();
            pros::delay(2000);
            intake.stop();
            break;
        case Auton::none:
            break;
    }
}