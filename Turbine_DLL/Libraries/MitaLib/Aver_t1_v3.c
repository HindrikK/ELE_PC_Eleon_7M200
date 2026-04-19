#include <Aver_t1_v3.h>



//*******************************************************************************
// S16
//*******************************************************************************

void ClearS16Buffer(struct S16Buffer* Buffer)
{
	int i;

	for (i = 0; i < BufLen20ms; i++)
	{
		Buffer->_20ms[i] = 0;
	}

	for (i = 0; i < BufLen100ms; i++)
	{
		Buffer->_100ms[i] = 0;
	}

	for (i = 0; i < BufLen1s; i++)
	{
		Buffer->_1s[i] = 0;
	}

	for (i = 0; i < BufLen3s; i++)
	{
		Buffer->_3s[i] = 0;
	}

	for (i = 0; i < BufLen30s; i++)
	{
		Buffer->_30s[i] = 0;
	}

	Buffer->time = 0;
}


static void UpdateS16Buffer_100ms(struct S16Buffer* Buffer, S16 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen100ms - 1; i > 0; i--)
	{
		Buffer->_100ms[i] = Buffer->_100ms[i - 1];
	}
	Buffer->_100ms[0] = newValue;
}

static void UpdateS16Buffer_1s(struct S16Buffer* Buffer, S16 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen1s - 1; i > 0; i--)
	{
		Buffer->_1s[i] = Buffer->_1s[i - 1];
	}
	Buffer->_1s[0] = newValue;
}

static void UpdateS16Buffer_3s(struct S16Buffer* Buffer, S16 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen3s - 1; i > 0; i--)
	{
		Buffer->_3s[i] = Buffer->_3s[i - 1];
	}
	Buffer->_3s[0] = newValue;
}

static void UpdateS16Buffer_30s(struct S16Buffer* Buffer, S16 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen30s - 1; i > 0; i--)
	{
		Buffer->_30s[i] = Buffer->_30s[i - 1];
	}
	Buffer->_30s[0] = newValue;
}




S16 GetS16_100msAverage(const struct S16Buffer* Buffer)
{
	S32 Sum = 0;

	int i;
	for (i = 0; i < BufLen20ms; i++)
	{
		Sum += Buffer->_20ms[i];
	}
	return Sum / BufLen20ms;
}

S16 GetS16_1sAverage(const struct S16Buffer* Buffer)
{
	S32 Sum = 0;

	int i;
	for (i = 0; i < BufLen100ms; i++)
	{
		Sum += Buffer->_100ms[i];
	}
	return Sum / BufLen100ms;
}

S16 GetS16_3sAverage(const struct S16Buffer* Buffer)
{
	S32 Sum = 0;

	int i;
	for (i = 0; i < BufLen1s; i++)
	{
		Sum += Buffer->_1s[i];
	}
	return Sum / BufLen1s;
}

S16 GetS16_30sAverage(const struct S16Buffer* Buffer)
{
	S32 Sum = 0;

	int i;
	for (i = 0; i < BufLen3s; i++)
	{
		Sum += Buffer->_3s[i];
	}
	return Sum / BufLen3s;
}

S16 GetS16_10mAverage(const struct S16Buffer* Buffer)
{
	S32 Sum = 0;

	int i;
	for (i = 0; i < BufLen30s; i++)
	{
		Sum += Buffer->_30s[i];
	}
	return Sum / BufLen30s;
}



// must be called in 20ms task
U8 UpdateS16Buffer(struct S16Buffer* Buffer, S16 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen20ms - 1; i > 0; i--)
	{
		Buffer->_20ms[i] = Buffer->_20ms[i - 1];
	}
	Buffer->_20ms[0] = newValue;
	Buffer->time += 20;		// add 20ms to time value

	if (Buffer->time % 100 == 0)
	{
		UpdateS16Buffer_100ms(Buffer, GetS16_100msAverage(Buffer));
		
		if (Buffer->time % 1000 == 0)
		{
			S16 avg1s = GetS16_1sAverage(Buffer);
			UpdateS16Buffer_1s(Buffer, avg1s);
			UpdateS16Buffer_3s(Buffer, avg1s);

			if (Buffer->time % 30000 == 0)
			{
				UpdateS16Buffer_30s(Buffer, GetS16_30sAverage(Buffer));
				Buffer->time = 20;
			}
		}
		else
		{
			UpdateS16Buffer_1s(Buffer, GetS16_1sAverage(Buffer));
		}
	}
	return 0;
}

