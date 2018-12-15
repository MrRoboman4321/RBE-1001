#include "PID.h"

//TODO: Document

PID::PID(Encoder *encoder1, Encoder *encoder2, float kp, PIDType type) {
    _encoder1 = encoder1;
    _encoder2 = encoder2;
    _kp = kp;
    _type = type;
}

/**
 * Update the setpoint of the PID
 * @param val new setpoint
 */
void PID::setSetpoint(float val) {
    _setpoint = val;
}

/**
 * Update the tolerance of the PID
 * @param val new tolerance
 */
void PID::setTolerance(float val) {
    _tolerance = val;
}

/**
 * Get the current error of the PID, based on PID type
 * @return current error of the PID
 */
float PID::getError() {
    //If normal, return the difference
    if(_type == NORMAL) {
        return _setpoint - _encoder1->getPosition();
    } else if(_type == STRAIGHT) { //If straight, return the difference between the two encoders
        return _encoder1->getPosition() - _encoder2->getPosition();
    } else if(_type == TURN) { //If turning, return the sum of the two encoders
        return _encoder1->getPosition() + _encoder2->getPosition();
    }
}

/**
 * Get the speed that the PID calculates
 * @return speed of the PID
 */
float PID::getSpeed() {
    return constrain(_kp * getError(), -1, 1);
}

/**
 * Gets the average encoder position
 * @return average encoder position
 */
float PID::getAvgEncoders() {
    return (_encoder1->getPosition() + _encoder2->getPosition())/2;
}

/**
 * Whether or not the encoder is within the range of the setpoint,
 *   dependant on the type of the PID.
 * @return whether the PID is within tolerance
 */
bool PID::withinTolerance() {
    Serial.println(abs(_setpoint - _encoder1->getPosition()) < _tolerance);
    if(_type == NORMAL) {
        return abs(_setpoint - _encoder1->getPosition()) < _tolerance;
    } else if(_type == STRAIGHT) {
        //We never used this type of PID, so we never implemented this logic.
        return false;
    }
}
