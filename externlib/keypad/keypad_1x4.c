/*
 * keypad_1x4.c
 *
 *  Created on: 8 gru 2024
 *      Author: User
 */
#include "keypad_1x4.h"

/***********************************************************************************************
 * Definitions for private class varibales
*/
static uint8_t irq_n, _colnum, _PINx;
static uint8_t _keydecoded, _keystate;
static uint8_t arrDebounce[KEYPAD1x4_ARRAY_AMOUNT_ROW];
static uint8_t arrCounter[KEYPAD1x4_ARRAY_AMOUNT_ROW];

static const uint8_t arrayPortOutNegative[KEYPAD1x4_ARRAY_AMOUNT_MAX_N] =
{   KEYPAD_CODE_PORTx_01_N, KEYPAD_CODE_PORTx_02_N,
    KEYPAD_CODE_PORTx_03_N, KEYPAD_CODE_PORTx_04_N};

static const uint8_t arrKeys2D[KEYPAD1x4_ARRAY_AMOUNT_ROW][KEYPAD1x4_ARRAY_AMOUNT_COL] =
{   {KEYCODE_01, KEYCODE_02, KEYCODE_03, KEYCODE_04}};

/***********************************************************************************************
 * Definitions for debounce state on keypad
*/
static uint8_t _DEBOUNCE_AMOUNT;
static volatile uint8_t keyCode;
static volatile uint8_t keyState;
//==============================================================================================


/*****************************************************************************************************
 * @name		void
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		void
 */
//====================================================================================================

/*****************************************************************************************************
 * @name		Constructor for Keypad1x4 class
 * @brief		void
 * @param[in]	dbAmount Debonce amount
 * @note		void
 */
void Keypad_SetDebounceAmount(uint8_t dbAmount)
{ 	_DEBOUNCE_AMOUNT = dbAmount;
	irq_n = 0x00;
	_colnum = 0xFF;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		DecodeKeyCode
 * @brief		All buttons are connected to 5V
 * 				When press input port signal 0V
 *
 * @param[in]	inPIN Input pin value
 *
 * @note		Simple input 4 buttons
 * @return		void
 */
uint8_t Keypad_DecodeKeyCode(uint8_t inPIN)
{
	uint8_t tCOL;

	inPIN = KEYPAD_CODE_PINx_MASK_F(inPIN);
	switch (inPIN)
	{
	case KEYPAD_CODE_PINx_02_N:	tCOL = 0; break;
	case KEYPAD_CODE_PINx_03_N: tCOL = 1; break;
	case KEYPAD_CODE_PINx_04_N: tCOL = 2; break;
	case KEYPAD_CODE_PINx_05_N: tCOL = 3; break;
	default: return KEYCODE_NOPRESS;
	}

	return arrKeys2D[0][tCOL];
}

/*****************************************************************************************************
 * @name		PadDebounce
 * @brief		Debounce for keypad
 * @param[in]	pDebounce Pointer to debounce state machine
 * @param[in]	pCounter Pointer to counter for amount of debounce
 * @param[in]	inState Certain input value of decoded column
 * @note		void
 * @return		Current debounce state
 */
uint8_t Keypad_PadDebounce(uint8_t* pDebounce, uint8_t* pCounter, uint8_t inState)
{
	switch(*pDebounce)
	{
		// Initialization of button debounce state machine
		case KEYPAD_DEBOUNCE_x00_INIT:
			*pDebounce = KEYPAD_DEBOUNCE_x11_STABLE_OFF;
			*pCounter = 0x00;
			break;

		// Stan stabilny zero czekanie na stan wysoki
		case KEYPAD_DEBOUNCE_x11_STABLE_OFF:
			if(inState != KEYPAD_DEBOUNCE_STATE_NOPRESS)
			{	*pDebounce = KEYPAD_DEBOUNCE_x33_DB_OFFON;
				return KEYPAD_DEBOUNCE_x22_RISING_EDGE;}
			else{;}
			break;

		// Czekanie na ustabilizowanie sie stanu
		case KEYPAD_DEBOUNCE_x33_DB_OFFON:
			if(*pCounter < _DEBOUNCE_AMOUNT)
			{	*pCounter = *pCounter + 0x01;}
			else
			{	*pDebounce = KEYPAD_DEBOUNCE_x44_STABLE_ON;
				*pCounter = 0x00;}
			break;

		// Czekanie na zwolnienie klawicza stan stabilny
		case KEYPAD_DEBOUNCE_x44_STABLE_ON:
			if(inState == KEYPAD_DEBOUNCE_STATE_NOPRESS)
			{	*pDebounce = KEYPAD_DEBOUNCE_x55_FALLING_EDGE;
				return KEYPAD_DEBOUNCE_x55_FALLING_EDGE;}
			else{;}
			break;

		// Czekanie na ustabilizowanie sie stanu niskiego
		case KEYPAD_DEBOUNCE_x66_DB_ONOFF:
			if(*pCounter < _DEBOUNCE_AMOUNT)
			{	*pCounter = *pCounter + 0x01;}
			else
			{	*pDebounce = KEYPAD_DEBOUNCE_x11_STABLE_OFF;
				*pCounter  = 0x00;}
			break;

		default:
			*pDebounce = KEYPAD_DEBOUNCE_x00_INIT;
	}

	return *pDebounce;
}

/*****************************************************************************************************
 * @name		KeypadStateEvaluation
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		state of a pressed button
 */
uint8_t Keypad_KeypadStateEvaluation(void)
{
	static uint8_t sButtonState;

	switch (irq_n)
	{
	case KEYPAD_IRQ_OPERATION_x11_INPUT_DEBOUNCE:
		irq_n = KEYPAD_IRQ_OPERATION_x22_DECODE_BUTTON;

		_PINx = KEYPAD_CODE_PINx_MASK_F(PINB);
		sButtonState = PadDebounce((uint8_t*)&(arrDebounce[0]), (uint8_t*)&(arrCounter[0]), _PINx);
		break;

	case KEYPAD_IRQ_OPERATION_x22_DECODE_BUTTON:
		irq_n = KEYPAD_IRQ_OPERATION_x00_SET_OUTPUT;

		if(sButtonState == KEYPAD_DEBOUNCE_x22_RISING_EDGE)
		{
			keyCode = DecodeKeyCode(_PINx);
			keyState = KEYPAD_DEBOUNCE_x22_RISING_EDGE;
			return KEYPAD_KEYPAD_STATE_PULS;
		}
		else{;}
		break;

	default:
		irq_n = KEYPAD_IRQ_OPERATION_x11_INPUT_DEBOUNCE;
		break;
	}

	return KEYCODE_NOPRESS;
}
uint8_t Keypad_GetKeyCode(void)
{
	return keyCode;
}
