/*
 * keypad_1x4.h
 *
 *  Created on: 8 gru 2024
 *      Author: User
 */

#ifndef KEYPAD_KEYPAD_1X4_H_
#define KEYPAD_KEYPAD_1X4_H_

#include "stdint.h"
#include "stdio.h"
#include "bit_mask_macros.h"

//#define KEYPAD_KEYDEF_AMOUNT
#define KEYPAD_KEYDEF_ASCI
#define KEYPAD_ACTIVE_STATE_LOW
//#define KEYPAD_ACTIVE_STATE_HIGH

typedef struct
{
    uint8_t keyState;
    uint8_t keyCode;
}keypadState_t;

/*******************************************************************************************************************
 * Definitions of a key code value.
 * Depend on demanding values
*/
// KEYPAD_KEYDEF_ASCI
#ifdef KEYPAD_KEYDEF_ASCI
#define KEYCODE_NOPRESS 0xFF
#define KEYCODE_00 (char)'0'
#define KEYCODE_01 (char)'1'
#define KEYCODE_02 (char)'2'
#define KEYCODE_03 (char)'3'
#define KEYCODE_04 (char)'4'
#define KEYCODE_05 (char)'5'
#define KEYCODE_06 (char)'6'
#define KEYCODE_07 (char)'7'
#define KEYCODE_08 (char)'8'
#define KEYCODE_09 (char)'9'
#define KEYCODE_10 (char)'A'
#define KEYCODE_11 (char)'B'
#define KEYCODE_12 (char)'C'
#define KEYCODE_13 (char)'D'
#define KEYCODE_14 (char)'E'
#define KEYCODE_15 (char)'F'
#endif // KEYPAD_KEYDEF_ASCI
//==================================================================================================================

/*******************************************************************************************************************
 * Definitions for certain  PORT output data
 * Need to be modified depend on connection
*/
#define KEYPAD4x4_ARRAY_AMOUNT_MAX_N   (uint8_t)0x04 // Maximum elements amont
#define KEYPAD4x4_ARRAY_AMOUNT_ROW     (uint8_t)0x04 // Maximum elements in row array
#define KEYPAD4x4_ARRAY_AMOUNT_COL     (uint8_t)0x04 // Maximum elements in col array

#define KEYPAD1x4_ARRAY_AMOUNT_MAX_N   (uint8_t)0x04 // Maximum elements amont
#define KEYPAD1x4_ARRAY_AMOUNT_ROW     (uint8_t)0x01 // Maximum elements in row array
#define KEYPAD1x4_ARRAY_AMOUNT_COL     (uint8_t)0x04 // Maximum elements in col array
//-----------------------------------------------------------------------------------


// MAcros for PORT and PIB states
#ifdef KEYPAD_ACTIVE_STATE_LOW

    #define KEYPAD_CODE_PORTx_01_N  (uint8_t)0x07 // 0b 0000 0111
    #define KEYPAD_CODE_PORTx_02_N  (uint8_t)0x0B // 0b 0000 1011
    #define KEYPAD_CODE_PORTx_03_N  (uint8_t)0x0D // 0b 0000 1101
    #define KEYPAD_CODE_PORTx_04_N  (uint8_t)0x0E // 0b 0000 1110
    #define KEYPAD_CODE_PORTx_NOPR  (uint8_t)0x0F // 0b 0000 1111

    #define KEYPAD_CODE_PINx_02_N   (uint8_t)0x38 // 0b 0011 1000
    #define KEYPAD_CODE_PINx_03_N   (uint8_t)0x34 // 0b 0011 0100
    #define KEYPAD_CODE_PINx_04_N   (uint8_t)0x2C // 0b 0010 1100
    #define KEYPAD_CODE_PINx_05_N   (uint8_t)0x1C // 0b 0001 1100
    #define KEYPAD_CODE_PINx_NOPR   (uint8_t)0x3C // 0b 0011 1100

