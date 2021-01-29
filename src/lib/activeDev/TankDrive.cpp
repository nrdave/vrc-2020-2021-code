#include "main.h"

/**
 * The implementation of the TankDrive class
 * This file contains the source code for the TankDrive class, along with
 * explanations of how each function works
 */ 

TankDrive::TankDrive(int leftMotor, int rightMotor, 
                 bool leftReversed, bool rightReversed, 
                 okapi::AbstractMotor::gearset gearset, float wD, float bW,
                 float Pconst, float Iconst, float Dconst):
                 rightBase({okapi::Motor(rightMotor, rightReversed, 
                    gearset, okapi::AbstractMotor::encoderUnits::degrees)}),                 
                 leftBase({okapi::Motor(leftMotor, leftReversed, 
                    gearset, okapi::AbstractMotor::encoderUnits::degrees)})
{
    /**
     * The TankDrive Constructor needs to initialize the
     * rightBase and leftBase objects, which must be done through
     * the constructor initializer list. Then, it sets the wheelDiameter, 
     * baseWidth, and PID constant variables to the passed in values
     */ 
    wheelDiameter = wD;
    baseWidth = bW;
    kP = Pconst;
    kI = Iconst;
    kD = Dconst;

    updateLeftTelemetry();
    updateRightTelemetry();
}

TankDrive::TankDrive(int leftFrontMotor, int rightFrontMotor, int leftBackMotor, int rightBackMotor, 
                bool leftFrontReversed, bool rightFrontReversed, bool leftBackReversed, bool rightBackReversed,
                okapi::AbstractMotor::gearset gearset, float wD, float bW, 
                float Pconst, float Iconst, float Dconst):
                 rightBase({okapi::Motor(rightFrontMotor, rightFrontReversed, 
                                gearset, okapi::AbstractMotor::encoderUnits::degrees), 
                            okapi::Motor(rightBackMotor, rightBackReversed, 
                                gearset, okapi::AbstractMotor::encoderUnits::degrees)}),                 
                 leftBase({okapi::Motor(leftFrontMotor, leftFrontReversed, 
                                gearset, okapi::AbstractMotor::encoderUnits::degrees),
                           okapi::Motor(leftBackMotor, leftBackReversed, 
                                gearset, okapi::AbstractMotor::encoderUnits::degrees)})
{
    /**
     * The TankDrive Constructor needs to initialize the
     * rightBase and leftBase objects, which must be done through
     * the constructor initializer list. Then, it sets the wheelDiameter, 
     * baseWidth, and PID constant variables to the passed in values
     */ 
    wheelDiameter = wD;
    baseWidth = bW;
    kP = Pconst;
    kI = Iconst;
    kD = Dconst;

    //Initializing the Telemetry struct values
    updateLeftTelemetry();
    updateRightTelemetry();
}


void TankDrive::driver(okapi::Controller controller) {
    /**
     * The driver function uses the okapi controller object to get the values of
     * the Y axes on each controller joystick. Then, each base motor group is set 
     * to the value of its corresponding joystick. Since the getAnalog function
     * returns a value between -1 and 1, the controllerSet function is used to 
     * set the motors, as it accepts values in that range
     */ 
    leftBase.controllerSet(controller.getAnalog(CONTROLLER_JOYSTICK_LEFT_Y));
    rightBase.controllerSet(controller.getAnalog(CONTROLLER_JOYSTICK_RIGHT_Y));
}

void TankDrive::drivePID(float leftT, float rightT)
{
    /**
     * Convert leftTarg and rightTarg from inches to travel to degrees for the
     * wheels to rotate
     * The distance the wheel travels (if it isn't slipping) over 1 full rotation is
     * equal to its circumference. So, for a wheel with a diameter of 4 inches, it would
     * travel 4*pi inches over 1 full rotation.
     * So, the conversion factor between inches to travel and degrees to rotate is
     * 360 degrees/(wheel diameter * pi), as wheel diameter times pi is the inches traveled
     * over 1 rotation, while 360 degrees is degrees rotated over 1 rotation
     */ 
    float leftTarg = leftT * 360/(wheelDiameter * 3.1415);
    float rightTarg = rightT * 360/(wheelDiameter * 3.1415);
    //Reset the encoders of each motor group to 0
    leftBase.tarePosition();
    rightBase.tarePosition();
    //Declare or initialize all variables used in the loop
    float leftError = leftTarg - leftBase.getPosition(); 
    float rightError = rightTarg - rightBase.getPosition();
    float leftOutput;
    float rightOutput;
    //Integral variables are initiated so that the += operator can be used throughout the while loop
    float leftIntegral = 0;
    float rightIntegral = 0;
    float leftDerivative;
    float rightDerivative;
    //Declaring the Previous Error Variable
    float leftPrevError;
    float rightPrevError;
    //Enter a while loop that runs until both sides are within 10 degrees of target rotation
    while(abs(leftError) > 5 && abs(rightError) > 5)
    {
        //Calculate the integral
        leftIntegral += leftError;
        rightIntegral += rightError;

        if(abs(leftError) < 10) leftIntegral = 0;
        if(abs(rightError) < 10) rightIntegral = 0;

        //Calculate the derivative
        leftDerivative = leftError - leftPrevError;
        rightDerivative = rightError - rightPrevError;

        //Set the previous error
        leftPrevError = leftError;
        rightPrevError = rightError;

        //Set the output values
        leftOutput = (leftError * kP) + (leftIntegral * kI) + (leftDerivative * kD);
        rightOutput = (rightError * kP) + (rightIntegral * kI) + (rightDerivative * kD);

        //Constraining the output voltages
        if(abs(leftOutput) > 12000)
            if(leftOutput < 0) leftOutput = -12000;
            else leftOutput = 12000;
        if(abs(rightOutput) > 12000)
            if(rightOutput < 0) rightOutput = -12000;
            else rightOutput = 12000;
        //Set the motor group voltages to the output velocity levels
        setVoltage(leftOutput, rightOutput);
        //Calculate the new error
        leftError = leftTarg - leftBase.getPosition(); 
        rightError = rightTarg - rightBase.getPosition();
        pros::delay(20);
    }
    setVelocity(0, 0);
}

