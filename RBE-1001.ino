  #include <DFW.h>
#include "Robot.h"

Robot *myRobotInstance;
DFW* dfw; // Declares the DFW object

void setup() {
	Serial.begin(9600); // Serial output begin. Only needed for debug
    myRobotInstance = new Robot();
    dfw = new DFW(myRobotInstance); //Instantiates the DFW object with the robot instance
	dfw->begin(); // Serial1 output begin for DFW library. Buad and port #."Serial1 only"
	myRobotInstance->dfw=dfw;// add a reference to the controller to your robot. this lets you control your robot
}

/**
 * Let the DFW call the robot methods
 */
void loop() {
	dfw->run();
} 
