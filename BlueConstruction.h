#pragma once

#include "Robot.h"

enum BlueConstructionState {
    FORWARD1,
    NEW,
    TURN1,
    FORWARD2,
    DEPOSIT_ELEVATOR,
    DEPOSIT_CONVEYOR,
    DRIVE_BACK
};

class Robot;
class Drivebase;
class Elevator;

/**
 * The auto routine to enter the blue construction zone
 * and deliver a PIZZA to FARADAY.
 */
class BlueConstruction {
private:
    //The current state that the auto is in
    BlueConstructionState _autoState = FORWARD1;

    //Pointer to the instance of the robot
    Robot *_robot;

    //Pointer to the instance of the drivebase and elevator
    Drivebase *_drivebase;
    Elevator *_elevator;

    //Whether this is the first pass through the auto
    bool _firstIter = true;

    int _startMillis = 0;
public:
    BlueConstruction(Robot *_robot);

    void run();

    //Old PID version, with a dummy parameter so that the code still compiles.
    void run(int dummy);
};
