/***************************************************************
 *
 * Servo driver for Arduino
 *
 * ************************************************************/
#ifndef _XQ_SERVO_H
#define _XQ_SERVO_H

typedef struct XqServo
{
	unsigned int pinPWM;	/* PWM intput pin */
	float angle;			/* current position */

	unsigned int cycle_us;   /* for SG90, it's 20000 (20ms) */
	unsigned int duty_min_us; /* min duty us, for SG90, it's 500 */
	unsigned int duty_max_us; /* for SG90, it's 2400 */

	unsigned int clicks_per_us;

	unsigned int duty_clicks; /* timer clicks for duty */
	unsigned int cycle_clicks; /* cycle_us / clicks_per_us */
	unsigned int clicks;	/* record clicks */

} XqServo;

void xqServoInit(XqServo* m, unsigned char pinPWM);
void xqServoSetPos(XqServo* m, float angle);
float xqServoGetPos(XqServo* m);

#endif /* #ifdef _XQ_SERVO_H */
