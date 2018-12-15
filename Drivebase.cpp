#include "Drivebase.h"
#include "Constants.h"

/**
 * Helper function. Maps one range of values to another
 * @param x input
 * @param in_min minimum input value
 * @param in_max maximum input value
 * @param out_min minimum output value
 * @param out_max maximum output value
 * @return the mapped value
 */
double mapVal(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * Helper function. Maps a joystick value to the range [-1, 1]
 * @param in joystick value
 * @return mapped joystick value
 */
double mapJoy(double in) {
    double val = mapVal(in, 0.0, 180.0, -1.0, 1.0);
    return val;
}

Drivebase::Drivebase() {
    //Setup both motors
    _left.attach(LEFT_DRIVE, 1000, 2000);
    _right.attach(RIGHT_DRIVE, 1000, 2000);

    //Construct both encoders
    _rightDist = new Encoder(RIGHT_POS_A, RIGHT_POS_B);
    _leftDist = new Encoder(LEFT_POS_A, LEFT_POS_B);

    //Construct both a straight and turning PID
    _distPID = new PID(_leftDist, _rightDist, DRIVEBASE_FORWARD_P, STRAIGHT);
    _turnPID = new PID(_leftDist, _rightDist, DRIVEBASE_TURN_P, TURN);
}

/**
 * Sets the left speed of the drivebase
 * @param speed motor speed, between -1 and 1
 */
void Drivebase::setLeft(double speed) {
    speed = mapVal(speed, 1.0, -1.0, 0.0, 180.0);
    _left.write(speed);
}

/**
 * Sets the right speed of the drivebase
 * @param speed motor speed, between -1 and 1
 */
void Drivebase::setRight(double speed) {
    speed = mapVal(speed, -1.0, 1.0, 0.0, 180.0);
    _right.write(speed);
}

/**
 * Get the left encoder value
 * @return left encoder value
 */
float Drivebase::getLeftDist() {
    return _leftDist->getPosition();
}

/**
 * Get the right encoder value
 * @return right encoder value
 */
float Drivebase::getRightDist() {
    return _rightDist->getPosition();
}

/**
 * Update the state of encoders, and motor speed during teleop.
 */
void Drivebase::update() {
    //If we're in teleop, read joystick inputs
    if(_robot->getGamePeriod() == TELEOP) {
        setLeft(mapJoy(_robot->getLeftJoy()));
        setRight(mapJoy(_robot->getRightJoy()));
    }
    _rightDist->update();
    _leftDist->update();

    Serial.println(getRightDist());
}

/**
 * Sets the robot instance
 * @param robot instance of Robot
 */
void Drivebase::setRobot(Robot *robot) {
    _robot = robot;
}

/**
 * Update the distance PID with a new offset
 * @param pos number of ticks to travel, added to the current position
 */
void Drivebase::setStraightOffset(float pos) {
    //TODO: Make this work (bad right now)
    _distPID->setSetpoint((getLeftDist() + getRightDist())/2 + pos);
}

void Drivebase::setTurnOffset(float pos) {
    //TODO: Document and make work
    _turnPID->setSetpoint(pos);
}

/**
 * Get the error of the straight-line PID
 * @return error of _distPID
 */
float Drivebase::getStraightError() {
    return _distPID->getError();
}

/**
 * Get the error of the point-turn PID
 * @return error of _turnPID
 */
float Drivebase::getTurnError() {
    return _turnPID->getError();
}

/**
 * Whether or not the straight PID is within tolerance
 * @return is straight PID in tolerance
 */
bool Drivebase::straightWithinTolerance() {
    return _distPID->withinTolerance();
}

/**
 * Whether or not the turn PID is within tolerance
 * @return is turn PID in tolerance
 */
bool Drivebase::turnWithinTolerance() {
    return _turnPID->withinTolerance();
}