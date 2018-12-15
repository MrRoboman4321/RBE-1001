#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <DFW.h>
#include <AbstractDFWRobot.h>

#include <Servo.h>
#include <LiquidCrystal.h>

#include "Auto.h"
#include "Drivebase.h"
#include "Elevator.h"
#include "PID.h"

class Auto;

class Drivebase;
class Elevator;

//Represents both game periods, AUTO and TELEOP
enum Period {
	AUTO,
	TELEOP
};

/**
 * The entry point into the Robot software.
 * Instantiates different subsystems, and manages what is happening during different game periods.
 */
class Robot : public AbstractDFWRobot {
private:
	//Auto selector
	Auto *_autonomous;

	//The two main robot subsystems
	Drivebase *_drivebase;
	Elevator *_elevator;

	//Current strings to display on the LCD
	String *_toDisplay1;
	String *_toDisplay2;

	//LCD pin parameters
	const int rs = 47, en = 48, d4 = 49, d5 = 50, d6 = 51, d7 = 52;

	//Instance of LCD
	LiquidCrystal *_lcd;

	//Current game period (instanceof Period)
	int _period;
public:
	//Pointer to the DFW base class
	DFW *dfw;

	void robotStartup();

	void autonomous(long time);
	void teleop(long time);

	void robotShutdown(void);

	//Returns the pin that the Arduino LED pin is connected to.
	int getDebugLEDPin(void) {
	    return 13;
	};

	double getLeftJoy();
	double getRightJoy();

	bool upPressed();
	bool downPressed();
	bool l2Pressed();
	bool r2Pressed();
	bool onePressed();
	bool twoPressed();
	bool threePressed();
	bool fourPressed();

	Drivebase *getDrivebase();
	Elevator *getElevator();

	void setLCDString(String *line1, String *line2);
	void setLCDString(String *line);

	int getGamePeriod();

	Robot();
};

#endif
