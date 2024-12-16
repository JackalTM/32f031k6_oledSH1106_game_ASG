/*
 * dataconvert.c
 *
 *  Created on: 4 gru 2024
 *      Author: User
 */
#include "data_convert.h"

/*****************************************************************************************************
 * @name    CUST_CONV_uint_itoa
 * @brief   recursive function
 * @param   num Number to convert into string
 * @param   p_buffer Pointer to char buffer
 * @param   base Base of number format to convert into
 * @return  pointer to char this function is recursive
 */
char* CUST_CONV_uint_itoa(unsigned int num, char* p_buffer, unsigned int base)
{
  switch (base)
  {
  case 8:
    if(num >= 8)
    {   p_buffer = CUST_CONV_uint_itoa( num/8, p_buffer, 8);
    }else{;}

    *p_buffer++ = '0' + (num % 8);

    return p_buffer;
    break;

  case 10:
    if(num >= 10)
    {   p_buffer = CUST_CONV_uint_itoa( num/10, p_buffer, 10);
    }else{;}

    *p_buffer++ = '0' + (num % 10);

    return p_buffer;
    break;

  case 16:
    if(num >= 16)
    {   p_buffer = CUST_CONV_uint_itoa( num/16, p_buffer, 16);
    }else{;}

    num = (num % 16);
    if(num > 9)  { num = ('7' + num);} // '7' + 10 = 'A'
    else          { num = ('0' + num);}
    *p_buffer++ = num;

    return p_buffer;
    break;

  default:
    break;
  }

  return p_buffer;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		NumToString
 * @brief		This method convert number to string in format decimal
 *
 * @param[in] 	number Number that will be converted to string
 * @param[in]	  arrChar[] Pointer to array of chars
 * @param[in] 	DecimalNumberStringSize destination string size
 *
 * @note		  void
 * @return		strlen(arrChar)
 */
unsigned int CUST_CONV_NumToString_oct(uint8_t number, char arrChar[], enum OctalNumberStringSize lenght)
{
  *(CUST_CONV_uint_itoa(number, arrChar, 8)) = '\0';
  return strlen(arrChar);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		NumToString
 * @brief		This method convert number to string in format decimal
 *
 * @param[in] 	number Number that will be converted to string
 * @param[in]	  arrChar[] Pointer to array of chars
 * @param[in] 	DecimalNumberStringSize destination string size
 *
 * @note		  void
 * @return		strlen(arrChar)
 */
unsigned int CUST_CONV_NumToString_dec(uint8_t number, char arrChar[], enum DecimalNumberStringSize lenght)
{
  *(CUST_CONV_uint_itoa(number, arrChar, 10)) = '\0';
  return strlen(arrChar);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		NumToString
 * @brief		This method convert number to string in format hexadecimal
 *
 * @param[in] 	number Number that will be converted to string
 * @param[in]	  arrChar[] Pointer to array of chars
 * @param[in] 	HexadeciNumberStringSize destination string size
 *
 * @note		  void
 * @return		strlen(arrChar)
 */
unsigned int CUST_CONV_NumToString_hex(uint8_t number, char arrChar[], enum HexadeciNumberStringSize lenght)
{
  *(CUST_CONV_uint_itoa(number, arrChar, 0x10)) = '\0';
  return strlen(arrChar);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		CUST_CONV_StrFormatToRight
 * @brief		Convert string from front to end of a string array
 *
 * @param[in]	arrSRC[] Pointer to source array
 * @param[in]	lenSRC strlen(arrChar)
 * @param[in]	arrDST[] Pointer to destination array
 * @param[in]	lenDST strlen(arrChar)
 * @param[in] c char to fil empty spaces
 *
 * @note		  Input lenght need to be strlen(arrChar)
 *            This string is formating specyfic
 * @return		void
 */
void CUST_CONV_StrFormatToRight(char arrSRC[], uint8_t lenSRC, char arrDST[], uint8_t lenDST, char c)
{
  unsigned int i,j;
  for(i=0; i<lenDST; i++)
  { arrDST[i] = c; }

  arrDST[lenDST] = '\0';

  j = lenDST - 1;
  i = lenSRC - 1;
  while((j < 0x7F) && (i < 0x7F))
  {
    arrDST[j--] = arrSRC[i--];
  }
}
//====================================================================================================

/*****************************************************************************************************
 * @name        CUST_CONV_TimeToStr_struct
 * @brief       Time structure format to string
 * @param[ptr]  pTime Pointer to struct timeformat_t
 * @param[ptr]  arrChar Pointer to array buffer
 */
void CUST_CONV_TimeToStr_hh_mm_ss_struct(struct timeformat_t *pTime, char pBuffer[])
{
  char tBuffer[3];
  unsigned int lenght;

  lenght = CUST_CONV_NumToString_dec(pTime->hour, (char*)tBuffer, 2);
  CUST_CONV_StrFormatToRight(tBuffer, lenght, (char*)(pBuffer + 0), 2, '0');
  //printf(">> hour= %d | h= %s | hh= %s \n", hour, tBuffer, (char*)(pBuffer + 0));

  lenght = CUST_CONV_NumToString_dec(pTime->minute, tBuffer, 2);
  CUST_CONV_StrFormatToRight(tBuffer, lenght, (char*)(pBuffer + 3), 2, '0');
  //printf(">> minute= %d | m= %s | mm= %s \n", minute, tBuffer, (char*)(pBuffer + 3));

  lenght = CUST_CONV_NumToString_dec(pTime->second, (char*)tBuffer, 2);
  CUST_CONV_StrFormatToRight(tBuffer, lenght, (char*)(pBuffer + 6), 2, '0');
  //printf(">> second= %d | s= %s | ss= %s \n", second, tBuffer, (char*)(pBuffer + 6));

  *((char*)(pBuffer + 2)) = ':';
  *((char*)(pBuffer + 5)) = ':';

  //printf(">> time= %s \n", pBuffer);
  //printf("===\n");
}
//====================================================================================================

/*****************************************************************************************************
 * @name        CUST_CONV_TimeToStr_args
 * @brief       Time structure format to string
 * @param[in]   hour
 * @param[in]   minute
 * @param[in]   minute
 * @param[ptr]  pBuffer Pointer to array buffer
 */
void CUST_CONV_TimeToStr_hh_mm_ss_args(uint8_t hour, uint8_t minute, uint8_t second, char pBuffer[])
{
  char tBuffer[3];
  unsigned int lenght;

  lenght = CUST_CONV_NumToString_dec(hour, (char*)tBuffer, 2);
  CUST_CONV_StrFormatToRight(tBuffer, lenght, (char*)(pBuffer + 0), 2, '0');
  //printf(">> hour= %d | h= %s | hh= %s \n", hour, tBuffer, (char*)(pBuffer + 0));

  lenght = CUST_CONV_NumToString_dec(minute, tBuffer, 2);
  CUST_CONV_StrFormatToRight(tBuffer, lenght, (char*)(pBuffer + 3), 2, '0');
  //printf(">> minute= %d | m= %s | mm= %s \n", minute, tBuffer, (char*)(pBuffer + 3));

  lenght = CUST_CONV_NumToString_dec(second, (char*)tBuffer, 2);
  CUST_CONV_StrFormatToRight(tBuffer, lenght, (char*)(pBuffer + 6), 2, '0');
  //printf(">> second= %d | s= %s | ss= %s \n", second, tBuffer, (char*)(pBuffer + 6));

  *((char*)(pBuffer + 2)) = ':';
  *((char*)(pBuffer + 5)) = ':';

  //printf(">> time= %s \n", pBuffer);
  //printf("===\n");
}
//====================================================================================================
