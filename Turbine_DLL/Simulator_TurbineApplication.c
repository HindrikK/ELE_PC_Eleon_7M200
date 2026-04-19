//*****************************PEPTOOL Header Start******************************
//                                                                               
//                         Copyright © 2014 Mita-Teknik.                         
//This software may only be used with WP4x00 Controllers delivered by Mita-Teknik
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL version:9.0$                                                         
// $PEPTOOL file version:101$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************

//***********************************************************************
#include <Simulator.h>
#include <Simulator_TurbineApplication.h>


#define PI 3.14159265359
#define ROTOR_ENCODER_PPR 4096		// 1024 step incremental encoder, but Mita 351 module calculates 4 steps when
									// encoder makes one step(4 encoder signal transitions happen in one step - A(ON)->B(ON)->A(OFF)->B(OFF)...)
									// This applies when no shifting(division) has been set for the gray counter in 351 parameters.




//**************************************************************************
// pointers to actual variable values in variable database structures
// pointers are used in this code, to make accessing database variables easier (and faster)
//**************************************************************************

// values as inputs to this module
BOOL * DO_SafetySystemEStopOESR_value;
S32 * V_PitchAngle_value;
//U32 * AI_GeneratorRpm_value;
S32 * V_CNV_TorqueActNm_value;
U8 * P_PowerCalcTest_value;
U16 * P_SIm_OwnCons_value;
U8 * P_Sim_GenEfficiency_value;
U16 * V_WindSpeed1Sec_value;
U32 * P_SIM_RotorInertia_value;


// values as outputs to this module
BOOL * DI_SafetySystemEStopTBp_value;
BOOL * DI_SafetySystemEStopNp_value;
BOOL * DI_SafetySystemEStopExt1_value;
BOOL * DI_SafetySystemEStopExt2_value;
BOOL * DI_SafetySystemKES_value;
BOOL * DI_SafetySystemYawCam1_value;
BOOL * DI_SafetySystemYawCam2_value;
BOOL * DI_SafetySystemYawCableTwisted_value;

BOOL * DO_SafetySystemOSCR_value;
BOOL * DI_SafetySystemK1WP2035_value;
BOOL * DI_SafetySystemK2WP2035_value;

S32 * AI_RotorRotationCnt_value;		// counter for rotor position incremental encoder

U16 * V_WindDirectionSensor1_value;
U16 * V_WindSpeedSensor1_value;
U16 * P_SIM_WindMax_value;
U16 * P_SIM_WindMin_value;
U16 * P_SIM_WindMaxChange_value;
S32 * AI_GridRealPower_value;
S32 * AI_GridReactivePower_value;

// debug print out values
F32 * V_SIM_RotorAcc_value;
S32 * V_SIM_WindTorque_value;
S32 * V_SIM_TorqueSum_value;
F32 * V_SIM_PowerCoef_value;
F32 * V_SIM_A_value;
F32 * V_SIM_B_value;
S32 * V_Cnv_GridSide_ActivePower_Total_value;



//**************************************************************************
//**************************************************************************



//**************************************************************************
// pointers to variable structs in variable database
//**************************************************************************

// values as inputs to this module
// none

// values as outputs to this module
varid_t AI_GEN_PulserFrequency_ID;
varid_t HSI_GEN_EncoderFrequency1_ID;
varid_t HSI_GEN_EncoderFrequency2_ID;
//varid_t AI_GridRealPower_ID;

//**************************************************************************
//**************************************************************************






//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++							FUNCTIONS								++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//static U16 WindSpeed_buffer[50];
//
//void ClearBuffer(U16* buffer[])
//{
//	U8 i = 0;
//	for (i; i < (sizeof(*buffer) / 2); i++)
//	{
//		buffer[i] = 0;
//	}
//}
//
////*********************************************************************
//// Average function - 1s MUST BE CALLED IN 20ms TASK
////*********************************************************************
//static U16 GetWindSpeed_1s(U16* buffer[], U16 Input)
//{
//	U8 i = 0;
//	U32 sum = 0;
//
//	for (i; i < (50 - 1); i++)
//	{
//		*buffer[i] = *buffer[i + 1];
//		sum += *buffer[i];
//	}
//	sum += Input;
//	*buffer[49] = Input;
//
//	return (sum / 50);
//}




//**************************************************************************
// Conversion RPM to rad/s
//**************************************************************************
static float Rpm_To_RadS(float inVal) { return (inVal * (float)PI) / 30; }
//**************************************************************************
//**************************************************************************




//**************************************************************************
// Random number generator
//**************************************************************************
U32 GetRandom()
{
	static U32 m_w = 0x12345678;    /* must not be zero, nor 0x464fffff */
	static U32 m_z = 0xabcdef01;    /* must not be zero, nor 0x9068ffff */

	m_z = 36969 * (m_z & 65535) + (m_z >> 16);
	m_w = 18000 * (m_w & 65535) + (m_w >> 16);

	return (m_z << 16) + m_w;  /* 32-bit result */
}
//**************************************************************************
//**************************************************************************




