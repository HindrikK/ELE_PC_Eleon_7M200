#include "Eleon_DLL_API.h"

#include <Mita.h>
#include "DLL/DLL_InOut.h"


__declspec(dllexport)
unsigned int GetActiveCP1CodeNo() {
	return DLL_OUT_ActiveCP1CodeNo;
}

__declspec(dllexport)
unsigned char GetOperationState() {
	return DLL_OUT_OperationState;
}
__declspec(dllexport)
float GetPowerSetpoint() {
	return DLL_OUT_PowerSetpoint;
}
__declspec(dllexport)
float GetPowerOutput() {
	return DLL_OUT_PowerOutput;
}
__declspec(dllexport)
float GetGenTorque() {
	return DLL_OUT_GenTorque;
}
__declspec(dllexport)
unsigned char GetGenConnected() {
	return DLL_OUT_GenConnected;
}
__declspec(dllexport)
float GetPitchAngle_1() {
	return DLL_OUT_PitchAngle_1;
}
__declspec(dllexport)
float GetPitchAngle_2() {
	return DLL_OUT_PitchAngle_2;
}
__declspec(dllexport)
float GetPitchAngle_3() {
	return DLL_OUT_PitchAngle_3;
}

__declspec(dllexport)
float GetControllerRpm() {
	return DLL_OUT_ControllerRpm;
}


__declspec(dllexport)
void SetInitialize(unsigned char  Initialize) {
	DLL_IN_Initialize = Initialize;
	return 0;
}
__declspec(dllexport)
void SetAllowStart(unsigned char  AllowStart) {
	DLL_IN_AllowStart = AllowStart;
	return 0;
}
__declspec(dllexport)
void SetStopMode(unsigned char  stopMode) {
	DLL_IN_StopMode = stopMode;
	return 0;
}
__declspec(dllexport)
void SetPowerDemand(float PowerDemand) {
	DLL_IN_PowerDemand = PowerDemand;
	return 0;
}
__declspec(dllexport)
void SetGenSpeed(float Genspeed) {
	DLL_IN_GenSpeed = Genspeed;
	return 0;
}
__declspec(dllexport)
void SetHubWindSpeed(float windSpeed) {
	DLL_IN_HubWindSpeed = windSpeed;
	return 0;
}
__declspec(dllexport)
void SetWindDirectionRel(float windDirRel) {
	DLL_IN_WindDirectionRel = windDirRel;
	return 0;
}
__declspec(dllexport)
void SetNacAccForeAft(float accel) {
	DLL_IN_NacAccForeAft = accel;
	return 0;
}
__declspec(dllexport)
void SetNacAccSideSide(float accel) {
	DLL_IN_NacAccSideSide = accel;
	return 0;
}
__declspec(dllexport)
void SetPitchAngle_1(float angle) {
	DLL_IN_PitchAngle_1 = angle;
	return 0;
}
__declspec(dllexport)
void SetPitchAngle_2(float angle) {
	DLL_IN_PitchAngle_2 = angle;
	return 0;
}
__declspec(dllexport)
void SetPitchAngle_3(float angle) {
	DLL_IN_PitchAngle_3 = angle;
	return 0;
}
__declspec(dllexport)
void SetRotorAzimuth(float angle) {
	DLL_IN_RotorAzimuth = angle;
	return 0;
}
__declspec(dllexport)
void EnableMenuServer() {
	MenuServer_enabled = true;
}

__declspec(dllexport)
int Eleon_MainCall()
{
	static BOOL firstentry = true;
	int result;

	if (firstentry)
	{
		//DLL_IN_Initialize = true;
		MainCall();    // make one call just to get initialized
		//DLL_IN_Initialize = false;
		firstentry = false;
	}

	result = MainCall();
	if (result < 0) {
		return result;
	}

	return 0;
}