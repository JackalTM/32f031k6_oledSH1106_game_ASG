/*
 * dataconvert.h
 *
 *  Created on: 4 gru 2024
 *      Author: User
 */

#ifndef DATEANDTIME_DATA_CONVERT_H_
#define DATEANDTIME_DATA_CONVERT_H_

#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "data_types.h"

#define CONVERSION_TYPE_DEC_uint8_t 4U
#define CONVERSION_TYPE_DEC_uint16_t 6U
#define CONVERSION_TYPE_DEC_uint32_t 10U

#define CONVERSION_TYPE_DEC_int8_t 5U
#define CONVERSION_TYPE_DEC_int16_t 7U
#define CONVERSION_TYPE_DEC_int32_t 11U

#define CONVERSION_TYPE_ASCI_HEX_BASE ('A' - 0xA)

#define CONVERSION_TIME_STR_LEN (9)

/*****************************************************************************
 * enum for data lenght widhout carraige return
 */
enum OctalNumberStringSize
{// Lenght with carriage return
    TYPE_OCT_time_t = 3U,
    TYPE_OCT_uin8_t = 6U, TYPE_OCT_int8_t = 7U,
    TYPE_OCT_uint16_t = 8U, TYPE_OCT_int16_t = 9U,
    TYPE_OCT_uint32_t = 12U, TYPE_OCT_int32_t = 13U,
};
enum DecimalNumberStringSize
{// Lenght with carriage return
    TYPE_DEC_time_t = 3U,
    TYPE_DEC_uin8_t = 4U, TYPE_DEC_int8_t = 5U,
    TYPE_DEC_uint16_t = 6U, TYPE_DEC_int16_t = 7U,
    TYPE_DEC_uint32_t = 10U, TYPE_DEC_int32_t = 11U,
};
enum HexadeciNumberStringSize
{// Lenght with carriage return
    TYPE_HEX_uin8_t = 3U, TYPE_HEX_int8_t = 3U,
    TYPE_HEX_uint16_t = 5U, TYPE_HEX_int16_t = 5U,
    TYPE_HEX_uint32_t = 8U, TYPE_HEX_int32_t = 8U
};
//=============================================================================
char* CUST_CONV_uint_itoa(unsigned int num, char* p_buffer, unsigned int base);

// Conversion methods
unsigned int CUST_CONV_NumToString_oct(uint8_t number, char arrChar[], enum OctalNumberStringSize lenght);      // Fill left
unsigned int CUST_CONV_NumToString_dec(uint8_t number, char arrChar[], enum DecimalNumberStringSize lenght);    // Fill left
unsigned int CUST_CONV_NumToString_hex(uint8_t number, char arrChar[], enum HexadeciNumberStringSize lenght);   // Fill left

void CUST_CONV_StrFormatToRight(char arrSRC[], uint8_t lenSRC, char arrDST[], uint8_t lenDST, char c);
void CUST_CONV_StrFormatToRight_filterHEX(char arrSRC[], uint8_t lenSRC, char arrDST[], uint8_t lenDST, char c);

// Time to string formating
void CUST_CONV_TimeToStr_hh_mm_ss_struct(struct timeformat_t *pTime, char arrChar[]);
void CUST_CONV_TimeToStr_hh_mm_ss_args(uint8_t hour, uint8_t minute, uint8_t second, char pBuffer[]);

#endif /* DATEANDTIME_DATA_CONVERT_H_ */