//**************************************************************************
// Simulates the behaviour of safety related I/O
//**************************************************************************
static void SafetySystem()
{
	//--------------------------------------------------------------------------
	// Controls rotor and generator overspeed signals
	//-------------------------------------------------------------------------
	if(*DO_SafetySystemOSCR_value)
	{
		*DI_SafetySystemK1WP2035_value = false;
		*DI_SafetySystemK2WP2035_value = false;
	}
	else
	{
		*DI_SafetySystemK1WP2035_value = true;
		*DI_SafetySystemK2WP2035_value = true;
	}
	//--------------------------------------------------------------------------

}
//**************************************************************************
//**************************************************************************






//**************************************************************************
// Rotor rotation dynamics simulation
//**************************************************************************
#define AIR_DENSITY 1.225
#define SWEPT_AREA 10490
#define ROTOR_RADIUS 58

static void Simulate_Rotation()
{
	static U32 RPMfrequency;
	static S32 RotorRotationCnt_Prev;

	static float RotorAcc = 0;			// rotor acceleration [rad/s^2]
	static float RotorSpeed = 0;		// rotor speed [rad/s]
	static float TipSpeed = 0;
	static float WindTipSpeed = 0;
	static float TipSpeedRatio = 0;
	static float PowerCoefficient = 0;
	static int WindTorque = 0;
	static int TorqueSum = 0;


	//--------------------------------------------------------------------------
	// Calculate effective rotor torque from wind
	//--------------------------------------------------------------------------
	// Calculate current tipspeed ratio
	TipSpeed = RotorSpeed * ROTOR_RADIUS;
	WindTipSpeed = (float)*V_WindSpeed1Sec_value / 100;
	TipSpeedRatio = TipSpeed / WindTipSpeed;
	//if (TipSpeedRatio < 2) TipSpeedRatio = 2;	// min. TipSpeedRatio is always 2
	// Calculate blade power coefficient based on current tipspeed ratio
	float A = -1220 / (6 * (float)(*V_PitchAngle_value / 100) + 130) + 4.05;
	float B = 33 / (8.9 * (float)(*V_PitchAngle_value / 100) + 65) - 0.25;
	PowerCoefficient = 0.23 * sin((TipSpeedRatio + A) / 1.9) + B;

	
	//if (*V_PitchAngle_value < 8991)	// pitch operate position
	//{
		if (PowerCoefficient >= 0)
		{
			if (RotorSpeed > 0)		// normal operation
			{
				WindTorque = 0.5 * AIR_DENSITY * SWEPT_AREA * pow(((float)*V_WindSpeed1Sec_value / 100), 3) * PowerCoefficient / RotorSpeed;
			}
			else	// starting rotation
			{
				WindTorque = 0.5 * AIR_DENSITY * SWEPT_AREA * pow(((float)*V_WindSpeed1Sec_value / 100), 3) * PowerCoefficient;
			}
		}
		else
		{
			if (TipSpeed > WindTipSpeed)	// rotor speed higher than wind allows
			{
				WindTorque = -RotorSpeed * *V_PitchAngle_value * 500;		// simulate the torque from air braking
			}
			else  // rotor speed lower than wind allows
			{
				PowerCoefficient = 0.01;	// set min. power coefficient
				WindTorque = 0.5 * AIR_DENSITY * SWEPT_AREA * pow(((float)*V_WindSpeed1Sec_value / 100), 3) * PowerCoefficient;
			}
		}
	//}
	/*else	// pitch feather position
	{
		if (RotorSpeed < 0.0104)
		{
			WindTorque = 0;
		}
		else	// air braking if pitch in feather, but rotor still rotating(speed > 0,1rpm)
		{
			WindTorque = -RotorSpeed * *V_PitchAngle_value * 500;		// simulate the torque from air braking
		}
	}*/

	// Calculate the sum of torque for wind and generator
	TorqueSum = WindTorque - *V_CNV_TorqueActNm_value / 10;
	//--------------------------------------------------------------------------


	//--------------------------------------------------------------------------
	// Calculate rotor acceleration[rad/s^2] based on sum of torque values and rotor inertia
	//--------------------------------------------------------------------------
	RotorAcc = (float)TorqueSum / *P_SIM_RotorInertia_value;
	//--------------------------------------------------------------------------



	//--------------------------------------------------------------------------
	// Calculate new rotor speed data based on acceleration
	//--------------------------------------------------------------------------
	RotorSpeed += (float)RotorAcc / 50;	// divide by 50, because this program runs in 20ms task
	RPMfrequency = (float)(RotorSpeed * 1000 * (ROTOR_ENCODER_PPR / 4) / 6);
	OS_VarDB_UpdateU32(HSI_GEN_EncoderFrequency1_ID, RPMfrequency);
	OS_VarDB_UpdateU32(HSI_GEN_EncoderFrequency2_ID, RPMfrequency);
	//--------------------------------------------------------------------------

	// rotor position counter
	*AI_RotorRotationCnt_value += (RPMfrequency * 4) / 50 / 1000;		// calculate how many pulses for rotor movement in 20 ms
	if (*AI_RotorRotationCnt_value >= ROTOR_ENCODER_PPR)
	{
      *AI_RotorRotationCnt_value = 0;
	}

	// generator RPM
	RPMfrequency = RPMfrequency / 43;
	OS_VarDB_UpdateU32(AI_GEN_PulserFrequency_ID, RPMfrequency);

	// debug print out
	*V_SIM_RotorAcc_value = RotorSpeed; // RotorAcc;
	*V_SIM_WindTorque_value = WindTorque;
	*V_SIM_TorqueSum_value = TorqueSum;
	*V_SIM_PowerCoef_value = PowerCoefficient;
	*V_SIM_A_value = A;
	*V_SIM_B_value = B;
}
//**************************************************************************
//**************************************************************************