#endif // KEYPAD_ACTIVE_STATE_LOW
//-----------------------------------------------------------------------------------

// Port mask macro
#define KEYPAD_CODE_PORTx_MASK      (uint8_t)0x0F // Mask for output port valid data
#define KEYPAD_CODE_PORTx_MASK_F(x) (KEYPAD_CODE_PORTx_MASK & x) // 0b 0000 1111 & x
// Pin mask macro
#define KEYPAD_CODE_PINx_MASK       (uint8_t)0x3C // Mask for input PIN valid data
#define KEYPAD_CODE_PINx_MASK_F(x)  (KEYPAD_CODE_PINx_MASK & x)  // 0b 0011 1100 & x
//==============================================================================================

enum outputColumn_enum {COLUMN_1 = 0, COLUMN_2 = 1, COLUMN_3 = 2, COLUMN_4 = 3};

/*******************************************************************************************************************
 * Debounce state machine value definitions
*/
#define KEYPAD_DEBOUNCE_x00_INIT        (uint8_t)0x00 // State initialization
#define KEYPAD_DEBOUNCE_x11_STABLE_OFF  (uint8_t)0x11 // Stable low state
#define KEYPAD_DEBOUNCE_x22_RISING_EDGE (uint8_t)0x22 // Rising edge om state
#define KEYPAD_DEBOUNCE_x33_DB_OFFON    (uint8_t)0x33 // Debounce from low to high
#define KEYPAD_DEBOUNCE_x44_STABLE_ON   (uint8_t)0x44 // Stable high state
#define KEYPAD_DEBOUNCE_x55_FALLING_EDGE (uint8_t)0x55 // Falling edge on state
#define KEYPAD_DEBOUNCE_x66_DB_ONOFF    (uint8_t)0x66 // Debounce from high to low
#define KEYPAD_DEBOUNCE_STATE_NOPRESS   KEYPAD_CODE_PINx_NOPR
//-----------------------------------------------------------------------------------

#define KEYPAD_KEYPAD_STATE_PULS        KEYPAD_DEBOUNCE_x22_RISING_EDGE

enum enum_KEYPAD_DB_STATE_t
{
    KEY_STATE_Ini = KEYPAD_DEBOUNCE_x00_INIT,
    KEY_STATE_Relised = KEYPAD_DEBOUNCE_x11_STABLE_OFF,
    KEY_STATE_RisingEdge = KEYPAD_DEBOUNCE_x22_RISING_EDGE,
    KEY_STATE_DebounceOn = KEYPAD_DEBOUNCE_x33_DB_OFFON,
    KEY_STATE_Presed = KEYPAD_DEBOUNCE_x44_STABLE_ON,
    KEY_STATE_FallingEdge = KEYPAD_DEBOUNCE_x55_FALLING_EDGE,
    KEY_STATE_DebounceOff = KEYPAD_DEBOUNCE_x66_DB_ONOFF
};
//==============================================================================================

/*******************************************************************************************************************
 *
*/
#define KEYPAD_IRQ_OPERATION_x00_SET_OUTPUT (uint8_t)0x00 // Set output port for every column
#define KEYPAD_IRQ_OPERATION_x11_INPUT_DEBOUNCE (uint8_t)0x11 // Read buton and debounce
#define KEYPAD_IRQ_OPERATION_x22_DECODE_BUTTON (uint8_t)0x22 // Decode debounced button
//==============================================================================================


void Keypad_SetDebounceAmount(uint8_t dbAmount);
uint8_t Keypad_DecodeKeyCode(uint8_t inPIN);
uint8_t Keypad_PadDebounce(uint8_t* pDebounce, uint8_t* pCounter, uint8_t inState);

uint8_t Keypad_KeypadStateEvaluation(void);
uint8_t Keypad_GetKeyCode(void);


#endif /* KEYPAD_KEYPAD_1X4_H_ */
