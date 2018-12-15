#pragma once

#include "Encoder.h"
#include "Constants.h"

//The different possible types of PID
enum PIDType {
    NORMAL,   //A normal PID based off of one encoder
    STRAIGHT, //A PID to travel forward, while also keeping the difference between two encoders minimal.
    TURN      //A PID to turn about the VTC of the robot.
};

class Encoder;

/**
 * The PID class is used to adjust motor speeds based off of encoder position.
 */
class PID {
private:
    //The P value of the encoder and the current setpoint
    float _kp, _setpoint;

    //The tolerance of the PID
    float _tolerance = 10;

    //The two encoders to be used.
    //Note: if _type == NORMAL, _encoder2 == NULL
    Encoder *_encoder1;
    Encoder *_encoder2;

    //The type of PID this instance is
    int _type;

    float getAvgEncoders();
public:
    //Multiple constructors to allow for different kinds of PIDs.
    PID(Encoder *encoder1, Encoder *encoder2, float kp, PIDType type);
    PID(Encoder *encoder, float kp, PIDType type) : PID(encoder, NULL, kp, type) {};
    PID(Encoder *encoder, float kp) : PID(encoder, NULL, kp, NORMAL) {};

    void setSetpoint(float val);
    void setTolerance(float val);

    float getError();
    float getSpeed();

    bool withinTolerance();
};
