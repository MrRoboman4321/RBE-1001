#include "Robot.h"
#include "Arduino.h"

#include <DFW.h>

/**
 * The Robot constructor.
 * Initializes subsystems, autonomous, and the LCD.
 */
Robot::Robot() {
    //Instantiate the subsystems
    _drivebase = new Drivebase();
    _elevator = new Elevator();

    //Instantiate the autonomous selector
    _autonomous = new Auto(this);

    //Setup the LCD
    _lcd = new LiquidCrystal(rs, en, d4, d5, d6, d7);
    _lcd->begin(16, 2);

    //Let the operator know the robot successfully started up
    setLCDString(&String("Booted up."), &String("It's pizza time"));

}

/**
 * Called when the start button is pressed and the robot control begins
 */
void Robot::robotStartup() {
    _drivebase->setRobot(this);
    _elevator->setRobot(this);
}

/**
* Called by the controller between communication with the wireless controller
* during autonomous mode
* @param time the amount of time remaining
* @param dfw instance of the DFW controller
*/
void Robot::autonomous(long time) {
    _period = AUTO;

	//Run the autonomous routine, determined by jumper configuration on the robot.
    _autonomous->runAuto();
}

/**
* Called by the controller between communication with the wireless controller
* during teleop mode
* @param time the amount of time remaining
* @param dfw instance of the DFW controller
*/
void Robot::teleop(long time) {
    _period = TELEOP;
    _drivebase->update();
    _elevator->update();
}

/**
 * Called at the end of control to reset the objects for the next start.
 * Also turns off all motors
*/
void Robot::robotShutdown(void){
	setLCDString(&String("Waiting..."));
	_drivebase->setLeft(0);
	_drivebase->setRight(0);
	_elevator->setSpeed(0);
	_elevator->setConveyorSpeed(0);
}

/**
 * Get the left joystick position [0, 180]
 * @return left joystick position
 */
double Robot::getLeftJoy() {
    return (double) dfw->joysticklv();
}

/**
 * Get the right joystick position [0, 180]
 * @return right joystick position
 */
double Robot::getRightJoy() {
    return (double) dfw->joystickrv();
}

/**
 * The following methods are just pass-throughs to DFW calls,
 *   so that each subsystem need only access to the instance of Robot, not the dfw
 * @return
 */
bool Robot::downPressed() {
    return dfw->down();
}

bool Robot::upPressed() {
    return dfw->up();
}

bool Robot::l2Pressed() {
    return dfw->l2();
}

bool Robot::r2Pressed() {
    return dfw->r2();
}

bool Robot::onePressed() {
    return dfw->one();
}

bool Robot::twoPressed() {
    return dfw->two();
}

bool Robot::threePressed() {
    return dfw->three();
}

bool Robot::fourPressed() {
    return dfw->four();
}

/**
 * Give access to the Drivebase. Mainly utilized in Autos
 * @return the instance of drivebase
 */
Drivebase * Robot::getDrivebase() {
    return _drivebase;
}

/**
 * Give access to the Elevator. Mainly utilized in Autos
 * @return the instance of elevator
 */
Elevator * Robot::getElevator() {
    return _elevator;
}
/**
 * Helper function to the other setLCDString, allows for single line debugging.
 * @param line
 */
void Robot::setLCDString(String *line) {
    //Just call the other version, with line2 as a blank string.
    setLCDString(line, &String(""));
}

/**
 * Set the current debug message of the LCD screen.
 * @param line1 String for the first line of the display
 * @param line2 String for the second line of the display
 */
void Robot::setLCDString(String *line1, String *line2) {
    _toDisplay1 = line1;
    _toDisplay2 = line2;

    _lcd->clear();

    //Move to the first line
    _lcd->setCursor(0, 0);

    //Write the first line to the screen
    _lcd->print(*_toDisplay1);

    //Move to the second line
    _lcd->setCursor(0, 1);

    //Write the second line to the screen
    _lcd->print(*_toDisplay2);
}

/**
 * Get the current game period
 * @return current game period
 */
int Robot::getGamePeriod() {
    return _period;
}
