#ifndef _ELEVATOR_H_
#define _ELEVATOR_H_

#include "Robot.h"
#include "Constants.h"
#include "PotEncoder.h"
#include "PID.h"

class Robot;
class Encoder;

/**
 * The Elevator class encapsulates all behavior performed by the elevator.
 * The Robot class will instantiate one of these, then call its methods.
 */
class Elevator {
private:
    //Pointer to the instance of the robot
    Robot *_robot;

    //Drum and conveyor motor
    Servo _drumMotor, _conveyorMotor;

    //Drum encoder
    PotEncoder *_position;

    //Whether or not the elevator is currently within range of its setpoint
    bool _inRange = false;

    //PID to control elevator motor speed
    PID *_posPID;
public:
    Elevator();

    void setRobot(Robot *robot);

    void setSpeed(float speed);

    int getPosition();
    void setPosition(float val);

    void setConveyorSpeed(float speed);

    bool withinTolerance();

    void update();

    void resetEncoders();
};

#endif
