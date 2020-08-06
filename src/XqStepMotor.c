#include "XqStepMotor.h"
#include "XqGpio.h"

typedef struct XqStepMotor T;
typedef unsigned char u8;

static void do_step(T* m, char stepIndex)
{
	int i=0;
	unsigned char step = m->steps[stepIndex];
	for(i=0; i<4; i++){
		xqGpioWrite(m->pins[i], (step & (1<<i)) ? 1:0);
	}
}

/********************** API section ***************************/

void xqStepMotorInit(T* m, u8 pin1, u8 pin2, u8 pin3, u8 pin4)
{
	int i=0;
	m->pins[0] = pin1;
	m->pins[1] = pin2;
	m->pins[2] = pin3;
	m->pins[3] = pin4;

	m->dir = 1;

	m->steps[0] = 0x07;
	m->steps[1] = 0x03;
	m->steps[2] = 0x0B;
	m->steps[3] = 0x09;
	m->steps[4] = 0x0D;
	m->steps[5] = 0x0C;
	m->steps[6] = 0x0E;
	m->steps[7] = 0x06;

	for(i=0; i<4; i++){
		xqGpioSetMode(m->pins[i], OUT);
	}
}
void xqStepMotorSetDir(T* m, char dir)
{
	m->dir = (dir > 0) ? 1 : -1;
}
char xqStepMotorGetDir(T* m)
{
	return m->dir;
}
void xqStepMotorStep(T* m)
{
	static char curStep = 0;
	if(m->dir == 1){
		curStep ++;
		if(curStep > 7){
		curStep = 0;
		}
	}else{
		curStep --;
		if(curStep < 0){
			curStep = 7;
		}
	}
	do_step(m, curStep);
}

