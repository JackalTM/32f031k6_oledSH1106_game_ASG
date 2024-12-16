/*
 * events_types.c
 *
 *  Created on: 5 gru 2024
 *      Author: User
 */
#include "events_types.h"

static struct EventsTypes_t _pf_events = {NULL, NULL, NULL};
static uint8_t _TIM14_div;

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
 * @name		ProgramEvents_set_event_1ms
 * @brief		Set function pointer to 1ms event
 * @param[in]	pFunction Function type void (*pFunction) (void)
 * @note
 * @return
 */
void ProgramEvents_set_event_1ms(void (*pFunction) (void))
{
	_pf_events.pf_EventTime_1ms = pFunction;
}
//==========================================================================

/***************************************************************************
 * @name		ProgramEvents_set_event_1sec
 * @brief		Set function pointer to 1ms event
 * @param[in]	pFunction Function type void (*pFunction) (void)
 * @note
 * @return
 */
void ProgramEvents_set_event_1sec(void (*pFunction) (void))
{
	_pf_events.pf_EventTime_1sec = pFunction;
}
//=========================================================================

/***************************************************************************
 * @name		ProgramEvents_set_current_screen
 * @brief		Set function pointer to 1ms event
 * @param[in]	pFunction Function type void (*pFunction) (void)
 * @note
 * @return
 */
void ProgramEvents_set_current_screen(void (*pFunction) (void))
{
	_pf_events.pf_ScrrenCurrent = pFunction;
}
//==========================================================================

/***************************************************************************
 * @name		ProgramEvents_reset_event_1ms
 * @brief		Reset function pointer
 * @note
 * @return
 */
void ProgramEvents_reset_event_1ms(void)
{
	_pf_events.pf_EventTime_1ms = NULL;
}
//==========================================================================

/***************************************************************************
 * @name		ProgramEvents_reset_event_1sec
 * @brief		Reset function pointer
 * @note
 * @return
 */
void ProgramEvents_reset_event_1sec(void)
{
	_pf_events.pf_EventTime_1sec = NULL;
}
//==========================================================================

/***************************************************************************
 * @name		ProgramEvents_reset_current_screen
 * @brief		Reset function pointer
 * @note
 * @return
 */
void ProgramEvents_reset_current_screen(void)
{
	_pf_events.pf_ScrrenCurrent = NULL;
}
//=========================================================================

/***************************************************************************
 * @name		ProgramEvents_call_event_1ms
 * @brief
 * @note
 * @return
 */
void ProgramEvents_call_event_1ms(void)
{
	if(_pf_events.pf_EventTime_1ms == NULL)
		return;
	else
		(*_pf_events.pf_EventTime_1ms)();
}
//==========================================================================

/***************************************************************************
 * @name		ProgramEvents_call_event_1sec
 * @brief
 * @note
 * @return
 */
void ProgramEvents_call_event_1sec(void)
{
	if(++_TIM14_div < 16) return;
	else{;}
	_TIM14_div = 0;

	if(_pf_events.pf_EventTime_1sec == NULL)
		return;
	else
		(*_pf_events.pf_EventTime_1sec)();
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
void ProgramEvents_call_current_screen(void)
{
	if(_pf_events.pf_ScrrenCurrent == NULL)
		return;
	else
		(*_pf_events.pf_ScrrenCurrent)();
}
//===========================================================================
