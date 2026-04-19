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
#include <Aver_Bearing.h>

#define PI (3.14159265359f)


void PresetAvgBearingBuffer(struct AvgBearing_F32_20ms_Struct* avgBearingS, F32 newValue)
{
	F32 newValue_X = cos(newValue / 180.f * PI);
	F32 newValue_Y = sin(newValue / 180.f * PI);
	int i;

	if (newValue >= 360) { newValue -= ((int)newValue / 360) * 360; }
	else if (newValue < 0) { newValue += ((int)newValue / 360) * 360; }

	for (i = 0; i < AVGBEAR_BUFLEN100MS; i++)
	{
		avgBearingS->buffer_100ms.data_X[i] = newValue_X;
		avgBearingS->buffer_100ms.data_Y[i] = newValue_Y;
	}

	for (i = 0; i < AVGBEAR_BUFLEN1S; i++)
	{
		avgBearingS->buffer_1s.data_X[i] = newValue_X;
		avgBearingS->buffer_1s.data_Y[i] = newValue_Y;
	}

	for (i = 0; i < AVGBEAR_BUFLEN3S; i++)
	{
		avgBearingS->buffer_3s.data_X[i] = newValue_X;
		avgBearingS->buffer_3s.data_Y[i] = newValue_Y;
	}

	for (i = 0; i < AVGBEAR_BUFLEN30S; i++)
	{
		avgBearingS->buffer_30s.data_X[i] = newValue_X;
		avgBearingS->buffer_30s.data_Y[i] = newValue_Y;
	}

	for (i = 0; i < AVGBEAR_BUFLEN10M; i++)
	{
		avgBearingS->buffer_10m.data_X[i] = newValue_X;
		avgBearingS->buffer_10m.data_Y[i] = newValue_Y;
	}

	avgBearingS->buffer_100ms.index = 0;
	avgBearingS->buffer_1s.index = 0;
	avgBearingS->buffer_3s.index = 0;
	avgBearingS->buffer_30s.index = 0;
	avgBearingS->buffer_10m.index = 0;

	avgBearingS->buffer_100ms.avgResult_X = newValue_X;
	avgBearingS->buffer_100ms.avgResult_Y = newValue_Y;
	avgBearingS->buffer_1s.avgResult_X = newValue_X;
	avgBearingS->buffer_1s.avgResult_Y = newValue_Y;
	avgBearingS->buffer_3s.avgResult_X = newValue_X;
	avgBearingS->buffer_3s.avgResult_Y = newValue_Y;
	avgBearingS->buffer_30s.avgResult_X = newValue_X;
	avgBearingS->buffer_30s.avgResult_Y = newValue_Y;
	avgBearingS->buffer_10m.avgResult_X = newValue_X;
	avgBearingS->buffer_10m.avgResult_Y = newValue_Y;

	avgBearingS->buffer_100ms.sum_X = newValue_X * AVGBEAR_BUFLEN100MS;
	avgBearingS->buffer_100ms.sum_Y = newValue_Y * AVGBEAR_BUFLEN100MS;
	avgBearingS->buffer_1s.sum_X = newValue_X * AVGBEAR_BUFLEN1S;
	avgBearingS->buffer_1s.sum_Y = newValue_Y * AVGBEAR_BUFLEN1S;
	avgBearingS->buffer_3s.sum_X = newValue_X * AVGBEAR_BUFLEN3S;
	avgBearingS->buffer_3s.sum_Y = newValue_Y * AVGBEAR_BUFLEN3S;
	avgBearingS->buffer_30s.sum_X = newValue_X * AVGBEAR_BUFLEN30S;
	avgBearingS->buffer_30s.sum_Y = newValue_Y * AVGBEAR_BUFLEN30S;
	avgBearingS->buffer_10m.sum_X = newValue_X * AVGBEAR_BUFLEN10M;
	avgBearingS->buffer_10m.sum_Y = newValue_Y * AVGBEAR_BUFLEN10M;

	avgBearingS->time = 0;
}

void ClearAvgBearingBuffer(struct AvgBearing_F32_20ms_Struct* avgBearingS)
{
	PresetAvgBearingBuffer(avgBearingS, 0);
}

