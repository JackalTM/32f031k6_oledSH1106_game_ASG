/*
 * x_call_test.h
 *
 *  Created on: Nov 28, 2024
 *      Author: User
 */

#ifndef OLED_SH1106_APPLICATION_OLED_H_
#define OLED_SH1106_APPLICATION_OLED_H_

#include "data_convert.h"
#include "data_types.h"
#include "date_and_time.h"

void ApplicationOLED_Init(void);

void ApplicationOLED_PrintTime(struct timeformat_t* pTime, uint8_t x, uint8_t y);


void ApplicationOLED_screen_twoteams(struct timeformat_t teamActive, struct timeformat_t teamPasive, char* pteamLeding);
void ApplicationOLED_screen_teamtaking(char* pteamLeding, uint8_t n, uint8_t max_n);

void ApplicationOLED_screen_winner_init(void);
void ApplicationOLED_screen_startup(void);
void ApplicationOLED_screen_noevents(void);
void ApplicationOLED_screen_winner(void);

void ApplicationOLED_TwoTeams(void);

#endif /* OLED_SH1106_APPLICATION_OLED_H_ */
