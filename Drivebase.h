#ifndef _DRIVEBASE_H_
#define _DRIVEBASE_H_

#include "Robot.h"
#include "Encoder.h"
#include "Constants.h"
#include "PID.h"

class Robot;

/**
 * The Drivebase class encapsulates all behavior performed by the drivebase.
 * The Robot class will instantiate one of these, then call its methods.
 */
class Drivebase {
private:
    //Pointer to the instance of the robot
    Robot *_robot;

    //Left and right motors
    Servo _left;
    Servo _right;

    //Left and right encoders
    Encoder *_leftDist;
    Encoder *_rightDist;

    //Driving straight PID
    PID *_distPID;

    //Turning pid
    PID *_turnPID;
public:
    Drivebase();

    void update();

    void setLeft(double speed);
    void setRight(double speed);

    void setStraightOffset(float pos);
    void setTurnOffset(float pos);

    float getLeftDist();
    float getRightDist();

    float getStraightError();
    float getTurnError();

    bool straightWithinTolerance();
    bool turnWithinTolerance();

    void resetEncoders();

    void setRobot(Robot *robot);
};

#endif
