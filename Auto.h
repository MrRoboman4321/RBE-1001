#ifndef _AUTONOMOUS_H_
#define _AUTONOMOUS_H_

#include "Robot.h"
#include "BlueConstruction.h"

class Robot;
class BlueConstruction;

/**
 * The auto class is used to select autos based on jumper position
 * It will create an instance of different classes, corresponding
 * to the different autos we want to run.
 * We were planning on having more autos (Red and Blue Faraday and Construction),
 *   but we ran out of time before the OED.
 */
class Auto {
private:
    int _test;
    Robot *_robot;

    bool _firstIter = true;

    BlueConstruction *_bC;
public:
    Auto(Robot *robot);

    //Determines which auto we want to run, then call the respective function.
    void runAuto();

    //Each function here will call the run() method of the respective auto.
    void redConstruction();
    void redFaraday();

    void blueConstruction();
    void blueFaraday();
};

#endif
