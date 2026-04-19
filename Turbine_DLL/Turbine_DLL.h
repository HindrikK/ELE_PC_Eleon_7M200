#ifdef ELEON_DLL_EXPORTS
#define ELEON_DLL_API __declspec(dllexport)
#else
#define ELEON_DLL_API __declspec(dllimport)
#endif

//inputs
extern ELEON_DLL_API unsigned char DLL_IN_Initialize;			// 0 - normal; 1 - trigger initialization process
extern ELEON_DLL_API unsigned char DLL_IN_AllowStart;			// 0 - stop turbine; 1 - start turbine
extern ELEON_DLL_API unsigned char DLL_IN_StopMode;				// unit: enum StopMode
extern ELEON_DLL_API float DLL_IN_PowerDemand;					// unit: [kW]; normally keep it set to nominal power value, except when manually limiting power
extern ELEON_DLL_API float DLL_IN_GenSpeed;						// unit: [rpm]
extern ELEON_DLL_API float DLL_IN_HubWindSpeed;					// unit: [m/s]
extern ELEON_DLL_API float DLL_IN_WindDirectionRel;				// unit: [deg] relative to turbine; -179,9 to 180,0
extern ELEON_DLL_API float DLL_IN_NacAccForeAft;				// unit: [m/s^2]
extern ELEON_DLL_API float DLL_IN_NacAccSideSide;				// unit: [m/s^2]
extern ELEON_DLL_API float DLL_IN_PitchAngle_1;					// unit: [deg]; actual pitch angle feedback when using external pitch drive simulation
extern ELEON_DLL_API float DLL_IN_PitchAngle_2;					// unit: [deg]
extern ELEON_DLL_API float DLL_IN_PitchAngle_3;					// unit: [deg]
extern ELEON_DLL_API float DLL_IN_RotorAzimuth;					// unit: [deg]

//outputs
extern ELEON_DLL_API unsigned int DLL_OUT_ActiveCP1CodeNo;		// turbine status code
extern ELEON_DLL_API unsigned char DLL_OUT_OperationState;		// unit: enum OperationState
extern ELEON_DLL_API float DLL_OUT_PowerSetpoint;				// unit: [kW]; power setpoint to converter
extern ELEON_DLL_API float DLL_OUT_PowerOutput;					// unit: [kW]
extern ELEON_DLL_API float DLL_OUT_GenTorque;					// unit: [Nm]
extern ELEON_DLL_API unsigned char DLL_OUT_GenConnected;		// 0 - not connected; 1 - connected
extern ELEON_DLL_API float DLL_OUT_PitchAngle_1;				// unit: [deg]; actual pitch angle output when using internal pitch drive simulation
extern ELEON_DLL_API float DLL_OUT_PitchAngle_2;				// unit: [deg]
extern ELEON_DLL_API float DLL_OUT_PitchAngle_3;				// unit: [deg]



ELEON_DLL_API unsigned int GetActiveCP1CodeNo();
ELEON_DLL_API unsigned char GetOperationState();
ELEON_DLL_API float GetPowerSetpoint();
ELEON_DLL_API float GetPowerOutput();
ELEON_DLL_API float GetGenTorque();
ELEON_DLL_API unsigned char GetGenConnected();
ELEON_DLL_API float GetPitchAngle_1();
ELEON_DLL_API float GetPitchAngle_2();
ELEON_DLL_API float GetPitchAngle_3();

ELEON_DLL_API void SetInitialize(unsigned char);
ELEON_DLL_API void SetAllowStart(unsigned char);
ELEON_DLL_API void SetStopMode(unsigned char);
ELEON_DLL_API void SetPowerDemand(float);
ELEON_DLL_API void SetGenSpeed(float);
ELEON_DLL_API void SetHubWindSpeed(float);
ELEON_DLL_API void SetWindDirectionRel(float);
ELEON_DLL_API void SetNacAccForeAft(float);
ELEON_DLL_API void SetNacAccSideSide(float);
ELEON_DLL_API void SetPitchAngle_1(float);
ELEON_DLL_API void SetPitchAngle_2(float);
ELEON_DLL_API void SetPitchAngle_3(float);
ELEON_DLL_API void SetRotorAzimuth(float);


ELEON_DLL_API void EnableMenuServer();

ELEON_DLL_API int MainCall(void);								// main function call for simulation; one call equals 20 ms period in realtime


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
