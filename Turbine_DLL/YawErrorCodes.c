//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2015 Mita-Teknik.                         
//This software may only be used with WP4x00 Controllers delivered by Mita-Teknik
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:8.0$                                                         
// $PEPTOOL file version:101$                                                    
//                                                                               
//*******************************************************************************
//                                                                               
// $Date: XXXX/XX/XX XX:XX:XX $                                                  
// $Author: XXXX\XXX $                                                           
// $RCSfile: YawErrorCodes.c,v $                                                 
// $Revision: X.X $                                                              
//                                                                               
//******************************PEPTOOL Header End*******************************
#include <os_lib.h>
static char *ERROR_CODES_GetDescription(S16 *code)
{
	switch (*code)
	{
		case 0:
		{
			return "No Error\0";
		}
		case 1:
		{
			return "Overcurrent\0";
		}
		case 2:
		{
			return "Overvoltage\0";
		}
		case 3:
		{
			return "Earth fault\0";
		}
		case 5:
		{
			return "Charging switch\0";
		}
		case 6:
		{
			return "Emergency stop\0";
		}
		case 7:
		{
			return "Saturation trip\0";
		}
		case 8:
		{
			return "Syatem fault\0";
		}
		case 9:
		{
			return "Undervoltage\0";
		}
		case 10:
		{
			return "Input line supervision\0";
		}
		case 11:
		{
			return "Output phase supervision\0";
		}
		case 12:
		{
			return "Brake chopper supervision\0";
		}
		case 13:
		{
			return "Drive under-temperature\0";
		}
		case 14:
		{
			return "Drive over-temperature\0";
		}
		case 15:
		{
			return "Motor stalled\0";
		}
		case 16:
		{
			return "Motor over-temperature\0";
		}
		case 17:
		{
			return "Motor underload\0";
		}
		case 18:
		{
			return "Unbalance\0";
		}
		case 22:
		{
			return "EEPROM checksum fault\0";
		}
		case 24:
		{
			return "Counter fault\0";
		}
		case 25:
		{
			return "Microprocessor watchdog fault\0";
		}
		case 26:
		{
			return "Start-up prevented\0";
		}
		case 29:
		{
			return "Thermistor fault\0";
		}
		case 30:
		{
			return "Safe disable\0";
		}
		case 31:
		{
			return "IGBT temperature(hardware)\0";
		}
		case 32:
		{
			return "Fan cooling\0";
		}
		case 34:
		{
			return "CAN bus communication\0";
		}
		case 35:
		{
			return "Application\0";
		}
		case 36:
		{
			return "Control unit\0";
		}
		case 37:
		{
			return "Device changed\0";
		}

		case 38:
		{
			return "Device added\0";
		}
		case 39:
		{
			return "Device removed\0";
		}
		case 40:
		{
			return "Device unknown\0";
		}
		case 41:
		{
			return "IGBT temperature\0";
		}
		case 42:
		{
			return "Brake resistor\0";
		}

		case 43:
		{
			return "Encoder fault\0";
		}
		case 44:
		{
			return "Device changed\0";
		}
		case 45:
		{
			return "Device added\0";
		}
		case 49:
		{
			return "Division by zero in application\0";
		}
		case 50:
		{
			return "Analog input range\0";
		}
		case 51:
		{
			return "External fault\0";
		}
		case 52:
		{
			return "Keypad communication fault\0";
		}
		case 53:
		{
			return "Fieldbus fault\0";
		}
		case 54:
		{
			return "Slot fault\0";
		}

		case 56:
		{
			return "PT100 board temp fault\0";
		}
		case 57:
		{
			return "Identification\0";
		}
		case 58:
		{
			return "Brake\0";
		}
		case 59:
		{
			return "Follower communication\0";
		}
		case 60:
		{
			return "Cooling\0";
		}
		case 61:
		{
			return "Speed error\0";
		}
		case 62:
		{
			return "Run disable\0";
		}
		case 63:
		{
			return "Emergency stop\0";
		}
		case 64:
		{
			return "Input switch open\0";
		}
		case 65:
		{
			return "PT100 board 2 temp fault\0";
		}
		case 74:
		{
			return "Follower fault\0";
		}

		default:
		{
			return "No description\0";
		}
	}
}
