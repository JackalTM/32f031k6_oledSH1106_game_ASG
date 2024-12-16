/*
 * bit_mask_macros.h
 *
 *  Created on: 14 gru 2024
 *      Author: User
 */

#ifndef KEYPAD_BIT_MASK_MACROS_H_
#define KEYPAD_BIT_MASK_MACROS_H_

/************************************************
 * Set bit definitions
*/
#define BITMASK_NULL 0x00U //  0b 0000 0000
#define BITMASK_Tx0 0x01U //  0b 0000 0001
#define BITMASK_Tx1 0x02U //  0b 0000 0010
#define BITMASK_Tx2 0x04U //  0b 0000 0100
#define BITMASK_Tx3 0x08U //  0b 0000 1000

#define BITMASK_Tx4 0x10U //  0b 0001 0000
#define BITMASK_Tx5 0x20U //  0b 0010 0000
#define BITMASK_Tx6 0x40U //  0b 0100 0000
#define BITMASK_Tx7 0x80U //  0b 1000 0000

#define BITMACRO_SET_nBit(x,y) (x | y)
//===============================================

/************************************************
 * Reset bit definitions
*/
#define BITMASK_FULL 0xFFU //  0b 1111 1111
#define BITMASK_Fx0 0xFEU //  0b 1111 1110
#define BITMASK_Fx1 0xFDU //  0b 1111 1101
#define BITMASK_Fx2 0xFBU //  0b 1111 1011
#define BITMASK_Fx3 0xF7U //  0b 1111 0111

#define BITMASK_Fx4 0xEFU //  0b 1110 1111
#define BITMASK_Fx5 0xDFU //  0b 1101 1111
#define BITMASK_Fx6 0xBFU //  0b 1011 1111
#define BITMASK_Fx7 0x7FU //  0b 0111 1111

#define BITMACRO_RESET_nBit(x,y) (x & y)
//===============================================

/************************************************
 * Varibale size definitions
*/
#define BYTE_SIZE_OF_uint8_t    1U
#define BYTE_SIZE_OF_uint16_t   2U
#define BYTE_SIZE_OF_uint32_t   4U
#define BYTE_SIZE_OF_uint64_t   8U

#define BYTE_MASK_PART_LOW      0x0F
#define BYTE_MASK_PART_HIH      0xF0
//===============================================

#endif /* KEYPAD_BIT_MASK_MACROS_H_ */
