/*
 * event_types.h
 *
 *  Created on: 5 gru 2024
 *      Author: User
 */

#ifndef EVENTS_MENAGMENT_EVENTS_TYPES_H_
#define EVENTS_MENAGMENT_EVENTS_TYPES_H_

#include <stdio.h>
#include <stdint.h>

struct EventsTypes_t
{
	void (*pf_EventTime_1ms) (void);
	void (*pf_EventTime_1sec) (void);
	void (*pf_ScrrenCurrent) (void);
};

struct ScreenPointers_t
{
	unsigned int current_screen;
	unsigned int max_screen;
	void (*pf_Screens_ptr[16]) (void);
};

void ProgramEvents_set_event_1ms(void (*pFunction) (void));
void ProgramEvents_set_event_1sec(void (*pFunction) (void));
void ProgramEvents_set_current_screen(void (*pFunction) (void));

void ProgramEvents_reset_event_1ms(void);
void ProgramEvents_reset_event_1sec(void);
void ProgramEvents_reset_current_screen(void);

void ProgramEvents_call_event_1ms(void);
void ProgramEvents_call_event_1sec(void);
void ProgramEvents_call_current_screen(void);

#endif /* EVENTS_MENAGMENT_EVENTS_TYPES_H_ */
