//*****************************PEPTOOL Header Start******************************
//                                                                               
//                            Copyright © 2014 Eleon.                            
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL file version:106$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************


#include <Convert.h>

//#define CONVERT_DEBUG


// Convert numbers formatted as ASCII string to S32
// String length is specified by Length parameter; if Length == NULL(0), string length is detected automatically by looking \0 termination
// PARAMETERS:
//   String - ASCII number to convert
//   Value - pointer to the variable where the result will be stored
//   Length - Num of digits in ASCII string that form the value; if "Length" == NULL (or 0), string length is detected automatically by looking \0
// RETURN:
//    0 - success
//   -1 - invalid string length
//   -2 - value too big for S32
//   -3 - non numerical character detected
S32 Convert_StringToInt(char* String, S32* Value, U8 Length)
{
    U8 Len;
    S8 sign = 1;
    S32 value = 0;
    S32 multiplier = 1;

    
    if (Length == NULL || Length == 0) { Len = strlen(String); }
    else { Len = Length; }

    if (Len > 10 || Len < 1) { return -1; }       // invalid string length
    
#ifdef CONVERT_DEBUG
    OS_com_printf("\n%s(%d)\n", String, Len);
#endif

    int i = 0;
    // detect sign
    if (String[0] == '-') { sign = -1; i++; }
    else if (String[0] == '+') { sign = 1; i++; }

    // this part calculates multiplier for x10 calculations (c lib pow() would require double type)
    int k;
    for (k = Len - i - 1; k > 0; k--)
    {
        multiplier *= 10;
    }

    for (i; i < Len; i++)
    {
        if (String[i] < 0x30 || String[i] > 0x39) { return -3; }     // non numerical character detected

        value += (String[i] - 0x30) * multiplier;
        multiplier /= 10;

#ifdef CONVERT_DEBUG
        OS_com_printf("%d, %d, %d, %d\n", String[i], (String[i] - 0x30), value, i);
#endif
    }

    *Value = value * sign;
    
#ifdef CONVERT_DEBUG
	OS_com_printf("\nvalue: %d\n", *Value);
#endif

    return 0;
}


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
S32 Convert_StringToFloat(char* String, F32* Value, char DecimalSeparator, char EndCharacter, U8 Length)
{
    U8 Len;
    U8 fullNum[15];
    U8 fullNumCount = 0;
    U8 decimalNum[15];
    U8 decimalNumCount = 0;
    S8 sign = 1;
    F32 value = 0;
    S32 multiplier = 1;
    char endChar;

    if (EndCharacter == NULL) { endChar = '\0'; }
    else { endChar = EndCharacter; }

    if (Length == NULL || Length == 0)
    {
        Len = 20;
    }
    else if (Length > 20 || Length < 1)
    {
#ifdef CONVERT_DEBUG
        OS_com_printf("Debug-inv. string len: %d\n", Length);
#endif
        return -1;  // invalid string length
    }
    else { Len = Length; }

    if (DecimalSeparator == NULL)
    {
#ifdef CONVERT_DEBUG
        OS_com_printf("Debug-no decimal separator\n");
#endif
        return -4;  // no decimal separator character specified
    }

    int i = 0;
    // detect sign
    if (String[0] == '-') { sign = -1; i++; Len++; }
    else if (String[0] == '+') { sign = 1; i++; Len++; }

    // check if first number is available
    if (String[i] < 0x30 || String[i] > 0x39)
    {
#ifdef CONVERT_DEBUG
        OS_com_printf("Debug-%c\n", String[i]);
#endif
        return -3;  // non numerical character detected
    }
    fullNum[fullNumCount] = String[i] - 0x30;
    fullNumCount++;

    // find num of full digits in string
    while (true)
    {
        if (i >= Len) { goto CONVERT_calcvalue; }

        i++;
        if (String[i] == DecimalSeparator) { break; }
        else if (String[i] == endChar) { goto CONVERT_calcvalue; }
        if (String[i] < 0x30 || String[i] > 0x39)
        {
#ifdef CONVERT_DEBUG
            OS_com_printf("Debug-%c\n", String[i]);
#endif
            return -3;  // non numerical character detected
        }
        fullNum[fullNumCount] = String[i] - 0x30;
        fullNumCount++;
        multiplier *= 10;
        if (i > 20) { return -1; }      // invalid string length
    }

    // find num of digits in decimal part
    while (true)
    {
        i++;
        if (i >= Len) { goto CONVERT_calcvalue; }
        if (String[i] == endChar) { break; }
        else if (String[i] < 0x30 || String[i] > 0x39)
        {
#ifdef CONVERT_DEBUG
            OS_com_printf("Debug-%c\n", String[i]);
#endif
            return -3;  // non numerical character detected
        }
        decimalNum[decimalNumCount] = String[i] - 0x30;
        decimalNumCount++;
        if (i > 20) { return -1; }      // invalid string length
    }

CONVERT_calcvalue:

    // calculate full part
    for (i = 0; i < fullNumCount; i++)
    {
        value += (F32)fullNum[i] * multiplier;
        multiplier /= 10;
    }

    // calculate decimal part
    multiplier = 10;
    for (i = 0; i < decimalNumCount; i++)
    {
        value += (F32)decimalNum[i] / multiplier;
        multiplier *= 10;
    }

    *Value = value * sign;

    return 0;
}


S32 Convert_HexToUInt(char* String, U32* Value, U8 Length)
{
    U8 Len;
    S32 value = 0;
    S32 multiplier;

    if (Length == NULL || Length == 0) { Len = strlen(String); }
    else { Len = Length; }

    if (Len > 8 || Len < 1) { return -1; }       // invalid string length

    int j = Len - 1;     // j helps to calculate x16 multiplier value based on digit position
    int i;
    for (i = 0; i < Len; i++)
    {
        // because there is no "^" function in C, then this part makes x16 calculations
        multiplier = 1;
        int k;
        for (k = 0; k < j; k++)
        {
            multiplier *= 16;
        }

        if (String[i] > 0x2F && String[i] < 0x3A)
        {
            value += (String[i] - 0x30) * multiplier;
        }
        else if (String[i] > 0x40 && String[i] < 0x47)
        {
            value += (10 + String[i] - 0x41) * multiplier;
        }
        else { return -3; }     // non numerical character detected

        j--;

#ifdef CONVERT_DEBUG
        OS_com_printf("%d, %d, %d\n", String[i], value, j);
#endif
    }

    *Value = value;

    return 0;
}

/*
S32 Convert_UIntToHex(unsigned int UInt, char* Hex, U8 Length)
{
    U8 Len;
    char hex[8];
    S32 multiplier;

    if (Length == NULL || Length == 0) { Len = strlen(String); }
    else { Len = Length; }

    if (Len > 8 || Len < 1) { return -1; }       // invalid string length

    int j = Len - 1;     // j helps to calculate x16 multiplier value based on digit position
    int i;
    for (i = 0; i < Len; i++)
    {
        // because there is no "^" function in C, then this part makes x16 calculations
        multiplier = 1;
        int k;
        for (k = 0; k < j; k++)
        {
            multiplier *= 16;
        }

        if (String[i] > 0x2F && String[i] < 0x3A)
        {
            value += (String[i] - 0x30) * multiplier;
        }
        else if (String[i] > 0x40 && String[i] < 0x47)
        {
            value += (10 + String[i] - 0x41) * multiplier;
        }
        else { return -3; }     // non numerical character detected

        j--;

#ifdef CONVERT_DEBUG
        OS_com_printf("%d, %d, %d\n", String[i], value, j);
#endif
    }

    *Value = value;

    return 0;
}
*/
