#include "XqDs1307.h"
#include "XqI2c.h"

static int rtc_read_all(
		unsigned char* year,
		unsigned char* mon,
		unsigned char* day,
		unsigned char* dow,
		unsigned char* hour,
		unsigned char* min,
		unsigned char* second
		)
{
	if(-1==xqI2cStart()){
		return -1;
	}
	if(-1==xqI2cWriteByte(0xD0)) return -1;
	if(-1==xqI2cWriteByte(0x00)) return -1;
	xqI2cStop();

	xqI2cStart();
	if(-1 == xqI2cWriteByte(0xD1)) return -1;

	int _second, _min, _hour, _dow, _day, _mon, _year;

	_second = xqI2cReadByte(1);
	if(_second == -1) return -1;
	_min = xqI2cReadByte(1);
	if(_min == -1) return -1;
	_hour = xqI2cReadByte(1);
	if(_hour == -1) return -1;
	_dow = xqI2cReadByte(1);
	if(_dow == -1) return -1;
	_day = xqI2cReadByte(1);
	if(_day == -1) return -1;
	_mon = xqI2cReadByte(1);
	if(_mon == -1) return -1;
	_year = xqI2cReadByte(0);
	if(_year == -1) return -1;

	*second = (unsigned char)_second;
	*min = (unsigned char)_min;
	*hour = (unsigned char)_hour;
	*dow = (unsigned char)_dow;
	*day = (unsigned char)_day;
	*mon = (unsigned char)_mon;
	*year = (unsigned char)_year;

	xqI2cStop();
	return 0;
}

static int rtc_set_all(
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
	if(-1 == xqI2cWriteByte(0xD0)) return -1;
	if(-1 == xqI2cWriteByte(0x00)) return -1;
	if(-1 == xqI2cWriteByte(second)) return -1;
	if(-1 == xqI2cWriteByte(min)) return -1;
	if(-1 == xqI2cWriteByte(hour)) return -1;
	if(-1 == xqI2cWriteByte(dow)) return -1;
	if(-1 == xqI2cWriteByte(day)) return -1;
	if(-1 == xqI2cWriteByte(mon)) return -1;
	if(-1 == xqI2cWriteByte(year)) return -1;
	xqI2cStop();

	return 0;
}
	
/******************* API section ******************************/
int xqDs1307Init()
{
	xqI2cInit();
	xqI2cStart();
	if(-1==xqI2cWriteByte(0xD0)) return -1;
	if(-1==xqI2cWriteByte(0x07)) return -1;
	if(-1==xqI2cWriteByte(0x00)) return -1;
	xqI2cStop();
	return 0;
}
/* ignore the parameter with NULL value */
int xqDs1307GetTime(
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
	if(-1 == rtc_read_all(
				&_year, &_mon, &_day, &_dow, &_hour, &_min, &_second)){
		return -1;
	}

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
	return 0;
}
/* ignore the parameter with 255 value */
int xqDs1307SetTime(
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
	if(-1==xqDs1307GetTime(
				&_year, &_mon, &_day, &_dow, &_hour, &_min, &_second)){
		return -1;
	}

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
	if(-1 == rtc_set_all(_year, _mon, _day, _dow, _hour, _min, _second)){
		return -1;
	}
	return 0;
}
