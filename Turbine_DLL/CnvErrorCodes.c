//********************************************************************
//
//            Copyright (c) 2014 Eleon AS
//
//*******************************************************************
//
// $Date: 2014/08/24 16:54:00 $
// $Author: HK $
// $RCSfile: CnvErrorCodes.c,v $
// $Revision: 1.0 $
//
//*******************************************************************





char *ERROR_CODES_GetDescription(U8 *code)
{
	switch (*code)
	{
		case 0:
		{
			return "No Error\0";
		}
		case 3:
		{
			return "High temperature, booster\0";
		}
		case 7:
		{
			return "Low temperature, booster\0";
		}
		case 11:
		{
			return "High temperature, IGBT U, HW-driver\0";
		}
		case 12:
		{
			return "High temperature, IGBT U, software\0";
		}
		case 13:
		{
			return "High temperature, IGBT V, HW-driver\0";
		}
		case 14:
		{
			return "High temperature, IGBT V, software\0";
		}
		case 15:
		{
			return "High temperature, IGBT W, HW-driver\0";
		}
		case 16:
		{
			return "High temperature, IGBT W, software\0";
		}
		case 17:
		{
			return "High temperature, cabinet\0";
		}
		case 18:
		{
			return "High temperature, ambient\0";
		}
		case 19:
		{
			return "High temperature, inductor\0";
		}
		case 20:
		{
			return "High temperature, brake chopper\0";
		}
		case 21:
		{
			return "High temperature, control card\0";
		}
		case 22:
		{
			return "Low temperature, IGBT L1\0";
		}
		case 23:
		{
			return "Low temperature, IGBT L2\0";
		}
		case 24:
		{
			return "Low temperature, IGBT L3\0";
		}
		case 25:
		{
			return "Low temperature, ambient\0";
		}
		case 26:
		{
			return "Low temperature, cabinet\0";
		}
		case 27:
		{
			return "Low temperature, inductor\0";
		}
		case 28:
		{
			return "Low temperature, brake chopper\0";
		}
		case 29:
		{
			return "Low temperature, control card\0";
		}
		case 31:
		{
			return "Overcurrent U, HW-driver\0";
		}
		case 32:
		{
			return "Overcurrent U, HW control card\0";
		}
		case 33:
		{
			return "Overcurrent U, software\0";
		}
		case 35:
		{
			return "Overcurrent V, HW-driver\0";
		}
		case 36:
		{
			return "Overcurrent V, HW control card\0";
		}
		case 37:
		{
			return "Overcurrent V, software\0";
		}
		case 39:
		{
			return "Overcurrent W, HW-driver\0";
		}
		case 40:
		{
			return "Overcurrent W, HW control card\0";
		}
		case 41:
		{
			return "Overcurrent W, software\0";
		}
		case 45:
		{
			return "Current Inverter asymmetric\0";
		}
		case 46:
		{
			return "Current Sum Error Inverter currents\0";
		}

		case 51:
		{
			return "Over current U, driver\0";
		}
		case 52:
		{
			return "Over current U, control card\0";
		}
		case 53:
		{
			return "Over current U, software\0";
		}
		case 54:
		{
			return "Over current V, driver\0";
		}
		case 55:
		{
			return "Over current V, control card\0";
		}
		case 56:
		{
			return "Over current V, software\0";
		}
		case 57:
		{
			return "Over current W, driver\0";
		}
		case 58:
		{
			return "Over current W, control card\0";
		}
		case 59:
		{
			return "Over current W, software\0";
		}

		case 63:
		{
			return "Overvoltage U, software\0";
		}
		case 64:
		{
			return "Overvoltage V, software\0";
		}
		case 65:
		{
			return "Overvoltage W, software\0";
		}
		case 66:
		{
			return "Overvoltage grid L1, stage 1\0";
		}
		case 67:
		{
			return "Overvoltage grid L1, stage 2\0";
		}
		case 71:
		{
			return "Overvoltage grid L2, stage 1\0";
		}
		case 72:
		{
			return "Overvoltage grid L2, stage 2\0";
		}
		case 76:
		{
			return "Overvoltage grid L3, stage 1\0";
		}
		case 77:
		{
			return "Overvoltage grid L3, stage 2\0";
		}
		case 81:
		{
			return "Over voltage DC Link, control card\0";
		}
		case 82:
		{
			return "Over voltage DC Link, software\0";
		}
		case 83:
		{
			return "Over voltage DC Link, driver\0";
		}
		case 116:
		{
			return "Undervoltage grid L1, stage 1\0";
		}
		case 117:
		{
			return "Undervoltage grid L1, stage 2\0";
		}
		case 121:
		{
			return "Undervoltage grid L2, stage 1\0";
		}
		case 122:
		{
			return "Undervoltage grid L2, stage 2\0";
		}
		case 126:
		{
			return "Undervoltage grid L3, stage 1\0";
		}
		case 127:
		{
			return "Undervoltage grid L3, stage 2\0";
		}
		case 131:
		{
			return "Undervoltage DC, control card\0";
		}
		case 132:
		{
			return "Undervoltage DC, software\0";
		}
		case 133:
		{
			return "Inverter U driver error\0";
		}
		case 134:
		{
			return "Inverter V driver error\0";
		}
		case 135:
		{
			return "Inverter W driver error\0";
		}
		case 136:
		{
			return "Undervoltage U SW\0";
		}
		case 137:
		{
			return "Undervoltage V SW\0";
		}
		case 138:
		{
			return "Undervoltage W SW\0";
		}

		case 161:
		{
			return "Inverter HW Error L1\0";
		}
		case 162:
		{
			return "Inverter HW Error L2\0";
		}
		case 163:
		{
			return "Inverter HW Error L3\0";
		}
		case 164:
		{
			return "Chopper driver error\0";
		}
		case 165:
		{
			return "Error harmonic filter\0";
		}
		case 168:
		{
			return "OV protection error\0";
		}
		case 169:
		{
			return "EtherCAT error\0";
		}
		case 171:
		{
			return "Grid rotation\0";
		}
		case 172:
		{
			return "Rotation direction not matching\0"; // was "LVRT voltage curve reached"
		}
		case 173:
		{
			return "Vector jump error\0";
		}
		case 174:
		{
			return "Grid frequency error\0";
		}
		case 175:
		{
			return "Island grid conditions detected\0";
		}
		case 176:
		{
			return "No grid\0";
		}
		case 179:
		{
			return "Power supply control card error\0";
		}
		case 181:
		{
			return "Wrong system parameter\0";
		}
		case 182:
		{
			return "EtherCAT disabled\0";
		}
		case 185:
		{
			return "Wrong setpoints EtherCAT\0";
		}
		case 187:
		{
			return "CAN transmit ID wrong\0";
		}
		case 189:
		{
			return "Sync error\0";
		}
		case 198:
		{
			return "Wrong calibration version\0";
		}
		case 199:
		{
			return "Charge circuit tripped\0";
		}

		case 220:
		{
			return "High temperature, IGBT U, driver\0";
		}
		case 221:
		{
			return "High temperature, IGBT U, software\0";
		}
		case 222:
		{
			return "High temperature, IGBT V, driver\0";
		}
		case 223:
		{
			return "High temperature, IGBT V, software\0";
		}
		case 224:
		{
			return "High temperature, IGBT W, driver\0";
		}
		case 225:
		{
			return "High temperature, IGBT W, software\0";
		}
		case 226:
		{
			return "Low temperature, IGBT U, software\0";
		}
		case 227:
		{
			return "Low temperature, IGBT V, software\0";
		}
		case 228:
		{
			return "Low temperature, IGBT W, software\0";
		}
		case 231:
		{
			return "Over current exciter, HW-driver\0";
		}
		case 232:
		{
			return "Over current exciter, control card\0";
		}
		case 233:
		{
			return "Over current exciter, software\0";
		}
		case 234:
		{
			return "Exciter HW error\0";
		}

		default:
		{
			return "No description\0";
		}
	}
}