void TankDrive::setVelocity(int leftVelo, int rightVelo)
{
    /**
     * As noted in TankDrive.hpp, setVelocity simply encapsulates
     * the okapi moveVelocity function into a cleaner package,
     * while also allowing manual velocity setting in an
     * autonomous routine
     */ 
    leftBase.moveVelocity(leftVelo);
    rightBase.moveVelocity(rightVelo);
}

void TankDrive::setVoltage(int leftVolt, int rightVolt)
{
    /**
     * As noted in TankDrive.hpp, setVelocity simply encapsulates
     * the okapi moveVelocity function into a cleaner package,
     * while also allowing manual velocity setting in an
     * autonomous routine
     */ 
    leftBase.moveVoltage(leftVolt);
    rightBase.moveVoltage(rightVolt);
}

void TankDrive::moveStraight(float distance)
{
    /**
     * The moveStraight function just slightly simplifies the drivePID
     * function, cutting down on a paramter. This is purely added for
     * convenience/readability. Although not having this function wouldn't
     * change anything signifigant, I wanted to keep the drivePID function
     * private, as, in my mind, it makes sense for an object's PID controller
     * to be kept private.
     */ 
    drivePID(distance, distance);
}

void TankDrive::turnAngle(float angle)
{
    /**
     * The distance each side needs to rotate can be found with the 
     * arc length equation s = r * theta, where theta is the angle
     * in radians, r is the radius of the circle, and s is the 
     * arc length.
     * This equation works because the robot turns around a point,
     * so while it might not be perfectly accurate, it is more than a
     * good enough approximation.
     * Relating the equation with the statement below, baseWidth is r * 2, so
     * we divide the baseWidth by 2, angle * (3.1415/180) is theta 
     * (as the angle passed in is degrees, and the arc length equation 
     * uses radians), and turnLength is s
     */ 
    double turnLength = angle * (3.1415/180) * (baseWidth / 2);
    /**
     * As stated in TankDrive.hpp, a positive angle will make the robot
     * turn clockwise. To achieve this, the left side of the base must 
     * move forward. So, the target for the right side is negative by
     * default. If the input angle is negative, the signs are switched,
     * so the right side goes forward, and the left goes backward, turning
     * the robot counterclockwise
     */ 
    drivePID(turnLength, -turnLength);
}

void TankDrive::updateLeftTelemetry()
{
    //Updating all the values in the leftTelemetry struct
    leftTelemetry.pos = leftBase.getPosition();
    leftTelemetry.targetPos = leftBase.getTargetPosition();
    leftTelemetry.velo = leftBase.getTargetVelocity();
    leftTelemetry.targetVelo = leftBase.getTargetVelocity();
    leftTelemetry.temp = leftBase.getTemperature();
    leftTelemetry.torque = leftBase.getTorque();
}

void TankDrive::updateRightTelemetry()
{
    //Updating all the values in the rightTelemetry struct
    rightTelemetry.pos = rightBase.getPosition();
    rightTelemetry.targetPos = rightBase.getTargetPosition();
    rightTelemetry.velo = rightBase.getTargetVelocity();
    rightTelemetry.targetVelo = rightBase.getTargetVelocity();
    rightTelemetry.temp = rightBase.getTemperature();
    rightTelemetry.torque = rightBase.getTorque();
}

Telemetry TankDrive::getLeftTelemetry()
{
    updateLeftTelemetry();
    return leftTelemetry;
}

Telemetry TankDrive::getRightTelemetry()
{
    updateRightTelemetry();
    return rightTelemetry;
}