//*******************************************************************************




//*******************************************************************************
// U16
//*******************************************************************************

void ClearU16Buffer(struct U16Buffer* Buffer)
{
	int i;

	for (i = 0; i < BufLen20ms; i++)
	{
		Buffer->_20ms[i] = 0;
	}

	for (i = 0; i < BufLen100ms; i++)
	{
		Buffer->_100ms[i] = 0;
	}

	for (i = 0; i < BufLen1s; i++)
	{
		Buffer->_1s[i] = 0;
	}

	for (i = 0; i < BufLen3s; i++)
	{
		Buffer->_3s[i] = 0;
	}

	for (i = 0; i < BufLen30s; i++)
	{
		Buffer->_30s[i] = 0;
	}

	Buffer->time = 0;
}


static void UpdateU16Buffer_100ms(struct U16Buffer* Buffer, U16 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen100ms - 1; i > 0; i--)
	{
		Buffer->_100ms[i] = Buffer->_100ms[i - 1];
	}
	Buffer->_100ms[0] = newValue;
}

static void UpdateU16Buffer_1s(struct U16Buffer* Buffer, U16 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen1s - 1; i > 0; i--)
	{
		Buffer->_1s[i] = Buffer->_1s[i - 1];
	}
	Buffer->_1s[0] = newValue;
}

static void UpdateU16Buffer_3s(struct U16Buffer* Buffer, U16 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen3s - 1; i > 0; i--)
	{
		Buffer->_3s[i] = Buffer->_3s[i - 1];
	}
	Buffer->_3s[0] = newValue;
}

static void UpdateU16Buffer_30s(struct U16Buffer* Buffer, U16 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen30s - 1; i > 0; i--)
	{
		Buffer->_30s[i] = Buffer->_30s[i - 1];
	}
	Buffer->_30s[0] = newValue;
}




U16 GetU16_100msAverage(const struct U16Buffer* Buffer)
{
	U32 Sum = 0;

	int i;
	for (i = 0; i < BufLen20ms; i++)
	{
		Sum += Buffer->_20ms[i];
	}
	return Sum / BufLen20ms;
}

U16 GetU16_1sAverage(const struct U16Buffer* Buffer)
{
	U32 Sum = 0;

	int i;
	for (i = 0; i < BufLen100ms; i++)
	{
		Sum += Buffer->_100ms[i];
	}
	return Sum / BufLen100ms;
}

U16 GetU16_3sAverage(const struct U16Buffer* Buffer)
{
	U32 Sum = 0;

	int i;
	for (i = 0; i < BufLen1s; i++)
	{
		Sum += Buffer->_1s[i];
	}
	return Sum / BufLen1s;
}

U16 GetU16_30sAverage(const struct U16Buffer* Buffer)
{
	U32 Sum = 0;

	int i;
	for (i = 0; i < BufLen3s; i++)
	{
		Sum += Buffer->_3s[i];
	}
	return Sum / BufLen3s;
}

U16 GetU16_10mAverage(const struct U16Buffer* Buffer)
{
	U32 Sum = 0;

	int i;
	for (i = 0; i < BufLen30s; i++)
	{
		Sum += Buffer->_30s[i];
	}
	return Sum / BufLen30s;
}



// must be called in 20ms task
U8 UpdateU16Buffer(struct U16Buffer* Buffer, U16 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen20ms - 1; i > 0; i--)
	{
		Buffer->_20ms[i] = Buffer->_20ms[i - 1];
	}
	Buffer->_20ms[0] = newValue;
	Buffer->time += 20;		// add 20ms to time value

	if (Buffer->time % 100 == 0)
	{
		UpdateU16Buffer_100ms(Buffer, GetU16_100msAverage(Buffer));
		
		if (Buffer->time % 1000 == 0)
		{
			U16 avg1s = GetU16_1sAverage(Buffer);
			UpdateU16Buffer_1s(Buffer, avg1s);
			UpdateU16Buffer_3s(Buffer, avg1s);

			if (Buffer->time % 30000 == 0)
			{
				UpdateU16Buffer_30s(Buffer, GetU16_30sAverage(Buffer));
				Buffer->time = 20;
			}
		}
		else
		{
			UpdateU16Buffer_1s(Buffer, GetU16_1sAverage(Buffer));
		}
	}
	return 0;
}

