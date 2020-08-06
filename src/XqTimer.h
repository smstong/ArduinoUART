/***************************************************************
 * Timer driver for Arduino
 * 
 * An 1 ms timer via timer0 only.
 *
 * ************************************************************/
#ifndef XQ_TIMER_H
#define XQ_TIMER_H

typedef void (*XqTimerCb)(void);

void xqTimerInit(XqTimerCb cb);
void xqTimerStart();
void xqTimerStop();

#endif
