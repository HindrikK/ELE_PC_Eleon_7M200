
extern unsigned char MenuServer_enabled;

//inputs
__declspec(dllexport)
unsigned char DLL_IN_Initialize;
__declspec(dllexport)
unsigned char DLL_IN_AllowStart;
__declspec(dllexport)
unsigned char DLL_IN_StopMode;
__declspec(dllexport)
float DLL_IN_PowerDemand;
__declspec(dllexport)
float DLL_IN_GenSpeed;
__declspec(dllexport)
float DLL_IN_HubWindSpeed;
__declspec(dllexport)
float DLL_IN_WindDirectionRel;
__declspec(dllexport)
float DLL_IN_NacAccForeAft;
__declspec(dllexport)
float DLL_IN_NacAccSideSide;
__declspec(dllexport)
float DLL_IN_PitchAngle_1;
__declspec(dllexport)
float DLL_IN_PitchAngle_2;
__declspec(dllexport)
float DLL_IN_PitchAngle_3;
__declspec(dllexport)
float DLL_IN_RotorAzimuth;

//outputs
__declspec(dllexport)
unsigned int DLL_OUT_ActiveCP1CodeNo;
__declspec(dllexport)
unsigned char DLL_OUT_OperationState;
__declspec(dllexport)
float DLL_OUT_PowerSetpoint;
__declspec(dllexport)
float DLL_OUT_PowerOutput;
__declspec(dllexport)
float DLL_OUT_GenTorque;
__declspec(dllexport)
unsigned char DLL_OUT_GenConnected;
__declspec(dllexport)
float DLL_OUT_PitchAngle_1;
__declspec(dllexport)
float DLL_OUT_PitchAngle_2;
__declspec(dllexport)
float DLL_OUT_PitchAngle_3;

__declspec(dllexport)
unsigned int GetActiveCP1CodeNo();
__declspec(dllexport)
unsigned char GetOperationState();
__declspec(dllexport)
float GetPowerSetpoint();
__declspec(dllexport)
float GetPowerOutput();
__declspec(dllexport)
float GetGenTorque();
__declspec(dllexport)
unsigned char GetGenConnected();
__declspec(dllexport)
float GetPitchAngle_1();
__declspec(dllexport)
float GetPitchAngle_2();
__declspec(dllexport)
float GetPitchAngle_3();
__declspec(dllexport)
float GetControllerRpm();

__declspec(dllexport)
void SetInitialize(unsigned char);
__declspec(dllexport)
void SetAllowStart(unsigned char);
__declspec(dllexport)
void SetStopMode(unsigned char);
__declspec(dllexport)
void SetPowerDemand(float);
__declspec(dllexport)
void SetGenSpeed(float);
__declspec(dllexport)
void SetHubWindSpeed(float);
__declspec(dllexport)
void SetWindDirectionRel(float);
__declspec(dllexport)
void SetNacAccForeAft(float);
__declspec(dllexport)
void SetNacAccSideSide(float);
__declspec(dllexport)
void SetPitchAngle_1(float);
__declspec(dllexport)
void SetPitchAngle_2(float);
__declspec(dllexport)
void SetPitchAngle_3(float);
__declspec(dllexport)
void SetRotorAzimuth(float);


__declspec(dllexport)
void EnableMenuServer();

// Main entry for Eleon DLL API; call periodically; one call equals 20 ms period in realtime
__declspec(dllexport)
int __cdecl Eleon_MainCall(void);

// User this function for Bladed DISCON interface; one call equals 20 ms period in realtime
__declspec(dllexport)
void __cdecl DISCON(float* avrSWAP, int* aviFAIL, char* accINFILE, char* avcOUTNAME, char* avcMSG);


//enum OperationState
//PAT_STATE_STOPNORMAL     0
//PAT_STATE_STOPTORQUE     1
//PAT_STATE_STOPFAST       2
//PAT_STATE_STOPIMMEDIATE  3
//PAT_STATE_STOPPED        4
//PAT_STATE_LOWWIND        5
//PAT_STATE_STARTUP        6
//PAT_STATE_RAMPUP         7
//PAT_STATE_BELOWRATED     8
//PAT_STATE_RATEDSPEED     9
//PAT_STATE_RATEDPOWER    10
//PAT_STATE_LIMITED       11
//PAT_STATE_PITCHMOVE     12
//PAT_STATE_OVERSPEED     13
//PAT_STATE_NACACCEL      14
//PAT_STATE_FREEWHEEL     15


//enum StopMode
//BRAKE_PROG_50		50		// normal stop
//BRAKE_PROG_70		70		// torque aided slowdown
//BRAKE_PROG_99		99      // fast stop
//BRAKE_PROG_199	199     // immediate stop
//BRAKE_PROG_200	200     // immediate stop

// *StopMode = 0 defaults to BRAKE_PROG_50
