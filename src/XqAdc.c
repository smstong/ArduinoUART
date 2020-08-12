#include "XqAdc.h"
#include <avr/interrupt.h>
#include "XqGpio.h"

typedef unsigned char u8;
typedef unsigned int u16;
#define MAX_ADC_PINS 6

static void on_adc(u16 r);

ISR(ADC_vect)
{
	u8 L = ADCL;
	u8 H = ADCH;
	u16 r = L + ((H&0x03)<<8);
	on_adc(r);
}

/* a pair of (pin, vref) */
struct AdcPair{
	u8 pin;
	u8 vref;
	XqAdcCb onRead;
};

static u8 adcPins = 0; /* input Pins count */
static struct AdcPair adcPairs[MAX_ADC_PINS];

static void adc_add_pair(u8 pin, u8 vref, XqAdcCb cb)
{
	xqGpioSetMode(pin, IN);

	adcPairs[adcPins].pin = pin;
	adcPairs[adcPins].vref = vref;
	adcPairs[adcPins].onRead = cb;
	adcPins++;
}

/* Enable pair by selecting its vref and pin */
static void adc_select_pair(struct AdcPair pair)
{
	u8 C = 0; 
	C |= (pair.pin-A0);
	C |= (pair.vref<<6);
	ADMUX = C;
}

static void on_adc(u16 r)
{
	/* select next pair */
	static u8 curPair = 0;
	if(adcPairs[curPair].onRead){
		adcPairs[curPair].onRead(r);
	}
	curPair ++;
	if(curPair > adcPins-1){
		curPair = 0;
	}
	adc_select_pair(adcPairs[curPair]);	
	
	/* start convert */
	ADCSRA |= (1<<ADSC);
}

static void adc_init()
{
	ADCSRA = 0x8F;	
	sei();
}
/********************** API section ***************************/
/*
 * pin: A0,...,A5
 * vref: 0-AREF pin, 1-AVcc, 3-internal 1.1
*/
void xqAdcAdd(u8 pin, u8 vref, XqAdcCb cb)
{
	adc_add_pair(pin, vref, cb);
}

void xqAdcStart()
{
	adc_init();
	if(adcPins == 0) return;
	adc_select_pair(adcPairs[0]);	
	ADCSRA |= (1<<ADSC);
}