//*******************************************************************************




//*******************************************************************************
// S32
//*******************************************************************************

void ClearS32Buffer(struct S32Buffer* Buffer)
{
	int i;

	for (i = 0; i < BufLen20ms; i++)
	{
		Buffer->_20ms[i] = 0;
	}

	for (i = 0; i < BufLen100ms; i++)
	{
		Buffer->_100ms[i] = 0;
	}

	for (i = 0; i < BufLen1s; i++)
	{
		Buffer->_1s[i] = 0;
	}

	for (i = 0; i < BufLen3s; i++)
	{
		Buffer->_3s[i] = 0;
	}

	for (i = 0; i < BufLen30s; i++)
	{
		Buffer->_30s[i] = 0;
	}

	Buffer->time = 0;
}


static void UpdateS32Buffer_100ms(struct S32Buffer* Buffer, S32 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen100ms - 1; i > 0; i--)
	{
		Buffer->_100ms[i] = Buffer->_100ms[i - 1];
	}
	Buffer->_100ms[0] = newValue;
}

static void UpdateS32Buffer_1s(struct S32Buffer* Buffer, S32 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen1s - 1; i > 0; i--)
	{
		Buffer->_1s[i] = Buffer->_1s[i - 1];
	}
	Buffer->_1s[0] = newValue;
}

static void UpdateS32Buffer_3s(struct S32Buffer* Buffer, S32 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen3s - 1; i > 0; i--)
	{
		Buffer->_3s[i] = Buffer->_3s[i - 1];
	}
	Buffer->_3s[0] = newValue;
}

static void UpdateS32Buffer_30s(struct S32Buffer* Buffer, S32 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen30s - 1; i > 0; i--)
	{
		Buffer->_30s[i] = Buffer->_30s[i - 1];
	}
	Buffer->_30s[0] = newValue;
}




S32 GetS32_100msAverage(const struct S32Buffer* Buffer)
{
	S64 Sum = 0;

	int i;
	for (i = 0; i < BufLen20ms; i++)
	{
		Sum += Buffer->_20ms[i];
	}
	return Sum / BufLen20ms;
}

S32 GetS32_1sAverage(const struct S32Buffer* Buffer)
{
	S64 Sum = 0;

	int i;
	for (i = 0; i < BufLen100ms; i++)
	{
		Sum += Buffer->_100ms[i];
	}
	return Sum / BufLen100ms;
}

S32 GetS32_3sAverage(const struct S32Buffer* Buffer)
{
	S64 Sum = 0;

	int i;
	for (i = 0; i < BufLen1s; i++)
	{
		Sum += Buffer->_1s[i];
	}
	return Sum / BufLen1s;
}

S32 GetS32_30sAverage(const struct S32Buffer* Buffer)
{
	S64 Sum = 0;

	int i;
	for (i = 0; i < BufLen3s; i++)
	{
		Sum += Buffer->_3s[i];
	}
	return Sum / BufLen3s;
}

S32 GetS32_10mAverage(const struct S32Buffer* Buffer)
{
	S64 Sum = 0;

	int i;
	for (i = 0; i < BufLen30s; i++)
	{
		Sum += Buffer->_30s[i];
	}
	return Sum / BufLen30s;
}



// must be called in 20ms task
U8 UpdateS32Buffer(struct S32Buffer* Buffer, S32 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen20ms - 1; i > 0; i--)
	{
		Buffer->_20ms[i] = Buffer->_20ms[i - 1];
	}
	Buffer->_20ms[0] = newValue;
	Buffer->time += 20;		// add 20ms to time value

	if (Buffer->time % 100 == 0)
	{
		UpdateS32Buffer_100ms(Buffer, GetS32_100msAverage(Buffer));

		if (Buffer->time % 1000 == 0)
		{
			S32 avg1s = GetS32_1sAverage(Buffer);
			UpdateS32Buffer_1s(Buffer, avg1s);
			UpdateS32Buffer_3s(Buffer, avg1s);

			if (Buffer->time % 30000 == 0)
			{
				UpdateS32Buffer_30s(Buffer, GetS32_30sAverage(Buffer));
				Buffer->time = 0;
			}
		}
		else
		{
			UpdateS32Buffer_1s(Buffer, GetS32_1sAverage(Buffer));
		}
	}
	return 0;
}

//*******************************************************************************




