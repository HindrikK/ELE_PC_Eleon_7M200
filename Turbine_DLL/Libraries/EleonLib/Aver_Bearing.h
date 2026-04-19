//*****************************PEPTOOL Header Start******************************
//                                                                               
//                            Copyright © 2014 Eleon.                            
//                                                                               
//*******************************************************************************
//                                                                               
// $PEPTOOL file version:103$                                                    
//                                                                               
//******************************PEPTOOL Header End*******************************
#ifndef FILE_AVER_BEARING_H
#define FILE_AVER_BEARING_H

#include <lib_main.h>

#define AVGBEAR_BUFLEN100MS	 5
#define AVGBEAR_BUFLEN1S	10
#define AVGBEAR_BUFLEN3S	30
#define AVGBEAR_BUFLEN30S	30
#define AVGBEAR_BUFLEN10M	20

//*******************************************************************************
// This function calculates the real average value of directional bearing as
// 0-360 deg angle. The resulting average bearing can be from 0 to 360.
//
// INITIALIZE FUNCTION NEEDS TO BE CALLED BEFORE ANY OTHER, otherwise won't work
// UPDATE FUNCTION HAS TO BE CALLED WITH 20 ms INTERVALS to get correct timing
//*******************************************************************************


struct AvgBearing_F32_20ms_Buffer
{
	F32* data_X;
	F32* data_Y;
	F32 sum_X;
	F32 sum_Y;
	F32 avgResult_X;
	F32 avgResult_Y;
	F32 avgBearing;
	int dataCount;
	int index;
};

struct AvgBearing_F32_20ms_Struct
{
	BOOL Initialized;

	struct AvgBearing_F32_20ms_Buffer buffer_100ms;
	struct AvgBearing_F32_20ms_Buffer buffer_1s;
	struct AvgBearing_F32_20ms_Buffer buffer_3s;
	struct AvgBearing_F32_20ms_Buffer buffer_30s;
	struct AvgBearing_F32_20ms_Buffer buffer_10m;

	F32 X_100ms[AVGBEAR_BUFLEN100MS];
	F32 X_1s[AVGBEAR_BUFLEN1S];
	F32 X_3s[AVGBEAR_BUFLEN3S];
	F32 X_30s[AVGBEAR_BUFLEN30S];
	F32 X_10m[AVGBEAR_BUFLEN10M];
	F32 Y_100ms[AVGBEAR_BUFLEN100MS];
	F32 Y_1s[AVGBEAR_BUFLEN1S];
	F32 Y_3s[AVGBEAR_BUFLEN3S];
	F32 Y_30s[AVGBEAR_BUFLEN30S];
	F32 Y_10m[AVGBEAR_BUFLEN10M];
	
	U32  time;
};


F32 GetAvgBearing_100ms(struct AvgBearing_F32_20ms_Struct*);
F32 GetAvgBearing_1s(struct AvgBearing_F32_20ms_Struct*);
F32 GetAvgBearing_3s(struct AvgBearing_F32_20ms_Struct*);
F32 GetAvgBearing_30s(struct AvgBearing_F32_20ms_Struct*);
F32 GetAvgBearing_10m(struct AvgBearing_F32_20ms_Struct*);
void PresetAvgBearingBuffer(struct AvgBearing_F32_20ms_Struct*, F32 bearing);
void ClearAvgBearingBuffer(struct AvgBearing_F32_20ms_Struct*);

// average value pointers(*avg100ms, *avg1s, *avg3s, *avg30s, *avg10m) can be set to NULL if not required
void UpdateAvgBearing(struct AvgBearing_F32_20ms_Struct*, F32 bearing, F32* avg100ms, F32* avg1s, F32* avg3s, F32* avg30s, F32* avg10m);

void InitializeAvgBearing(struct AvgBearing_F32_20ms_Struct*);

#endif