//**************************************************************************
// Grid simulation
//**************************************************************************
static void Simulate_Grid()
{
	// in case of torque control mode
	//*AI_GridRealPower_value = ((*V_CNV_TorqueActNm_value / 10 * ((float)*AI_GeneratorRpm_value * (float)PI) / 30) * *P_Sim_GenEfficiency_value / 10000) - (*P_SIm_OwnCons_value * 1000);
   
   // in case of power control mode
   *AI_GridRealPower_value = (*V_Cnv_GridSide_ActivePower_Total_value * *P_Sim_GenEfficiency_value) - (*P_SIm_OwnCons_value * 1000);

	// Loop Output reactive power value
	if (*AI_GridReactivePower_value < 20000)
	{
		*AI_GridReactivePower_value += 20;
	}
	else
	{
		*AI_GridReactivePower_value = -20000;
	}
}
//**************************************************************************
//**************************************************************************





//**************************************************************************
// Weather simulation
//**************************************************************************
static void Simulate_Weather()
{
	static S16 WindChange = 0;
	static U8 counter_1s = 0;

	counter_1s++;

	//simulate windspeed value twice per second
	if (counter_1s == 25)
	{
		counter_1s = 0;

		if (*P_SIM_WindMaxChange_value != 0) {

		WindChange = *P_SIM_WindMaxChange_value - (GetRandom() % (*P_SIM_WindMaxChange_value * 2));	// get +/- value for WindChange
		*V_WindSpeedSensor1_value += WindChange;
		}

		if (*V_WindSpeedSensor1_value > *P_SIM_WindMax_value)
		{
			*V_WindSpeedSensor1_value = *P_SIM_WindMax_value  - WindChange;
		}
		else if (*V_WindSpeedSensor1_value < *P_SIM_WindMin_value)
		{
			*V_WindSpeedSensor1_value = *P_SIM_WindMin_value  - WindChange;
		}
	}
}
//**************************************************************************
//**************************************************************************




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++






//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//**************************************************************************
// SIMULATION MODE STATE MACHINE
//**************************************************************************
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// state functions declarations
static void State_Normal();
//static void State_WaitStart();
/*void State_Startup();
void State_NormalShutdown();
void State_PowerProduction();*/

//static void (*Active_State)(void) = State_WaitStart;
static void (*Active_State)(void) = State_Normal;
static void (*State_Prev)(void) = NULL;		// indicates the previous mode(sometimes it could affect the behaviour of new mode)

static BOOL StateChanged = true;			// indicates if the function/state is called the first time (startup or state change)

/*#define NORMALSHUTDOWN_DISCONNECTING 0
#define NORMALSHUTDOWN_COMPLETESTOP 1
static U8 State_NormalShutdown_Step = 0;*/






