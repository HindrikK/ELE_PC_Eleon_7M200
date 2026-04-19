//*****************************PEPTOOL Header Start******************************
//                                                                               
//                            Copyright © 2014 Eleon.                            
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL file version:103$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#ifndef FILE_CONVERT_H
#define FILE_CONVERT_H

#include <lib_main.h>


// Convert numbers formatted as ASCII string to S32
// String length is specified by Length parameter; if Length == NULL or 0, string length is detected automatically by looking \0 termination
// PARAMETERS:
//   String - ASCII number to convert
//   Value - pointer to the variable where the result will be stored
//   Length - Num of digits in ASCII string that form the value
// RETURN:
//    0 - success
//   -1 - invalid string length
//   -2 - value too big for S32
//   -3 - non numerical character detected
S32 Convert_StringToInt(char* /*String*/, S32* /*pointer to value*/, U8 /*Length*/);


// Convert numbers formatted as ASCII string, including decimal point, to F32
// If both, "Length" and "EndCharacter" are NULL, then '\0' is used as string end character
// If both, "Length" and "EndCharacter" are given, then conversion will stop at which comes first. (Basically "Length" acts as a maxLen in that case)
// PARAMETERS:
//   String - ASCII number to convert
//   Value - pointer to the variable where the result will be stored
//   DecimalSeparator - specifies character that represents decimal point
//   EndCharacter - specifies character that will define end of string; if NULL(0), "Length" must be set
//   Length - Num of digits in ASCII string that form the value(excluding sign); if "Length" == NULL(0), string length is detected automatically by looking "EndCharacter"
// RETURN:
//    0 - success
//   -1 - invalid string length
//   -2 - value too big for S32
//   -3 - non numerical character detected
//   -4 - no decimal separator character specified
S32 Convert_StringToFloat(char* /*String*/, F32* /*Value*/, char /*DecimalSeparator*/, char /*EndCharacter*/, U8 /*Length*/);


// Convert numbers formatted as ASCII HEX string to S32
// String length is specified by Length parameter; if Length == NULL or 0, string length is detected automatically by looking \0 termination
// PARAMETERS:
//   String - ASCII HEX number to convert
//   Value - pointer to the variable where the result will be stored
//   Length - Num of digits in ASCII string that form the value
// RETURN:
//    0 - success
//   -1 - invalid string length
//   -2 - value too big for U32
//   -3 - non numerical character detected
S32 Convert_HexToUInt(char* /*String*/, U32* /*pointer to value*/, U8 /*Length*/);

#endif
