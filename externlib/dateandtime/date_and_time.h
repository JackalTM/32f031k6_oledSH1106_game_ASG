/*
 * dateandtime.h
 *
 *  Created on: 3 gru 2024
 *      Author: User
 */

#ifndef DATEANDTIME_DATE_AND_TIME_H_
#define DATEANDTIME_DATE_AND_TIME_H_

#include "data_types.h"
#include "stdint.h"
#include "stdlib.h"

/***************************************************************************
 * @name		DateAndTime_SetDate
 * @brief		Set dateformat_t internal structure
 * @param[in]	year
 * @param[in]	moth
 * @param[in]	day
 */
void DateAndTime_SetDate(uint16_t year, uint8_t  month, uint8_t day);
#define DateAndTime_DATE_RESET	DateAndTime_SetDate(0,0,0)
//=========================================================================
/***************************************************************************
 * @name		DateAndTime_SetTime
 * @brief		Set timeformat_t internal structure
 * @param[in]	hour
 * @param[in]	minute
 * @param[in]	sec
 */
void DateAndTime_SetTime(uint8_t hour, uint8_t  minute, uint8_t sec, uint16_t msec);
#define DateAndTime_TIME_RESET DateAndTime_SetTime(0,0,0,0)
//=========================================================================

struct dateformat_t DateAndTime_GetDate(void);
struct timeformat_t DateAndTime_GetTime(void);

uint8_t DateAndTime_GetEvent(void);

void DateAndTime_IRQ_1ms_internal(void);

void DateAndTime_SetToExternal(struct timeformat_t* pTime);
void DateAndTime_IRQ_1ms_external(void);

#endif /* DATEANDTIME_DATE_AND_TIME_H_ */
