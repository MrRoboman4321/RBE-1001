#include "Auto.h"

Auto::Auto(Robot *robot) {
    _robot = robot;

    pinMode(40, INPUT_PULLUP);
    pinMode(41, INPUT_PULLUP);
    pinMode(42, INPUT_PULLUP);
    pinMode(43, INPUT_PULLUP);

    _bC = new BlueConstruction(_robot);
}

void Auto::runAuto() {
    if(digitalRead(40) == LOW) {
        blueConstruction();
    } else if(digitalRead(41) == LOW) {
        blueFaraday();
    } else if(digitalRead(42) == LOW) {
        redConstruction();
    } else if(digitalRead(43) == LOW) {
        redFaraday();
    }
}

void Auto::blueConstruction() {
    if(_firstIter) {
        _robot->setLCDString(&String("BlueConstruction"));
        _firstIter = false;
    }

    _bC->run();
}

void Auto::blueFaraday() {
    if(_firstIter) {
        _robot->setLCDString(&String("Blue Faraday"));
        _firstIter = false;
    }
}

void Auto::redConstruction() {
    if(_firstIter) {
        _robot->setLCDString(&String("Red Construction"));
        _firstIter = false;
    }

    //_rC->run();
}

void Auto::redFaraday() {
    if(_firstIter) {
        _robot->setLCDString(&String("Red Faraday"));
        _firstIter = false;
    }
}