void InitializeAvgBearing(struct AvgBearing_F32_20ms_Struct* avgBearingS)
{
	avgBearingS->buffer_100ms.data_X = &avgBearingS->X_100ms;
	avgBearingS->buffer_100ms.data_Y = &avgBearingS->Y_100ms;
	avgBearingS->buffer_1s.data_X = &avgBearingS->X_1s;
	avgBearingS->buffer_1s.data_Y = &avgBearingS->Y_1s;
	avgBearingS->buffer_3s.data_X = &avgBearingS->X_3s;
	avgBearingS->buffer_3s.data_Y = &avgBearingS->Y_3s;
	avgBearingS->buffer_30s.data_X = &avgBearingS->X_30s;
	avgBearingS->buffer_30s.data_Y = &avgBearingS->Y_30s;
	avgBearingS->buffer_10m.data_X = &avgBearingS->X_10m;
	avgBearingS->buffer_10m.data_Y = &avgBearingS->Y_10m;

	avgBearingS->buffer_100ms.dataCount = AVGBEAR_BUFLEN100MS;
	avgBearingS->buffer_1s.dataCount = AVGBEAR_BUFLEN1S;
	avgBearingS->buffer_3s.dataCount = AVGBEAR_BUFLEN3S;
	avgBearingS->buffer_30s.dataCount = AVGBEAR_BUFLEN30S;
	avgBearingS->buffer_10m.dataCount = AVGBEAR_BUFLEN10M;
	
	PresetAvgBearingBuffer(avgBearingS, 0);

	avgBearingS->Initialized = 1;
}

F32 GetAvgBearing_100ms(struct AvgBearing_F32_20ms_Struct* avgBearingS)
{
	return avgBearingS->buffer_100ms.avgBearing;
}

F32 GetAvgBearing_1s(struct AvgBearing_F32_20ms_Struct* avgBearingS)
{
	return avgBearingS->buffer_1s.avgBearing;
}

F32 GetAvgBearing_3s(struct AvgBearing_F32_20ms_Struct* avgBearingS)
{
	return avgBearingS->buffer_3s.avgBearing;
}

F32 GetAvgBearing_30s(struct AvgBearing_F32_20ms_Struct* avgBearingS)
{
	return avgBearingS->buffer_30s.avgBearing;
}

F32 GetAvgBearing_10m(struct AvgBearing_F32_20ms_Struct* avgBearingS)
{
	return avgBearingS->buffer_10m.avgBearing;
}


static void AvgBearing_UpdateF32Buffer(struct AvgBearing_F32_20ms_Buffer* Buffer, F32 newValue_X, F32 newValue_Y)
{
	Buffer->sum_X -= Buffer->data_X[Buffer->index];
	Buffer->sum_Y -= Buffer->data_Y[Buffer->index];
	Buffer->data_X[Buffer->index] = newValue_X;
	Buffer->data_Y[Buffer->index] = newValue_Y;
	Buffer->sum_X += newValue_X;
	Buffer->sum_Y += newValue_Y;
	Buffer->index++;
	if (Buffer->index >= Buffer->dataCount) Buffer->index = 0;

	Buffer->avgResult_X = Buffer->sum_X / Buffer->dataCount;
	Buffer->avgResult_Y = Buffer->sum_Y / Buffer->dataCount;
}



static F32 CalcAvgBearing_100ms(struct AvgBearing_F32_20ms_Struct* avgBearingS)
{
	avgBearingS->buffer_100ms.avgBearing = atan2(avgBearingS->buffer_100ms.avgResult_Y, avgBearingS->buffer_100ms.avgResult_X) * 180.f / PI;
	if (avgBearingS->buffer_100ms.avgBearing < 0) avgBearingS->buffer_100ms.avgBearing += 360.f;
	return avgBearingS->buffer_100ms.avgBearing;
}

static F32 CalcAvgBearing_1s(struct AvgBearing_F32_20ms_Struct* avgBearingS)
{
	avgBearingS->buffer_1s.avgBearing = atan2(avgBearingS->buffer_1s.avgResult_Y, avgBearingS->buffer_1s.avgResult_X) * 180.f / PI;
	if (avgBearingS->buffer_1s.avgBearing < 0) avgBearingS->buffer_1s.avgBearing += 360.f;
	return avgBearingS->buffer_1s.avgBearing;
}

