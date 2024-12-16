/*
 * application_flow.c
 *
 *  Created on: 11 gru 2024
 *      Author: User
 */
#include "application_flow.h"

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
 * @name		ApplicationFlow_Initialization
 * @brief		OLED initialization
 * @note
 */
void ApplicationFlow_Initialization(void)
{
	ApplicationOLED_Init();


	DateAndTime_TIME_RESET;
}
//==========================================================================


/***************************************************************************
 * @name		ApplicationFlow_mainscreen
 * @brief
 * @param[in]
 * @param[in]
 * @param[in]
 * @note
 * @return
 */
static uint8_t n=0;
void ApplicationFlow_mainscreen(void)
{
	//ApplicationOLED_screen_twoteams(DateAndTime_GetTime(), DateAndTime_GetTime(), "Czerwoni");

	ApplicationOLED_screen_teamtaking("Czerwoni", n, 8);
	n++;
	if(n>8) n=0;
}
//==========================================================================