//**************************************************************************
// This function must be called once, before using other functions
// Initialize database variables pointers
//**************************************************************************
STATUS Simulator_TurbineApplication_Initialize()
{
	// get database variables IDs (pointers to database variable structs) and then
	// assign pointers to direct to the value fields of the variables (for easy direct database value access from application)
	struct os_db_variable * varID;
	int LocalStatus = 0;
	// inputs
	LocalStatus = OS_VarDB_GetVariableID("V_WindSpeed1Sec", &varID);
	if(LocalStatus < 0) {return LocalStatus; }
	V_WindSpeed1Sec_value = &(varID->c.Value.u16);
	LocalStatus = OS_VarDB_GetVariableID("P_SIM_RotorInertia", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	P_SIM_RotorInertia_value = &(varID->c.Value.u32);



	LocalStatus = OS_VarDB_GetVariableID("DO_SafetySystemOSCR", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DO_SafetySystemOSCR_value = &(varID->c.Value.bool);
	LocalStatus = OS_VarDB_GetVariableID("DI_SafetySystemK1WP2035", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DI_SafetySystemK1WP2035_value = &(varID->c.Value.bool);
	LocalStatus = OS_VarDB_GetVariableID("DI_SafetySystemK2WP2035", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DI_SafetySystemK2WP2035_value = &(varID->c.Value.bool);
	//OS_VarDB_GetVariableID("HSI_RotorRpmFrq2", &varID);
	//HSI_RotorRpmFrq2_value = &(varID->c.Value.u32);
	LocalStatus = OS_VarDB_GetVariableID("V_PitchAngle", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	V_PitchAngle_value = &(varID->c.Value.s32);
	//OS_VarDB_GetVariableID("V_SafetySystemESCStatus", &varID);
	//V_SafetySystemESCStatus_value = &(varID->c.Value.bool);
	/*OS_VarDB_GetVariableID("DI_SafetySystemEStopTBp", &varID);
	DI_SafetySystemEStopTBp_value = &(varID->c.Value.bool);
	OS_VarDB_GetVariableID("DI_SafetySystemEStopNp", &varID);
	DI_SafetySystemEStopNp_value = &(varID->c.Value.bool);
	OS_VarDB_GetVariableID("DI_SafetySystemEStopExt1", &varID);
	DI_SafetySystemEStopExt1_value = &(varID->c.Value.bool);
	OS_VarDB_GetVariableID("DI_SafetySystemEStopExt2", &varID);
	DI_SafetySystemEStopExt2_value = &(varID->c.Value.bool);
	OS_VarDB_GetVariableID("DI_SafetySystemKES", &varID);
	DI_SafetySystemKES_value = &(varID->c.Value.bool);
	OS_VarDB_GetVariableID("DI_SafetySystemYawCam1", &varID);
	DI_SafetySystemYawCam1_value = &(varID->c.Value.bool);
	OS_VarDB_GetVariableID("DI_SafetySystemYawCam2", &varID);
	DI_SafetySystemYawCam2_value = &(varID->c.Value.bool);
	OS_VarDB_GetVariableID("DI_SafetySystemYawCableTwisted", &varID);
	DI_SafetySystemYawCableTwisted_value = &(varID->c.Value.bool);*/
	LocalStatus = OS_VarDB_GetVariableID("AI_GridRealPower", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	AI_GridRealPower_value = &(varID->c.Value.s32);
	//OS_VarDB_GetVariableID("V_GeneratorRpm", &varID);
	//AI_GeneratorRpm_value = &(varID->c.Value.u32);
	LocalStatus =  OS_VarDB_GetVariableID("V_CNV_TorqueActNm", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	V_CNV_TorqueActNm_value = &(varID->c.Value.s32);

	LocalStatus = OS_VarDB_GetVariableID("V_Cnv_GridSide_ActivePower_Total", &varID);
	V_Cnv_GridSide_ActivePower_Total_value = &(varID->c.Value.s32);

	LocalStatus = OS_VarDB_GetVariableID("AI_GEN_EncoderCounter", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	AI_RotorRotationCnt_value = &(varID->c.Value.s32);

	LocalStatus = OS_VarDB_GetVariableID("P_SIm_OwnCons", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	P_SIm_OwnCons_value = &(varID->c.Value.u16);
	LocalStatus = OS_VarDB_GetVariableID("P_Sim_GenEfficiency", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	P_Sim_GenEfficiency_value = &(varID->c.Value.u8);
	
	//LocalStatus = OS_VarDB_GetVariableID("P_PowerCalcTest", &varID);
	//if (LocalStatus < 0) { return LocalStatus; }
	//P_PowerCalcTest_value = &(varID->c.Value.u8);

	LocalStatus = OS_VarDB_GetVariableID("V_WindDirectionSensor1", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	V_WindDirectionSensor1_value = &(varID->c.Value.u16);
	LocalStatus = OS_VarDB_GetVariableID("V_WindSpeedSensor1", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	V_WindSpeedSensor1_value = &(varID->c.Value.u16);
	LocalStatus = OS_VarDB_GetVariableID("P_SIM_WindMax", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	P_SIM_WindMax_value = &(varID->c.Value.u16);
	LocalStatus = OS_VarDB_GetVariableID("P_SIM_WindMin", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	P_SIM_WindMin_value = &(varID->c.Value.u16);
	LocalStatus = OS_VarDB_GetVariableID("P_SIM_WindMaxChange", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	P_SIM_WindMaxChange_value = &(varID->c.Value.u16);
	LocalStatus = OS_VarDB_GetVariableID("AI_GridReactivePower", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	AI_GridReactivePower_value = &(varID->c.Value.s32);
	/*OS_VarDB_GetVariableID("", &varID);
	_value = &(varID->c.Value.);*/
	


	//OS_VarDB_GetVariableID("V_Debug", &varID);
	//V_Debug_value = &(varID->c.Value.s32);
	//OS_VarDB_GetVariableID("V_Debug2", &varID);
	//V_Debug2_value = &(varID->c.Value.f32);
	



	// get database variables IDs (pointers to database variable structs)
	LocalStatus = OS_VarDB_GetVariableID("AI_GEN_PulserFrequency", &AI_GEN_PulserFrequency_ID);
	if (LocalStatus < 0) { return LocalStatus; }
	LocalStatus = OS_VarDB_GetVariableID("HSI_GEN_EncoderFrequency1", &HSI_GEN_EncoderFrequency1_ID);
	if (LocalStatus < 0) { return LocalStatus; }
	LocalStatus = OS_VarDB_GetVariableID("HSI_GEN_EncoderFrequency2", &HSI_GEN_EncoderFrequency2_ID);
	if (LocalStatus < 0) { return LocalStatus; }
	//OS_VarDB_GetVariableID("AI_GridRealPower", &AI_GridRealPower_ID);

	// internal initializations
	//ClearBuffer(&WindSpeed_buffer);
	//*V_WindSpeedSensor1_value = *P_SIM_WindMin;

	// debug print out values
	LocalStatus = OS_VarDB_GetVariableID("V_SIM_RotorAcc", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	V_SIM_RotorAcc_value = &(varID->c.Value.f32);
	LocalStatus = OS_VarDB_GetVariableID("V_SIM_WindTorque", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	V_SIM_WindTorque_value = &(varID->c.Value.s32);
	LocalStatus = OS_VarDB_GetVariableID("V_SIM_TorqueSum", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	V_SIM_TorqueSum_value = &(varID->c.Value.s32);
	LocalStatus = OS_VarDB_GetVariableID("V_SIM_PowerCoef", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	V_SIM_PowerCoef_value = &(varID->c.Value.s32);
	LocalStatus = OS_VarDB_GetVariableID("V_SIM_A", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	V_SIM_A_value = &(varID->c.Value.s32);
	LocalStatus = OS_VarDB_GetVariableID("V_SIM_B", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	V_SIM_B_value = &(varID->c.Value.s32);
	return OS_SUCCESS;
}






//**************************************************************************
// Call the appropriate state function depending on simulation state
//**************************************************************************
void Simulator_TurbineApplication_Control()
{
	//--------------------------------------------------------------------------
	// MODE FIRST ENTRY
	//--------------------------------------------------------------------------
	if(Sim_ModeChanged)
	{
		Sim_ModeChanged = false;
		strcpy(V_SimulationModeTxt_value, "Turbine application");
		StateChanged = true;
		

		//**********************************************************************
		// Initialize necessary I/O values
		//**********************************************************************
		BOOL ValueDigital;
		U8 ValueAnalogU8;
		S16 ValueAnalogS16;
		U16 ValueAnalogU16;
		U32 ValueAnalogU32;
		S32 ValueAnalogS32;
		

		ValueDigital = true;

		// E-Stop Chain
		OS_VarDB_UpdateVariableByName("DI_SafetySystemEStopTBp", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_SafetySystemEStopNp", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_SafetySystemEStopExt1", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_SafetySystemEStopExt2", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_SafetySystemKES", &ValueDigital, 1);
		//OS_VarDB_UpdateVariableByName("DI_SafetySystemYawCam1", &ValueDigital, 1);
		//OS_VarDB_UpdateVariableByName("DI_SafetySystemYawCam2", &ValueDigital, 1);
		//OS_VarDB_UpdateVariableByName("DI_SafetySystemYawCableTwisted", &ValueDigital, 1);

		// Safety Chain
		OS_VarDB_UpdateVariableByName("DI_SafetySystemXCK1", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_SafetySystemXCK2", &ValueDigital, 1);
		//OS_VarDB_UpdateVariableByName("DI_SafetySystemK1WP2035", &ValueDigital, 1);
		//OS_VarDB_UpdateVariableByName("DI_SafetySystemK2WP2035", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_SafetySystemKSSR", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_SafetySystemSCMS", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_SafetySystemCONV", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_SafetySystemMCCB", &ValueDigital, 1);

		// Yaw
		ValueAnalogS16 = 12000;	// 12 mA - 0 degrees position
		OS_VarDB_UpdateVariableByName("AI_YawAbsoluteEncoderSignal", &ValueAnalogS16, 2);

		// Yaw Motor Control
		OS_VarDB_UpdateVariableByName("DI_YawMotor1MCBs", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_YawMotor2MCBs", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_YawMotor3MCBs", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_YawMotor4MCBs", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_YawMotor5MCBs", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_YawMotor6MCBs", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_YawMotor7MCBs", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_YawMotor8MCBs", &ValueDigital, 1);

		// Transformer
		OS_VarDB_UpdateVariableByName("DI_Transformer_GasReed", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_Transformer_PressureSwitch", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_Transformer_ThermostatT1", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_Transformer_ThermostatT2", &ValueDigital, 1);

		// Panels
		OS_VarDB_UpdateVariableByName("DI_Panels_MCCB_StatusBasePanel", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_PanelsHubHeatingCoolingSystemFB", &ValueDigital, 1);

		// Tower Base
		OS_VarDB_UpdateVariableByName("DI_TowerBase_BoltMonitoringSystemSystemOk", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_TowerBase_BoltMonitoringSystemBoltsOk", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_GroundWaterLevelSensor", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_TowerBaseSmokeDetect", &ValueDigital, 1);

		// Surge Protection
		OS_VarDB_UpdateVariableByName("DI_SurgeProtectionTowerBase", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_SurgeProtectionNacelle", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_SurgeProtectionTowerBase400V", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_SurgeProtectionNacelle400V", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_SurgeProtectionHub", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_SurgeProtectionHub400V", &ValueDigital, 1);

		// Generator
		ValueAnalogS16 = 12000;
		OS_VarDB_UpdateVariableByName("AI_GeneratorStatorAirGap1", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("AI_GeneratorStatorAirGap2", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("AI_GeneratorStatorAirGap3", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("AI_GeneratorStatorAirGap4", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("AI_GeneratorStatorAirGap5", &ValueAnalogS16, 2);
      OS_VarDB_UpdateVariableByName("DI_GEN_BoltBreakSensor", &ValueDigital, 1);

		// Generator Cooling
		ValueAnalogS16 = 25;		// 25 degrees celsius
		OS_VarDB_UpdateVariableByName("DI_GeneratorFan1ContactorFB", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_GeneratorFan2ContactorFB", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureHubSide1", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureHubSide2", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureHubSide3", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureHubSide4", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureHubSide5", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureHubSide6", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide1", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide2", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide3", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide4", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide5", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide6", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide7", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide8", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide9", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide10", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide11", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide12", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide13", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide14", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide15", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide16", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide17", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide18", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide19", &ValueAnalogS16, 2);
		OS_VarDB_UpdateVariableByName("PT_GeneratorTemperatureNacelleSide20", &ValueAnalogS16, 2);
		ValueAnalogS16 = 250;		// 25 degrees celsius
		OS_VarDB_UpdateVariableByName("PT_GeneratorBearingTemperature", &ValueAnalogS16, 2);
		ValueAnalogS16 = 3000;
		OS_VarDB_UpdateVariableByName("AI_GeneratorBearingTemperature2", &ValueAnalogS16, 2);

		// Outdoor Temperature
		ValueAnalogS16 = 10000;
		OS_VarDB_UpdateVariableByName("AI_OutdoorTempSensor4_Curr", &ValueAnalogS16, 2);

		// Hydraulic Pump
		ValueAnalogS16 = 4000;
		OS_VarDB_UpdateVariableByName("DI_HydrOilPump_MCBFeedback", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("AI_Hydraulic_PressureMa", &ValueAnalogS16, 2);

		// Flight Warning Light
		OS_VarDB_UpdateVariableByName("DI_ObstructionLightAlarm", &ValueDigital, 1);

		// Hub
		OS_VarDB_UpdateVariableByName("DI_Hub400V_ON", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_Hub_BoltMonitoringSystemOk1", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_Hub_BoltMonitoringBoltOk1", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_Hub_BoltMonitoringSystemOk2", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_Hub_BoltMonitoringBoltOk2", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_HubSmokeDetect", &ValueDigital, 1);

		// Inverter Cooling
		OS_VarDB_UpdateVariableByName("DI_CNVC_PumpMCB", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_CNVC_CoolantFanMCB", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_CNVC_CoolantLevel", &ValueDigital, 1);
      ValueAnalogS16 = 250;		// 25 degrees celsius
		OS_VarDB_UpdateVariableByName("PT_CNVC_CoolantHotTemp", &ValueAnalogS16, 2);
      OS_VarDB_UpdateVariableByName("PT_CNVC_CoolantCooledTemp", &ValueAnalogS16, 2);
      OS_VarDB_UpdateVariableByName("DI_CNVC_OutdoorFanMCB", &ValueDigital, 1);
      OS_VarDB_UpdateVariableByName("DI_CNVC_OutdoorFanHealth", &ValueDigital, 1);

		// Air Pressure
		ValueAnalogS16 = 12000;
		OS_VarDB_UpdateVariableByName("AI_AirPressure", &ValueAnalogS16, 2);

		// Rotor
		OS_VarDB_UpdateVariableByName("DI_RotorOneUnlocked", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_RotorTwoUnlocked", &ValueDigital, 1);
		
		// Operate
		OS_VarDB_UpdateVariableByName("DI_ServiceModeSwitch", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_ManualStopNacelle", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_ManualStopTowerBase", &ValueDigital, 1);

		// Grid
		ValueAnalogU16 = 2;
		OS_VarDB_UpdateVariableByName("AI_GridL1Current", &ValueAnalogU16, 2);
		OS_VarDB_UpdateVariableByName("AI_GridL2Current", &ValueAnalogU16, 2);
		OS_VarDB_UpdateVariableByName("AI_GridL3Current", &ValueAnalogU16, 2);
		OS_VarDB_UpdateVariableByName("AI_GridCurrent", &ValueAnalogU16, 2);
		ValueAnalogU32 = 350;
		OS_VarDB_UpdateVariableByName("AI_GridL1Voltage", &ValueAnalogU32, 4);
		OS_VarDB_UpdateVariableByName("AI_GridL2Voltage", &ValueAnalogU32, 4);
		OS_VarDB_UpdateVariableByName("AI_GridL3Voltage", &ValueAnalogU32, 4);
		OS_VarDB_UpdateVariableByName("AI_GridVoltage", &ValueAnalogU32, 4);
		ValueAnalogU32 = 50000;
		OS_VarDB_UpdateVariableByName("AI_GridFrequency", &ValueAnalogU32, 4);
		ValueAnalogU32 = 120000;
		OS_VarDB_UpdateVariableByName("AI_GridL1L2PhaseShift", &ValueAnalogU32, 4);
		ValueAnalogU32 = 240000;
		OS_VarDB_UpdateVariableByName("AI_GridL1L3PhaseShift", &ValueAnalogU32, 4);
		ValueAnalogS32 = -1000;
		OS_VarDB_UpdateVariableByName("AI_GridReactivePower", &ValueAnalogS32, 4);
		ValueAnalogS16 = 990;
		OS_VarDB_UpdateVariableByName("AI_GridCosPhi", &ValueAnalogS16, 2);
		ValueAnalogS32 = -2500;
		OS_VarDB_UpdateVariableByName("AI_GridRealPower", &ValueAnalogS32, 4);

		// Nacelle
		OS_VarDB_UpdateVariableByName("DI_NacelleSmokeDetect", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_Nacelle_MCB_FB_PowerBeforeSC", &ValueDigital, 1);
		OS_VarDB_UpdateVariableByName("DI_Nacelle_MCB_FB_PowerAfterSC", &ValueDigital, 1);
		ValueAnalogS16 = 25;
		OS_VarDB_UpdateVariableByName("PT_NacelleTemp", &ValueAnalogS16, 2);
      
      // Nacelle Acceleration
      ValueAnalogS16 = 5000;
		OS_VarDB_UpdateVariableByName("AI_NAC_AccSideSide", &ValueAnalogS16, 2);
      OS_VarDB_UpdateVariableByName("AI_NAC_AccForeAft", &ValueAnalogS16, 2);

		// Weather data
		/*ValueAnalogU16 = 560;
		OS_VarDB_UpdateVariableByName("V_WindSpeedSensor1", &ValueAnalogU16, 2);*/
		ValueAnalogU16 = 0;
		OS_VarDB_UpdateVariableByName("V_WindDirectionSensor1", &ValueAnalogU16, 2);
		ValueAnalogS16 = 234;
		OS_VarDB_UpdateVariableByName("V_OutdoorTempSensor1", &ValueAnalogS16, 2);
		/*OS_VarDB_UpdateVariableByName("", &ValueDigital, 1);*/


		/* *DI_SafetySystemEStopTBp_value = true;
		*DI_SafetySystemEStopNp_value = true;
		*DI_SafetySystemEStopExt1_value = true;
		*DI_SafetySystemEStopExt2_value = true;
		*DI_SafetySystemKES_value = true;
		*DI_SafetySystemYawCam1_value = true;
		*DI_SafetySystemYawCam2_value = true;
		*DI_SafetySystemYawCableTwisted_value = true;*/

		//**********************************************************************
		//**********************************************************************
	}
	//--------------------------------------------------------------------------
	
	
	//--------------------------------------------------------------------------
	// MODE OPERATION LOOP
	//--------------------------------------------------------------------------
	SafetySystem();
	(*Active_State)();	// call the simulation function according to current turbine state
	//--------------------------------------------------------------------------
}




void State_Normal()
{
	Simulate_Rotation();
	Simulate_Grid();
	Simulate_Weather();
}




/*
//**************************************************************************
// STATE - Wait start command from OS menu
//**************************************************************************
static void State_WaitStart()
{
	//--------------------------------------------------------------------------
	// STATE FIRST ENTRY
	//--------------------------------------------------------------------------
	if(StateChanged)
	{
		StateChanged = false;
		strcpy(V_SimulationStateTxt_value, "Waiting for start");
		
		// STATE INITIALIZATION CODE HERE
	}
	//--------------------------------------------------------------------------
	
	
	//--------------------------------------------------------------------------
	// STATE OPERATION LOOP
	//--------------------------------------------------------------------------
	// some code here
	//--------------------------------------------------------------------------
	
	
	//--------------------------------------------------------------------------
	// STATE EXIT CONDITIONS
	//--------------------------------------------------------------------------
	if(*V_SimStartTurbine_value)	// start command received
	{
		*V_SimStartTurbine_value = false;
		
		StateChanged = true;
		State_Prev = Active_State;
		//Active_State = State_Startup;
	}
	//--------------------------------------------------------------------------
}


//**************************************************************************
// STATE - Startup
//**************************************************************************
static void State_Startup()
{
	//--------------------------------------------------------------------------
	// STATE FIRST ENTRY
	//--------------------------------------------------------------------------
	if(StateChanged)
	{
		StateChanged = false;
		strcpy(V_SimulationStateTxt_value, "Startup");
		
		*GH_CI_AlgStartupTurbine_value = false;
		*GH_CI_AlgAllBladesAtFeather_value = false;
	}
	//--------------------------------------------------------------------------
	
	
	//--------------------------------------------------------------------------
	// STATE OPERATION LOOP
	//--------------------------------------------------------------------------
	PitchControl();
	RotorRotation();
	PowerConverter();
	//--------------------------------------------------------------------------
	
	
	//--------------------------------------------------------------------------
	// STATE EXIT CONDITIONS
	//--------------------------------------------------------------------------
	//U8 y;
	//OS_VarDB_ReadVariable(GH_CI_AlgGeneratorSpeed_varID, &y, 1, dummyTimeStamp);
	
	if( *V_SimStopTurbine_value )	// if OS normal shutdown command
	{
		*V_SimStopTurbine_value = false;
	
		StateChanged = true;
		State_Prev = Active_State;
		Active_State = State_NormalShutdown;
		
		*GH_CI_AlgNormalShutdown_value = true;
	}
	else if(*GH_CI_AlgPcsSynchronised_value)	// if converter synchronised
	{
		StateChanged = true;
		State_Prev = Active_State;
		Active_State = State_PowerProduction;
	}
	//--------------------------------------------------------------------------
}


//**************************************************************************
// STATE - Power production
//**************************************************************************
static void State_PowerProduction()
{
	//--------------------------------------------------------------------------
	// STATE FIRST ENTRY
	//--------------------------------------------------------------------------
	if(StateChanged)
	{
		StateChanged = false;
		strcpy(V_SimulationStateTxt_value, "Production");
		
		*GH_CI_AlgPcsSynchronised_value = true;
	}
	//--------------------------------------------------------------------------
	
	
	//--------------------------------------------------------------------------
	// STATE OPERATION LOOP
	//--------------------------------------------------------------------------
	PitchControl();
	RotorRotation();
	PowerConverter();
	//--------------------------------------------------------------------------
	
	
	//--------------------------------------------------------------------------
	// STATE EXIT CONDITIONS
	//--------------------------------------------------------------------------
	if(*V_SimStopTurbine_value)	// normal shutdown
	{
		*V_SimStopTurbine_value = false;
	
		StateChanged = true;
		State_Prev = Active_State;
		Active_State = State_NormalShutdown;
		
		*GH_CI_AlgNormalShutdown_value = true;
	}
	//--------------------------------------------------------------------------
}


//**************************************************************************
// STATE - Normal shutdown
//**************************************************************************
static void State_NormalShutdown()
{	
	//--------------------------------------------------------------------------
	// STATE FIRST ENTRY
	//--------------------------------------------------------------------------
	if(StateChanged)
	{
		StateChanged = false;
		strcpy(V_SimulationStateTxt_value, "Normal shutdown");
		
		*GH_CI_AlgNormalShutdown_value = false;
		
		// select different behaviour based on previous state
		if(State_Prev == State_Startup)	// if previous state was Startup then skip grid disconnecting step
		{
			State_NormalShutdown_Step = NORMALSHUTDOWN_COMPLETESTOP;
		}
	}
	
	
	//--------------------------------------------------------------------------
	// STATE OPERATION LOOP
	//--------------------------------------------------------------------------
	PitchControl();
	RotorRotation();
	PowerConverter();

	switch(State_NormalShutdown_Step)
	{
		case NORMALSHUTDOWN_DISCONNECTING:
		
			// step exit condition
			//--------------------------------------------------------------------------
			if(!*GH_CO_AlgPcsSynchroniseRequest_value)	// wait for deactivation of Pcs sync request
			{
				State_NormalShutdown_Step = NORMALSHUTDOWN_COMPLETESTOP;
			}
			//--------------------------------------------------------------------------
			break;
		
		case NORMALSHUTDOWN_COMPLETESTOP:
		
			// check if all blades are in feather position (tolerance +/-0,3 degrees)
			if((*GH_CI_AlgPitchPosition1_value <= (PITCH_FEATHER_RAD + 0.005236) && *GH_CI_AlgPitchPosition1_value >= (PITCH_FEATHER_RAD - 0.005236)) &&
				(*GH_CI_AlgPitchPosition2_value <= (PITCH_FEATHER_RAD + 0.005236) && *GH_CI_AlgPitchPosition2_value >= (PITCH_FEATHER_RAD - 0.005236)) &&
				(*GH_CI_AlgPitchPosition3_value <= (PITCH_FEATHER_RAD + 0.005236) && *GH_CI_AlgPitchPosition3_value >= (PITCH_FEATHER_RAD - 0.005236)))
			{
				*GH_CI_AlgAllBladesAtFeather_value = true;
			}
			
			//--------------------------------------------------------------------------
			// STATE EXIT CONDITIONS
			//--------------------------------------------------------------------------
			if(*GH_CO_AlgWaitForStartup_value)		// shutdown procedure completed
			{	
				StateChanged = true;
				State_Prev = Active_State;
				Active_State = State_WaitStart;
			}
			//--------------------------------------------------------------------------
			break;
	}
	//--------------------------------------------------------------------------
}*/

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//**************************************************************************
//**************************************************************************
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