static F32 CalcAvgBearing_3s(struct AvgBearing_F32_20ms_Struct* avgBearingS)
{
	avgBearingS->buffer_3s.avgBearing = atan2(avgBearingS->buffer_3s.avgResult_Y, avgBearingS->buffer_3s.avgResult_X) * 180.f / PI;
	if (avgBearingS->buffer_3s.avgBearing < 0) avgBearingS->buffer_3s.avgBearing += 360.f;
	return avgBearingS->buffer_3s.avgBearing;
}

static F32 CalcAvgBearing_30s(struct AvgBearing_F32_20ms_Struct* avgBearingS)
{
	avgBearingS->buffer_30s.avgBearing = atan2(avgBearingS->buffer_30s.avgResult_Y, avgBearingS->buffer_30s.avgResult_X) * 180.f / PI;
	if (avgBearingS->buffer_30s.avgBearing < 0) avgBearingS->buffer_30s.avgBearing += 360.f;
	return avgBearingS->buffer_30s.avgBearing;
}

static F32 CalcAvgBearing_10m(struct AvgBearing_F32_20ms_Struct* avgBearingS)
{
	avgBearingS->buffer_10m.avgBearing = atan2(avgBearingS->buffer_10m.avgResult_Y, avgBearingS->buffer_10m.avgResult_X) * 180.f / PI;
	if (avgBearingS->buffer_10m.avgBearing < 0) avgBearingS->buffer_10m.avgBearing += 360.f;
	return avgBearingS->buffer_10m.avgBearing;
}



// must be called in 20ms task
void UpdateAvgBearing(struct AvgBearing_F32_20ms_Struct* avgBearingS, F32 newValue, F32* avg100ms, F32* avg1s, F32* avg3s, F32* avg30s, F32* avg10m)
{
	if (avgBearingS->Initialized != 1) return;

	// convert values negative or greater than 360 into 0-360 range
	if (newValue >= 360) { newValue -= ((int)newValue / 360) * 360; }
	else if (newValue < 0) { newValue += ((int)-newValue / 360) * 360 + 360; }

	AvgBearing_UpdateF32Buffer(&avgBearingS->buffer_100ms, cos(newValue / 180.f * PI), sin(newValue / 180.f * PI));
	avgBearingS->time += 20;		// add 20ms to time value

	// help to shift 20ms task load by shifting calculation timing by 20ms for each following CalCAvgBearing_...s()
	if (avgBearingS->time % 100 == 0)
	{
		CalcAvgBearing_100ms(avgBearingS);
	}
	else if (avgBearingS->time % 100 == 20)
	{
		AvgBearing_UpdateF32Buffer(&avgBearingS->buffer_1s, avgBearingS->buffer_100ms.avgResult_X, avgBearingS->buffer_100ms.avgResult_Y);
		CalcAvgBearing_1s(avgBearingS);
	}
	else if (avgBearingS->time % 100 == 40)
	{
		AvgBearing_UpdateF32Buffer(&avgBearingS->buffer_3s, avgBearingS->buffer_100ms.avgResult_X, avgBearingS->buffer_100ms.avgResult_Y);
		CalcAvgBearing_3s(avgBearingS);
	}
	else if (avgBearingS->time % 1000 == 60)
	{
		AvgBearing_UpdateF32Buffer(&avgBearingS->buffer_30s, avgBearingS->buffer_3s.avgResult_X, avgBearingS->buffer_3s.avgResult_Y);
		CalcAvgBearing_30s(avgBearingS);
	}
	else if (avgBearingS->time > 30000 && avgBearingS->time % 30000 == 80)
	{
		AvgBearing_UpdateF32Buffer(&avgBearingS->buffer_10m, avgBearingS->buffer_30s.avgResult_X, avgBearingS->buffer_30s.avgResult_Y);
		CalcAvgBearing_10m(avgBearingS);
		avgBearingS->time = 80;
	}

	if (avg100ms != NULL) *avg100ms = avgBearingS->buffer_100ms.avgBearing;
	if (avg1s != NULL) *avg1s = avgBearingS->buffer_1s.avgBearing;
	if (avg3s != NULL) *avg3s = avgBearingS->buffer_3s.avgBearing;
	if (avg30s != NULL) *avg30s = avgBearingS->buffer_30s.avgBearing;
	if (avg10m != NULL) *avg10m = avgBearingS->buffer_10m.avgBearing;
}