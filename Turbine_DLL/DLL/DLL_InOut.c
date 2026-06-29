#include "DLL_InOut.h"


//inputs
unsigned char DLL_IN_Initialize = false;
unsigned char DLL_IN_AllowStart = false;
unsigned char DLL_IN_StopMode = 0;
float DLL_IN_PowerDemand = 3000;
float DLL_IN_GenSpeed = 0;
float DLL_IN_HubWindSpeed = 0;
float DLL_IN_WindDirectionRel = 0;
float DLL_IN_NacAccForeAft = 0;
float DLL_IN_NacAccSideSide = 0;
float DLL_IN_PitchAngle_1 = 0;
float DLL_IN_PitchAngle_2 = 0;
float DLL_IN_PitchAngle_3 = 0;
float DLL_IN_RotorAzimuth = 0;

//outputs
unsigned int DLL_OUT_ActiveCP1CodeNo = 0;
unsigned char DLL_OUT_OperationState = 0;
float DLL_OUT_PowerSetpoint = 0;
float DLL_OUT_PowerOutput = 0;
float DLL_OUT_GenTorque = 0;
unsigned char DLL_OUT_GenConnected = false;
float DLL_OUT_PitchAngle_1 = 0;
float DLL_OUT_PitchAngle_2 = 0;
float DLL_OUT_PitchAngle_3 = 0;


