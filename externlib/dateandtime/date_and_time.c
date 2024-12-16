/*
 * dateandtime.c
 *
 *  Created on: 3 gru 2024
 *      Author: User
 */
#include "date_and_time.h"

static struct dateformat_t _dataformat = {0,0,0};
static struct timeformat_t _timeformat = {0,0,0,0};
static struct timeformat_t *_p_timeformat = NULL;
static uint8_t _event_update = 0x00;

/***************************************************************************
 * @name
 * @brief
 * @param[in]
 * @param[in]
 * @param[in]
 * @note
 * @return
 */
//==========================================================================


/***************************************************************************
 * @name		DateAndTime_SetDate
 * @brief		Set dateformat_t internal structure
 * @param[in]	year
 * @param[in]	moth
 * @param[in]	day
 */
void DateAndTime_SetDate(uint16_t year, uint8_t  month, uint8_t day)
{
	_dataformat.year = year;
	_dataformat.month = month;
	_dataformat.day = day;
}
//==========================================================================

/***************************************************************************
 * @name		DateAndTime_SetTime
 * @brief		Set timeformat_t internal structure
 * @param[in]	hour
 * @param[in]	minute
 * @param[in]	sec
 */
void DateAndTime_SetTime(uint8_t hour, uint8_t  minute, uint8_t sec, uint16_t msec)
{
	_timeformat.hour = hour;
	_timeformat.minute = minute;
	_timeformat.second = sec;
	_timeformat.msec = msec;
}
//==========================================================================

/***************************************************************************
 * @name		DateAndTime_GetDate
 * @brief		return current value of struck dateformat_t
 * @note
 * @return		struck dateformat_t
 */
struct dateformat_t DateAndTime_GetDate(void)
{ 	return _dataformat; }
//==========================================================================

/***************************************************************************
 * @name		DateAndTime_GetTime
 * @brief		return current value of struck dateformat_t
 * @note
 * @return		struck timeformat_t
 */
struct timeformat_t DateAndTime_GetTime(void)
{ 	return _timeformat; }
//==========================================================================

void DateAndTime_IRQ_1ms_internal(void)
{
	if( ++_timeformat.msec < TIMEFORMAT_MS_MAX) return;
	else{	_timeformat.msec = 0;	}

	if( ++_timeformat.second < TIMEFORMAT_SECONDS_MAX) return;
	else{	_timeformat.second = 0;	_event_update = 0xFF;}

	if( ++_timeformat.minute < TIMEFORMAT_MINUTES_MAX) return;
	else{	_timeformat.minute = 0;	}

	if( ++_timeformat.hour < TIMEFORMAT_HOURS_MAX) return;
	else{	_timeformat.hour = 0;	}

	_dataformat.day++;
}

uint8_t DateAndTime_GetEvent(void)
{
	uint8_t tevent = _event_update;

	if(tevent == 0xFF)
	{
		_event_update = 0x00;
		return 0xFF;
	}
	else
		return 0x00;
}
void DateAndTime_SetToExternal(struct timeformat_t* pTime)
{
	_p_timeformat = pTime;
}
void DateAndTime_IRQ_1ms_external(void)
{
	if(_p_timeformat == NULL) return;
	else{;}

	if( ++(_p_timeformat->msec) < TIMEFORMAT_MS_MAX) return;
	else{	_p_timeformat->msec = 0;	}

	if( ++(_p_timeformat->second) < TIMEFORMAT_SECONDS_MAX) return;
	else{	_p_timeformat->second = 0;	}

	if( ++(_p_timeformat->minute) < TIMEFORMAT_MINUTES_MAX) return;
	else{	_p_timeformat->minute = 0;	}

	if( ++(_p_timeformat->hour) < TIMEFORMAT_HOURS_MAX) return;
	else{	_p_timeformat->hour = 0;	}
}
