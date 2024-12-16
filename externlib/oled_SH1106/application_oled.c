/*
 * x_call_test.c
 *
 *  Created on: Nov 28, 2024
 *      Author: User
 */
#include "application_oled.h"

static char _team = ' ';
//static char _arrchar[16];
static struct timeformat_t _timeRED = {00,00,00,00};
static struct timeformat_t _timeBLU = {00,00,00,00}; // SH1106_Puts("WORLD !!", &Font_11x18, 1);

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
 * @name		ApplicationOLED_Init
 * @brief		Initialization of a OLED SH1106
 * @note		This has to be done before usage
 */
void ApplicationOLED_Init(void)
{
	SH1106_Init();
	SH1106_Clear();
}
//==========================================================================

/***************************************************************************
 * @name
 * @brief
 * @param[in]
 * @param[in]
 * @param[in]
 * @note
 * @return
 */
void ApplicationOLED_screen_twoteams(struct timeformat_t teamActive, struct timeformat_t teamPasive, char* pteamLeding)
{
	char pBuffer[16];

	SH1106_GotoXY(1, 0);
	SH1106_Puts(pteamLeding, &Font_11x18, 1);

	CUST_CONV_TimeToStr_hh_mm_ss_struct(&teamActive, pBuffer);
	SH1106_GotoXY(1, 20);
	SH1106_Puts((char*)(pBuffer+0), &Font_11x18, 1);

	CUST_CONV_TimeToStr_hh_mm_ss_struct(&teamPasive, pBuffer);
	SH1106_GotoXY(1, 40);
	SH1106_Puts(pBuffer, &Font_7x10, 1);

	SH1106_UpdateScreen();
}
//==========================================================================

#define APPLICATION_OLED_WIDH_Font_7x10	((128 / 10) + 1)
#define APPLICATION_OLED_WIDH_Font_11x18 ((128 / 18) + 1)
#define APPLICATION_OLED_WIDH_Font_16x26 ((128 / 26) + 1)

/***************************************************************************
 * @name		ApplicationOLED_screen_teamtaking
 * @brief
 * @param[in]
 * @param[in]
 * @param[in]
 * @note
 * @return
 */
void ApplicationOLED_screen_teamtaking(char* pteamLeding, uint8_t n, uint8_t max_n)
{
	char pbufer[APPLICATION_OLED_WIDH_Font_11x18];
	uint8_t i;
	SH1106_GotoXY(1, 0);
	SH1106_Puts("Przejmowanie", &Font_11x18, 1);

	if(n>8) n=8;
	else{;}

	for(i=0; i<n; i++)
		pbufer[i] = '#';

	SH1106_GotoXY(1, 30);
	SH1106_Puts(pbufer, &Font_11x18, 1);

	SH1106_UpdateScreen();
}
//==========================================================================

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

void ApplicationOLED_PrintTime(struct timeformat_t* pTime, uint8_t x, uint8_t y)
{
	char pBuffer[16];
	SH1106_GotoXY(x, y);
	CUST_CONV_TimeToStr_hh_mm_ss_struct(pTime, pBuffer);
	SH1106_Puts(pBuffer, &Font_11x18, 1);
}

void ApplicationOLED_TwoTeams(void)
{
	static uint8_t _n=0;
	if(DateAndTime_GetEvent() == 0xFF)
	{
		switch (_team)
		{
		case 'R':
			SH1106_DrawLine(1, 17, 	128, 17, 	1);
			SH1106_DrawLine(1, 39, 	128, 39, 	0);
			DateAndTime_SetToExternal(&_timeRED);
			_team = 'N';
			_n=0;
			break;

		case 'B':
			SH1106_DrawLine(1, 17, 	128, 17, 	0);
			SH1106_DrawLine(1, 39, 	128, 39, 	1);
			DateAndTime_SetToExternal(&_timeBLU);
			_team = 'M';
			_n=0;
			break;

		case 'N':
			if(++_n > 59)
			{
				_n=0;
				_team = 'B';
			}else{;}
			break;

		case 'M':
			if(++_n > 59)
			{
				_n=0;
				_team = 'R';
			}else{;}
			break;

		default:
			break;
		}
		struct timeformat_t ttime = DateAndTime_GetTime();

		ApplicationOLED_PrintTime(&_timeRED, 33,0);
		ApplicationOLED_PrintTime(&_timeBLU, 33,22);
		ApplicationOLED_PrintTime(&ttime, 33,45);
		SH1106_UpdateScreen();
	}
	else{;}

	//HAL_Delay(500);
	//_PrintTeam(_timeRED, 1, 0, "RED ");
	//_PrintTeam(DateAndTime_GetTime(), 1, 22, "BLU ");
	//SH1106_UpdateScreen();
}