int DLL_Initialize_Variables()
{
	int LocalStatus = 0;
	struct os_db_variable* varID;


	LocalStatus = OS_VarDB_GetVariableID("DLL_IN_Initialize", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_IN_Initialize_value = &(varID->c.Value.u8);

	LocalStatus = OS_VarDB_GetVariableID("DLL_IN_AllowStart", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_IN_AllowStart_value = &(varID->c.Value.u8);

	LocalStatus = OS_VarDB_GetVariableID("DLL_IN_StopMode", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_IN_StopMode_value = &(varID->c.Value.u8);

	LocalStatus = OS_VarDB_GetVariableID("DLL_IN_PowerDemand", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_IN_PowerDemand_value = &(varID->c.Value.f32);

	LocalStatus = OS_VarDB_GetVariableID("DLL_IN_GenSpeed", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_IN_GenSpeed_value = &(varID->c.Value.f32);

	LocalStatus = OS_VarDB_GetVariableID("DLL_IN_HubWindSpeed", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_IN_HubWindSpeed_value = &(varID->c.Value.f32);

	LocalStatus = OS_VarDB_GetVariableID("DLL_IN_WindDirectionRel", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_IN_WindDirectionRel_value = &(varID->c.Value.f32);

	LocalStatus = OS_VarDB_GetVariableID("DLL_IN_NacAccForeAft", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_IN_NacAccForeAft_value = &(varID->c.Value.f32);

	LocalStatus = OS_VarDB_GetVariableID("DLL_IN_NacAccSideSide", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_IN_NacAccSideSide_value = &(varID->c.Value.f32);

	LocalStatus = OS_VarDB_GetVariableID("DLL_IN_PitchAngle_1", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_IN_PitchAngle_1_value = &(varID->c.Value.f32);

	LocalStatus = OS_VarDB_GetVariableID("DLL_IN_PitchAngle_2", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_IN_PitchAngle_2_value = &(varID->c.Value.f32);

	LocalStatus = OS_VarDB_GetVariableID("DLL_IN_PitchAngle_3", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_IN_PitchAngle_3_value = &(varID->c.Value.f32);

	LocalStatus = OS_VarDB_GetVariableID("DLL_IN_RotorAzimuth", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_IN_RotorAzimuth_value = &(varID->c.Value.f32);


	LocalStatus = OS_VarDB_GetVariableID("V_ActiveCP1CodeNo", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_OUT_ActiveCP1CodeNo_value = &(varID->c.Value.u16);

	LocalStatus = OS_VarDB_GetVariableID("DLL_OUT_OperationState", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_OUT_OperationState_value = &(varID->c.Value.u8);

	LocalStatus = OS_VarDB_GetVariableID("DLL_OUT_PowerSetpoint", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_OUT_PowerSetpoint_value = &(varID->c.Value.f32);

	LocalStatus = OS_VarDB_GetVariableID("DLL_OUT_PowerOutput", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_OUT_PowerOutput_value = &(varID->c.Value.f32);

	LocalStatus = OS_VarDB_GetVariableID("DLL_OUT_GenTorque", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_OUT_GenTorque_value = &(varID->c.Value.f32);

	LocalStatus = OS_VarDB_GetVariableID("DLL_OUT_GenConnected", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_OUT_GenConnected_value = &(varID->c.Value.bool);

	LocalStatus = OS_VarDB_GetVariableID("DLL_OUT_PitchAngle_1", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_OUT_PitchAngle_1_value = &(varID->c.Value.f32);

	LocalStatus = OS_VarDB_GetVariableID("DLL_OUT_PitchAngle_2", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_OUT_PitchAngle_2_value = &(varID->c.Value.f32);

	LocalStatus = OS_VarDB_GetVariableID("DLL_OUT_PitchAngle_3", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_OUT_PitchAngle_3_value = &(varID->c.Value.f32);

	LocalStatus = OS_VarDB_GetVariableID("DLL_OUT_ControllerRpm", &varID);
	if (LocalStatus < 0) { return LocalStatus; }
	DLL_OUT_ControllerRpm_value = &(varID->c.Value.f32);


	return 0;
}

int DLL_UpdateINPUT()
{
	(*DLL_IN_Initialize_value) = DLL_IN_Initialize;
	(*DLL_IN_AllowStart_value) = DLL_IN_AllowStart;
	(*DLL_IN_StopMode_value) = DLL_IN_StopMode;
	(*DLL_IN_PowerDemand_value) = DLL_IN_PowerDemand;
	(*DLL_IN_GenSpeed_value) = DLL_IN_GenSpeed;
	(*DLL_IN_HubWindSpeed_value) = DLL_IN_HubWindSpeed;
	(*DLL_IN_WindDirectionRel_value) = DLL_IN_WindDirectionRel;
	(*DLL_IN_NacAccForeAft_value) = DLL_IN_NacAccForeAft;
	(*DLL_IN_NacAccSideSide_value) = DLL_IN_NacAccSideSide;
	(*DLL_IN_PitchAngle_1_value) = DLL_IN_PitchAngle_1;
	(*DLL_IN_PitchAngle_2_value) = DLL_IN_PitchAngle_2;
	(*DLL_IN_PitchAngle_3_value) = DLL_IN_PitchAngle_3;
	(*DLL_IN_RotorAzimuth_value) = DLL_IN_RotorAzimuth;

	return 0;
}

int DLL_UpdateOUTPUT()
{
	DLL_OUT_ActiveCP1CodeNo = *DLL_OUT_ActiveCP1CodeNo_value;
	DLL_OUT_OperationState = *DLL_OUT_OperationState_value;
	DLL_OUT_PowerSetpoint = *DLL_OUT_PowerSetpoint_value;
	DLL_OUT_PowerOutput = *DLL_OUT_PowerOutput_value;
	DLL_OUT_GenTorque = *DLL_OUT_GenTorque_value;
	DLL_OUT_GenConnected = *DLL_OUT_GenConnected_value;
	DLL_OUT_PitchAngle_1 = *DLL_OUT_PitchAngle_1_value;
	DLL_OUT_PitchAngle_2 = *DLL_OUT_PitchAngle_2_value;
	DLL_OUT_PitchAngle_3 = *DLL_OUT_PitchAngle_3_value;
	DLL_OUT_ControllerRpm = *DLL_OUT_ControllerRpm_value;

	return 0;
}