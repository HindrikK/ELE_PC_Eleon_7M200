#include <Mita.h>

//inputs
unsigned char DLL_IN_Initialize;
unsigned char DLL_IN_AllowStart;
unsigned char DLL_IN_StopMode;
float DLL_IN_PowerDemand;
float DLL_IN_GenSpeed;
float DLL_IN_HubWindSpeed;
float DLL_IN_WindDirectionRel;
float DLL_IN_NacAccForeAft;
float DLL_IN_NacAccSideSide;
float DLL_IN_PitchAngle_1;
float DLL_IN_PitchAngle_2;
float DLL_IN_PitchAngle_3;
float DLL_IN_RotorAzimuth;

//outputs
unsigned int DLL_OUT_ActiveCP1CodeNo;
unsigned char DLL_OUT_OperationState;
float DLL_OUT_PowerSetpoint;
float DLL_OUT_PowerOutput;
float DLL_OUT_GenTorque;
unsigned char DLL_OUT_GenConnected;
float DLL_OUT_PitchAngle_1;
float DLL_OUT_PitchAngle_2;
float DLL_OUT_PitchAngle_3;
float DLL_OUT_ControllerRpm;


// DLL input and output variable pointers

static BOOL* DLL_IN_Initialize_value;
static BOOL* DLL_IN_AllowStart_value;
static U8* DLL_IN_StopMode_value;
static F32* DLL_IN_PowerDemand_value;
static F32* DLL_IN_GenSpeed_value;
static F32* DLL_IN_HubWindSpeed_value;
static F32* DLL_IN_WindDirectionRel_value;
static F32* DLL_IN_NacAccForeAft_value;
static F32* DLL_IN_NacAccSideSide_value;
static F32* DLL_IN_PitchAngle_1_value;
static F32* DLL_IN_PitchAngle_2_value;
static F32* DLL_IN_PitchAngle_3_value;
static F32* DLL_IN_RotorAzimuth_value;

static U16* DLL_OUT_ActiveCP1CodeNo_value;
static U8* DLL_OUT_OperationState_value;
static F32* DLL_OUT_PowerSetpoint_value;
static F32* DLL_OUT_PowerOutput_value;
static F32* DLL_OUT_GenTorque_value;
static BOOL* DLL_OUT_GenConnected_value;
static F32* DLL_OUT_PitchAngle_1_value;
static F32* DLL_OUT_PitchAngle_2_value;
static F32* DLL_OUT_PitchAngle_3_value;
static F32* DLL_OUT_ControllerRpm_value;


int DLL_Initialize_Variables();
int DLL_UpdateINPUT();
int DLL_UpdateOUTPUT();