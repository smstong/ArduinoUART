/***************************************************************
 * Timer driver for Arduino
 * 
 * An 100 us timer via timer0 only.
 *
 * Make sure ISR can be done within 100 us (100*16=1600 clks)
 *
 * ************************************************************/
#ifndef XQ_TIMER_H
#define XQ_TIMER_H

typedef void (*XqTimerCb)(void* arg);

/* return: then cb's index */
int XqTimerAddCb(XqTimerCb cbf, void* arg);

void xqTimerStart();
void xqTimerStop();

#endif