//*******************************************************************************
// U32
//*******************************************************************************

void ClearU32Buffer(struct U32Buffer* Buffer)
{
	int i;

	for (i = 0; i < BufLen20ms; i++)
	{
		Buffer->_20ms[i] = 0;
	}

	for (i = 0; i < BufLen100ms; i++)
	{
		Buffer->_100ms[i] = 0;
	}

	for (i = 0; i < BufLen1s; i++)
	{
		Buffer->_1s[i] = 0;
	}

	for (i = 0; i < BufLen3s; i++)
	{
		Buffer->_3s[i] = 0;
	}

	for (i = 0; i < BufLen30s; i++)
	{
		Buffer->_30s[i] = 0;
	}

	Buffer->time = 0;
}


static void UpdateU32Buffer_100ms(struct U32Buffer* Buffer, U32 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen100ms - 1; i > 0; i--)
	{
		Buffer->_100ms[i] = Buffer->_100ms[i - 1];
	}
	Buffer->_100ms[0] = newValue;
}

static void UpdateU32Buffer_1s(struct U32Buffer* Buffer, U32 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen1s - 1; i > 0; i--)
	{
		Buffer->_1s[i] = Buffer->_1s[i - 1];
	}
	Buffer->_1s[0] = newValue;
}

static void UpdateU32Buffer_3s(struct U32Buffer* Buffer, U32 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen3s - 1; i > 0; i--)
	{
		Buffer->_3s[i] = Buffer->_3s[i - 1];
	}
	Buffer->_3s[0] = newValue;
}

static void UpdateU32Buffer_30s(struct U32Buffer* Buffer, U32 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen30s - 1; i > 0; i--)
	{
		Buffer->_30s[i] = Buffer->_30s[i - 1];
	}
	Buffer->_30s[0] = newValue;
}




U32 GetU32_100msAverage(const struct U32Buffer* Buffer)
{
	U64 Sum = 0;

	int i;
	for (i = 0; i < BufLen20ms; i++)
	{
		Sum += Buffer->_20ms[i];
	}
	return Sum / BufLen20ms;
}

U32 GetU32_1sAverage(const struct U32Buffer* Buffer)
{
	U64 Sum = 0;

	int i;
	for (i = 0; i < BufLen100ms; i++)
	{
		Sum += Buffer->_100ms[i];
	}
	return Sum / BufLen100ms;
}

U32 GetU32_3sAverage(const struct U32Buffer* Buffer)
{
	U64 Sum = 0;

	int i;
	for (i = 0; i < BufLen1s; i++)
	{
		Sum += Buffer->_1s[i];
	}
	return Sum / BufLen1s;
}

U32 GetU32_30sAverage(const struct U32Buffer* Buffer)
{
	U64 Sum = 0;

	int i;
	for (i = 0; i < BufLen3s; i++)
	{
		Sum += Buffer->_3s[i];
	}
	return Sum / BufLen3s;
}

U32 GetU32_10mAverage(const struct U32Buffer* Buffer)
{
	U64 Sum = 0;

	int i;
	for (i = 0; i < BufLen30s; i++)
	{
		Sum += Buffer->_30s[i];
	}
	return Sum / BufLen30s;
}



// must be called in 20ms task
U8 UpdateU32Buffer(struct U32Buffer* Buffer, U32 newValue)
{
	// do the shifting
	int i;
	for (i = BufLen20ms - 1; i > 0; i--)
	{
		Buffer->_20ms[i] = Buffer->_20ms[i - 1];
	}
	Buffer->_20ms[0] = newValue;
	Buffer->time += 20;		// add 20ms to time value

	if (Buffer->time % 100 == 0)
	{
		UpdateU32Buffer_100ms(Buffer, GetU32_100msAverage(Buffer));

		if (Buffer->time % 1000 == 0)
		{
			U32 avg1s = GetU32_1sAverage(Buffer);
			UpdateU32Buffer_1s(Buffer, avg1s);
			UpdateU32Buffer_3s(Buffer, avg1s);

			if (Buffer->time % 30000 == 0)
			{
				UpdateU32Buffer_30s(Buffer, GetU32_30sAverage(Buffer));
				Buffer->time = 0;
			}
		}
		else
		{
			UpdateU32Buffer_1s(Buffer, GetU32_1sAverage(Buffer));
		}
	}
	return 0;
}

//*******************************************************************************
