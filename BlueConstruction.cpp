#include "BlueConstruction.h"

BlueConstruction::BlueConstruction(Robot *robot) {
    _robot = robot;
    _drivebase = _robot->getDrivebase();
    _elevator = _robot->getElevator();

    _elevator->setPosition(ELEVATOR_FLOOR1-200);
}

/**
 * The run method is called as fast as possible during auto.
 * This is the encoder + PID version of thd drivebase, which we would have used if
 *   we had succeeded in getting the encoders functional.
 */
void BlueConstruction::run() {
    //Depending on which state we're in, run different routines
    switch(_autoState) {
        case FORWARD1: {
            if(_firstIter) {
                _drivebase->setStraightOffset(BLUE_CONSTRUCTION_FORWARD1_DIST);
                _firstIter = false;
            }
            float error = _drivebase->getStraightError();
            _drivebase->setLeft(BLUE_CONSTRUCTION_DRIVE_SPEED + error);
            _drivebase->setRight(-BLUE_CONSTRUCTION_DRIVE_SPEED + error);

            if(_drivebase->straightWithinTolerance()) {
                _autoState = TURN1;
                _firstIter = true;
            }
            break;
        } case TURN1: {
            if(_firstIter) {
                _drivebase->setTurnOffset(BLUE_CONSTRUCTION_TURN1_ANGLE);
                _firstIter = false;
            }
            float error = _drivebase->getTurnError();
            _drivebase->setLeft(BLUE_CONSTRUCTION_TURN_SPEED + error);
            _drivebase->setRight(BLUE_CONSTRUCTION_DRIVE_SPEED - error);
            if(_drivebase->turnWithinTolerance()) {
                _autoState = FORWARD2;
                _firstIter = true;
            }
            break;
        } case FORWARD2: {
            if(_firstIter) {
                _drivebase->setStraightOffset(BLUE_CONSTRUCTION_FORWARD2_DIST);
                _firstIter = false;
            }
            float error = _drivebase->getStraightError();
            _drivebase->setLeft(BLUE_CONSTRUCTION_DRIVE_SPEED + error);
            _drivebase->setRight(-BLUE_CONSTRUCTION_DRIVE_SPEED + error);

            if(_drivebase->straightWithinTolerance()) {
                _autoState = TURN1;
                _firstIter = true;
            }
            break;
        } case DEPOSIT_ELEVATOR: {
            if(_firstIter) {
                _elevator->setPosition(ELEVATOR_FLOOR1);
                _firstIter = false;
            }
            _elevator->update();
            if(_elevator->withinTolerance()) {
                _autoState = DEPOSIT_CONVEYOR;
                _firstIter = true;
            }
            break;
        } case DEPOSIT_CONVEYOR: {
            _elevator->setConveyorSpeed(CONVEYOR_SPEED);
        }
        default:
            //We should never see a state that's not in State, so report an error
            _robot->setLCDString(&String("BConstruction"), &String("broken!"));
    }
}

/**
 * This is the dead reckoned version of the auto. We would drive
 *   for a specific number of milliseconds, then progress to the next State.
 * This was due to the fact that we could not get the encoders working on the drivebase.
 */
void BlueConstruction::run() {
    if(_firstIter) {
        _startMillis = millis();
        _firstIter = false;
    }

    //Depending on which state we're in, run different routines
    switch(_autoState) {
        case FORWARD1: {
            if(millis() - _startMillis > BLUE_CONSTRUCTION_FORWARD1_DIST) {
                _startMillis = millis();
                _autoState = NEW;
                _elevator->setPosition(ELEVATOR_FLOOR2);
            }

            _elevator->update();
            _elevator->setConveyorSpeed(0.5);

            _drivebase->setLeft(0.45);
            _drivebase->setRight(0.45);

            break;
        } case NEW: {
            if(millis() - _startMillis > BLUE_CONSTRUCTION_NEW_DIST) {
                _startMillis = millis();
                _autoState = TURN1;
            }

            _elevator->update();

            _drivebase->setLeft(0.5);
            _drivebase->setRight(0.5);

            break;
        } case TURN1: {
            if(millis() - _startMillis > BLUE_CONSTRUCTION_TURN1_ANGLE) {
                _startMillis = millis();
                _autoState = FORWARD2;
            }

            _drivebase->setLeft(-BLUE_CONSTRUCTION_TURN_SPEED);
            _drivebase->setRight(1);

            break;
        } case FORWARD2: {
            _drivebase->setLeft(BLUE_CONSTRUCTION_DRIVE_SPEED);
            _drivebase->setRight(BLUE_CONSTRUCTION_DRIVE_SPEED);

            if(millis() - _startMillis > BLUE_CONSTRUCTION_FORWARD2_DIST) {
                _startMillis = millis();
                _autoState = DEPOSIT_ELEVATOR;

                _drivebase->setLeft(0);
                _drivebase->setRight(0);
            }
            break;
        } case DEPOSIT_ELEVATOR: {
            _elevator->update();
            if(_elevator->withinTolerance()) {
                _autoState = DEPOSIT_CONVEYOR;
                _firstIter = true;
                _startMillis = millis();
            }

            _elevator->setPosition(ELEVATOR_FLOOR1);
            break;
        } case DEPOSIT_CONVEYOR: {
            _elevator->setConveyorSpeed(CONVEYOR_SPEED);
            if(millis() - _startMillis > 1500) {
                _startMillis = millis();
                _drivebase->setLeft(-0.5);
                _drivebase->setRight(-0.5);
                _autoState = DRIVE_BACK;
            }
        } case DRIVE_BACK: {
            if(millis() - _startMillis > 1000) {
                _drivebase->setLeft(0);
                _drivebase->setRight(0);
                _elevator->setConveyorSpeed(0);
            }
        }
        default:
            //We should never see a state that's not in State, so report an error
            _robot->setLCDString(&String("BConstruction"), &String("broken!"));
    }
}