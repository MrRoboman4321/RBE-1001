#include "Elevator.h"

/**
 * Helper function. Maps one range of values to another
 * @param x input
 * @param in_min minimum input value
 * @param in_max maximum input value
 * @param out_min minimum output value
 * @param out_max maximum output value
 * @return the mapped value
 */
double mapRange(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

Elevator::Elevator() {
    //Setup the drum and conveyor motors
    _drumMotor.attach(ELEVATOR_DRIVE);
    _conveyorMotor.attach(CONVEYOR_DRIVE);

    //Construct the drum encoder
    _position = new PotEncoder(ELEVATOR_POS);

    //Construct the PID
    _posPID = new PID(_position, ELEVATOR_P);
    _posPID->setTolerance(50);

    //Start the PID at the ground floor position
    _posPID->setSetpoint(ELEVATOR_FLOOR0);
}

/**
 * Sets the speed of the drum motor
 * @param speed
 */
void Elevator::setSpeed(float speed) {
    _drumMotor.write(mapRange(speed, -1, 1, 0, 180));
}

/**
 * Gets the current position of the elevator drum
 * @return encoder position of the drum
 */
int Elevator::getPosition() {
    return _position;
}

/**
 * Updates the setpoint of the elevator PID
 * @param val new position
 */
void Elevator::setPosition(float val) {
    _inRange = false;
    _posPID->setSetpoint(val);
}

/**
 * Sets the speed of the conveyor belt
 * @param val speed
 */
void Elevator::setConveyorSpeed(float val) {
    _conveyorMotor.write(mapRange(val, -1, 1, 0, 180));
}

/**
 * Whether the elevator PID is within tolerance of its setpoint
 * @return whether the elevator is within tolerance
 */
bool Elevator::withinTolerance() {
    return _posPID->withinTolerance();
}

/**
 * Updates the encoder position.
 * Called as quickly as possible by Robot
 */
void Elevator::update() {
    _position->update();

    //Get controller inputs, and set setpoints based off of them
    if(_robot->onePressed()) {
        _posPID->setSetpoint(ELEVATOR_FLOOR0);
        _inRange = false;
    } else if(_robot->twoPressed()) {
        _posPID->setSetpoint(ELEVATOR_FLOOR1);
        _inRange = false;
    } else if(_robot->threePressed()) {
        _posPID->setSetpoint(ELEVATOR_FLOOR2);
        _inRange = false;
    } else if(_robot->fourPressed()) {
        _posPID->setSetpoint(ELEVATOR_FLOOR3);
        _inRange = false;
    }

    //Get controller inputs, and set the conveyor speed
    if(_robot->downPressed()) {
        _conveyorMotor.write(mapRange(-0.5, -1, 1, 0, 180));
    } else if(_robot->upPressed()) {
        _conveyorMotor.write(mapRange(0.5, -1, 1, 0, 180));
    } else {
        _conveyorMotor.write(mapRange(0, -1, 1, 0, 180));
    }

    //Allow the driver to override elevator motor speed
    if(_robot->l2Pressed()) {
        _drumMotor.write(mapRange(0.25, -1, 1, 0, 180));
    } else if(_robot->r2Pressed()) {
        _drumMotor.write(mapRange(-0.35, -1, 1, 0, 180));
    } else {
        _drumMotor.write(mapRange(0, -1, 1, 0, 180));
    }

    //Update the speed of the elevator based on its PID
    if(!_posPID->withinTolerance() && !_inRange) {
        Serial.println("updating elevator...");
        _drumMotor.write(mapRange(constrain(_posPID->getSpeed(), -0.35, 0.15), -1, 1, 0, 180));
    } else if(!_inRange){
        _drumMotor.write(mapRange(0, -1, 1, 0, 180));

        _inRange = true;
    }
}

/**
 * Sets the robot instance
 * @param robot instance of Robot
 */
void Elevator::setRobot(Robot *robot) {
    _robot = robot;
}
