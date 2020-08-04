#include "XqDs1307.h"
#include "XqI2c.h"

static void rtc_read_all(
		unsigned char* year,
		unsigned char* mon,
		unsigned char* day,
		unsigned char* dow,
		unsigned char* hour,
		unsigned char* min,
		unsigned char* second
		)
{
	xqI2cStart();
	xqI2cWriteByte(0xD0);
	xqI2cWriteByte(0x00);
	xqI2cStop();

	xqI2cStart();
	xqI2cWriteByte(0xD1);

	*second = xqI2cReadByte(1);
	*min = xqI2cReadByte(1);
	*hour = xqI2cReadByte(1);
	*dow = xqI2cReadByte(1);
	*day = xqI2cReadByte(1);
	*mon = xqI2cReadByte(1);
	*year = xqI2cReadByte(0);
	xqI2cStop();
}

static void rtc_set_all(
		unsigned char year,
		unsigned char mon,
		unsigned char day,
		unsigned char dow,
		unsigned char hour,
		unsigned char min,
		unsigned char second
		)
{
	xqI2cStart();
	xqI2cWriteByte(0xD0);
	xqI2cWriteByte(0x00);
	xqI2cWriteByte(second);
	xqI2cWriteByte(min);
	xqI2cWriteByte(hour);
	xqI2cWriteByte(dow);
	xqI2cWriteByte(day);
	xqI2cWriteByte(mon);
	xqI2cWriteByte(year);
	xqI2cStop();
}
	
/******************* API section ******************************/
void xqDs1307Init()
{
	xqI2cInit();
	xqI2cStart();
	xqI2cWriteByte(0xD0);
	xqI2cWriteByte(0x07);
	xqI2cWriteByte(0x00);
	xqI2cStop();
}
/* ignore the parameter with NULL value */
void xqDs1307GetTime(
		unsigned char* year,
		unsigned char* mon,
		unsigned char* day,
		unsigned char* dow,
		unsigned char* hour,
		unsigned char* min,
		unsigned char* second
		)
{
	unsigned char _year, _mon, _day, _dow, _hour, _min, _second;
	rtc_read_all(&_year, &_mon, &_day, &_dow, &_hour, &_min, &_second);

	if(year){
		*year = (_year & 0x0F) + (_year>>4)*10;
	}
	if(mon){
		*mon = (_mon & 0x0F) + (_mon>>4)*10;
	}
	if(day){
		*day = (_day & 0x0F) + (_day>>4)*10;
	}
	if(dow){
		*dow = (_dow & 0x0F) + (_dow>>4)*10;
	}
	if(hour){
		*hour = (_hour & 0x0F) + (_hour>>4)*10;
	}
	if(min){
		*min = (_min & 0x0F) + (_min>>4)*10;
	}
	if(second){
		*second = (_second & 0x0F) + (_second>>4)*10;
	}
}
/* ignore the parameter with 255 value */
void xqDs1307SetTime(
		unsigned char year,
		unsigned char mon,
		unsigned char day,
		unsigned char dow,
		unsigned char hour,
		unsigned char min,
		unsigned char second
		)
{
	unsigned char _year, _mon, _day, _dow, _hour, _min, _second;
	xqDs1307GetTime(&_year, &_mon, &_day, &_dow, &_hour, &_min, &_second);

	if(year != 0xFF){
		_year = ((year / 10) << 4) + (year % 10);
	}
	if(mon != 0xFF){
		_mon = ((mon / 10) << 4) + (mon % 10);
	}
	if(day != 0xFF){
		_day = ((day / 10) << 4) + (day % 10);
	}
	if(dow != 0xFF){
		_dow = ((dow / 10) << 4) + (dow % 10);
	}
	if(hour != 0xFF){
		_hour = ((hour / 10) << 4) + (hour % 10);
	}
	if(min != 0xFF){
		_min = ((min / 10) << 4) + (min % 10);
	}
	if(second != 0xFF){
		_second = ((second / 10) << 4) + (second % 10);
	}
	rtc_set_all(_year, _mon, _day, _dow, _hour, _min, _second);
}
