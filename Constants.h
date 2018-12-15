#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

/**
 * The constants file is used to eliminate magic numbers from the code.
 * Many classes include this file, then use values #defined by it.
 */

//Motor and sensor parameters
//Drive: Motor port
//Pos[A/B]: Encoder ports

//Drivebase parameters
#define LEFT_DRIVE 5
#define LEFT_POS_A 26
#define LEFT_POS_B 27

#define RIGHT_DRIVE 4
#define RIGHT_POS_A 28
#define RIGHT_POS_B 29

//Elevator parameters
#define ELEVATOR_DRIVE 7
#define CONVEYOR_DRIVE 6
#define ELEVATOR_POS A1

//END MOTOR AND SENSOR PARAMETERS


//Elevator encoder positions

#define ELEVATOR_FLOOR0 1000
#define ELEVATOR_FLOOR1 878
#define ELEVATOR_FLOOR2 338
#define ELEVATOR_FLOOR3 0

//END ELEVATOR ENCODER POSITIONS


//PID parameters

//The tolerance for the straight and turn PIDs.
#define DRIVEBASE_STRAIGHT_TOLERANCE 10
#define DRIVEBASE_TURN_TOLERANCE 10

//The P value for driving straight
#define DRIVEBASE_FORWARD_P 0

//The P value for point turns
#define DRIVEBASE_TURN_P 0

//The P value for the elevator position
#define ELEVATOR_P 0.001

//END PID PARAMETERS


//Auto Parameters
#define CONVEYOR_SPEED 1

//All of these parameters, with the exception of SPEEDs, are in ms.
#define BLUE_CONSTRUCTION_DRIVE_SPEED 0.5
#define BLUE_CONSTRUCTION_TURN_SPEED 0.5
#define BLUE_CONSTRUCTION_FORWARD1_DIST 5.5*1000
#define BLUE_CONSTRUCTION_NEW_DIST 2.25*1000
#define BLUE_CONSTRUCTION_TURN1_ANGLE 1*1000
#define BLUE_CONSTRUCTION_FORWARD2_DIST 2.3*1000
#define BLUE_CONSTRUCTION_ELEVATOR_POS ELEVATOR_FLOOR1

#endif