/***************************************************************
 * Step Motor Driver for Arduino
 * 
 * only for 28BYJ-48 now.
 * ************************************************************/
#ifndef XQ_STEP_MOTOR_H
#define XQ_STEP_MOTOR_H

typedef struct XqStepMotor
{
	char dir;		/* 1: clockwise, -1: counter colock */
	unsigned char pins[4];
	unsigned char steps[8];
}XqStepMotor;

void xqStepMotorInit(
		XqStepMotor* m,
		unsigned char pin1,
		unsigned char pin2,
		unsigned char pin3,
		unsigned char pin4);

void xqStepMotorSetDir(XqStepMotor* m, char dir);
char xqStepMotorGetDir();
void xqStepMotorStep(XqStepMotor* m);

#endif
