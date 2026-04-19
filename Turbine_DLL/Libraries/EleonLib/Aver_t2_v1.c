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
#include <Aver_t2_v1.h>


/*
//*******************************************************************************
// S16
//*******************************************************************************

// must be called in 20ms task
public void Avg_UpdateS16Buffer(S16Buffer* Buffer, S16 newValue)
{
	// do the shifting
	int i = Avg_BufLen20ms - 1;
	for (i; i > 0; i--)
	{
		Buffer->_20ms[i] = Buffer->_20ms[i - 1];
	}
	Buffer->_20ms[0] = newValue;
	Buffer->time += 20;		// add 20ms to time value

	if (Buffer->time % 100 == 0)
	{
		UpdateS16Buffer_100ms(Buffer, Avg_GetS16_100msAverage());

		if (Buffer->time % 1000 == 0)
		{
			UpdateS16Buffer_1s(Buffer, Avg_GetS16_1sAverage());

			if (Buffer->time % 3000 == 0)
			{
				UpdateS16Buffer_3s(Buffer, Avg_GetS16_3sAverage());

				if (Buffer->time % 30000 == 0)
				{
					UpdateS16Buffer_30s(Buffer, Avg_GetS16_30sAverage());
					Buffer->time = 0;
				}
			}
		}
	}
}


public void Avg_ClearS16Buffer(S16Buffer* Buffer)
{
	int i = 0;

	for (i; i < Avg_BufLen20ms; i++)
	{
		Buffer->_20ms[i] = 0;
	}

	i = 0;
	for (i; i < Avg_BufLen100ms; i++)
	{
		Buffer->_100ms[i] = 0;
	}

	i = 0;
	for (i; i < Avg_BufLen1s; i++)
	{
		Buffer->_1s[i] = 0;
	}

	i = 0;
	for (i; i < Avg_BufLen3s; i++)
	{
		Buffer->_3s[i] = 0;
	}

	i = 0;
	for (i; i < Avg_BufLen30s; i++)
	{
		Buffer->_30s[i] = 0;
	}

	Buffer->time = 0;
}


private void Avg_UpdateS16Buffer_100ms(S16Buffer* Buffer, S16 newValue)
{
	// do the shifting
	int i = Avg_BufLen100ms - 1;
	for (i; i > 0; i--)
	{
		Buffer->_100ms[i] = Buffer->_100ms[i - 1];
	}
	Buffer->_100ms[0] = newValue;
}

public S16 Avg_GetS16_100msAverage(S16Buffer* Buffer)
{
	S32 Sum = 0;

	int i = 0;
	for (i; i < Avg_BufLen20ms; i++)
	{
		Sum += Buffer->_20ms[i];
	}
	return Sum / Avg_BufLen20ms;
}

public S16 Avg_GetS16_1sAverage(S16Buffer* Buffer)
{
	S32 Sum = 0;

	int i = 0;
	for (i; i < Avg_BufLen100ms; i++)
	{
		Sum += Buffer->_100ms[i];
	}
	return Sum / Avg_BufLen100ms;
}

public S16 Avg_GetS16_3sAverage(S16Buffer* Buffer)
{
	S32 Sum = 0;

	int i = 0;
	for (i; i < Avg_BufLen1s; i++)
	{
		Sum += Buffer->_1s[i];
	}
	return Sum / Avg_BufLen1s;
}

public S16 Avg_GetS16_30sAverage(S16Buffer* Buffer)
{
	S32 Sum = 0;

	int i = 0;
	for (i; i < Avg_BufLen3s; i++)
	{
		Sum += Buffer->_3s[i];
	}
	return Sum / Avg_BufLen3s;
}

public S16 Avg_GetS16_10minAverage(S16Buffer* Buffer)
{
	S32 Sum = 0;

	int i = 0;
	for (i; i < Avg_BufLen30s; i++)
	{
		Sum += Buffer->_30s[i];
	}
	return Sum / Avg_BufLen30s;
}

//*******************************************************************************




//*******************************************************************************
// U16
//*******************************************************************************

// must be called in 20ms task
public void Avg_UpdateU16Buffer(U16Buffer* Buffer, U16 newValue)
{
	// do the shifting
	int i = Avg_BufLen20ms - 1;
	for (i; i > 0; i--)
	{
		Buffer->_20ms[i] = Buffer->_20ms[i - 1];
	}
	Buffer->_20ms[0] = newValue;
	Buffer->time += 20;		// add 20ms to time value

	if (Buffer->time % 100 == 0)
	{
		Avg_UpdateU16Buffer_100ms(Buffer, GetU16_100msAverage());

		if (Buffer->time % 1000 == 0)
		{
			Avg_UpdateU16Buffer_1s(Buffer, GetU16_1sAverage());

			if (Buffer->time % 3000 == 0)
			{
				Avg_UpdateU16Buffer_3s(Buffer, GetU16_3sAverage());

				if (Buffer->time % 30000 == 0)
				{
					Avg_UpdateU16Buffer_30s(Buffer, GetU16_30sAverage());
					Buffer->time = 0;
				}
			}
		}
	}
}


public void Avg_ClearU16Buffer(U16Buffer* Buffer)
{
	int i = 0;

	for (i; i < Avg_BufLen20ms; i++)
	{
		Buffer->_20ms[i] = 0;
	}

	i = 0;
	for (i; i < Avg_BufLen100ms; i++)
	{
		Buffer->_100ms[i] = 0;
	}

	i = 0;
	for (i; i < Avg_BufLen1s; i++)
	{
		Buffer->_1s[i] = 0;
	}

	i = 0;
	for (i; i < Avg_BufLen3s; i++)
	{
		Buffer->_3s[i] = 0;
	}

	i = 0;
	for (i; i < Avg_BufLen30s; i++)
	{
		Buffer->_30s[i] = 0;
	}

	Buffer->time = 0;
}


private void Avg_UpdateU16Buffer_100ms(U16Buffer* Buffer, U16 newValue)
{
	// do the shifting
	int i = Avg_BufLen100ms - 1;
	for (i; i > 0; i--)
	{
		Buffer->_100ms[i] = Buffer->_100ms[i - 1];
	}
	Buffer->_100ms[0] = newValue;
}

public U16 Avg_GetU16_100msAverage(U16Buffer* Buffer)
{
	U32 Sum = 0;

	int i = 0;
	for (i; i < Avg_BufLen20ms; i++)
	{
		Sum += Buffer->_20ms[i];
	}
	return Sum / Avg_BufLen20ms;
}

public U16 Avg_GetU16_1sAverage(U16Buffer* Buffer)
{
	U32 Sum = 0;

	int i = 0;
	for (i; i < Avg_BufLen100ms; i++)
	{
		Sum += Buffer->_100ms[i];
	}
	return Sum / Avg_BufLen100ms;
}

public U16 Avg_GetU16_3sAverage(U16Buffer* Buffer)
{
	U32 Sum = 0;

	int i = 0;
	for (i; i < Avg_BufLen1s; i++)
	{
		Sum += Buffer->_1s[i];
	}
	return Sum / Avg_BufLen1s;
}

public U16 Avg_GetU16_30sAverage(U16Buffer* Buffer)
{
	U32 Sum = 0;

	int i = 0;
	for (i; i < Avg_BufLen3s; i++)
	{
		Sum += Buffer->_3s[i];
	}
	return Sum / Avg_BufLen3s;
}

public U16 Avg_GetU16_10minAverage(U16Buffer* Buffer)
{
	U32 Sum = 0;

	int i = 0;
	for (i; i < Avg_BufLen30s; i++)
	{
		Sum += Buffer->_30s[i];
	}
	return Sum / Avg_BufLen30s;
}

//*******************************************************************************
*/



//*******************************************************************************
// S32
//*******************************************************************************

void Avg_ClearS32Buffer(struct Avg_S32Buffer *Buffer)
{
	int i;

	for (i = 0; i < Avg_BufLen20ms; i++)
	{
		Buffer->_20ms[i] = 0;
	}

	for (i = 0; i < Avg_BufLen100ms; i++)
	{
		Buffer->_100ms[i] = 0;
	}

	for (i = 0; i < Avg_BufLen1s; i++)
	{
		Buffer->_1s[i] = 0;
	}

	for (i = 0; i < Avg_BufLen3s; i++)
	{
		Buffer->_3s[i] = 0;
	}

	for (i = 0; i < Avg_BufLen30s; i++)
	{
		Buffer->_30s[i] = 0;
	}

	Buffer->time = 0;
}


static void Avg_UpdateS32Buffer_100ms(struct Avg_S32Buffer *Buffer, S32 newValue)
{
	// do the shifting
	int i;
	for (i = Avg_BufLen100ms - 1; i > 0; i--)
	{
		Buffer->_100ms[i] = Buffer->_100ms[i - 1];
	}
	Buffer->_100ms[0] = newValue;
}

static void Avg_UpdateS32Buffer_1s(struct Avg_S32Buffer *Buffer, S32 newValue)
{
	// do the shifting
	int i;
	for (i = Avg_BufLen1s - 1; i > 0; i--)
	{
		Buffer->_1s[i] = Buffer->_1s[i - 1];
	}
	Buffer->_1s[0] = newValue;
}

static void Avg_UpdateS32Buffer_3s(struct Avg_S32Buffer *Buffer, S32 newValue)
{
	// do the shifting
	int i;
	for (i = Avg_BufLen3s - 1; i > 0; i--)
	{
		Buffer->_3s[i] = Buffer->_3s[i - 1];
	}
	Buffer->_3s[0] = newValue;
}

static void Avg_UpdateS32Buffer_30s(struct Avg_S32Buffer *Buffer, S32 newValue)
{
	// do the shifting
	int i;
	for (i = Avg_BufLen30s - 1; i > 0; i--)
	{
		Buffer->_30s[i] = Buffer->_30s[i - 1];
	}
	Buffer->_30s[0] = newValue;
}




S32 Avg_GetS32_100msAverage(const struct Avg_S32Buffer *Buffer)
{
	S64 Sum = 0;

	int i;
	for (i = 0; i < Avg_BufLen20ms; i++)
	{
		Sum += Buffer->_20ms[i];
	}
	return Sum / Avg_BufLen20ms;
}

S32 Avg_GetS32_1sAverage(const struct Avg_S32Buffer *Buffer)
{
	S64 Sum = 0;

	int i;
	for (i = 0; i < Avg_BufLen100ms; i++)
	{
		Sum += Buffer->_100ms[i];
	}
	return Sum / Avg_BufLen100ms;
}

S32 Avg_GetS32_3sAverage(const struct Avg_S32Buffer *Buffer)
{
	S64 Sum = 0;

	int i;
	for (i = 0; i < Avg_BufLen1s; i++)
	{
		Sum += Buffer->_1s[i];
	}
	return Sum / Avg_BufLen1s;
}

S32 Avg_GetS32_30sAverage(const struct Avg_S32Buffer *Buffer)
{
	S64 Sum = 0;

	int i;
	for (i = 0; i < Avg_BufLen3s; i++)
	{
		Sum += Buffer->_3s[i];
	}
	return Sum / Avg_BufLen3s;
}

S32 Avg_GetS32_10mAverage(const struct Avg_S32Buffer *Buffer)
{
	S64 Sum = 0;

	int i;
	for (i = 0; i < Avg_BufLen30s; i++)
	{
		Sum += Buffer->_30s[i];
	}
	return Sum / Avg_BufLen30s;
}



// must be called in 20ms task
void Avg_UpdateS32Buffer(struct Avg_S32Buffer *Buffer, S32 newValue)
{
	// do the shifting
	int i;
	for (i = Avg_BufLen20ms - 1; i > 0; i--)
	{
		Buffer->_20ms[i] = Buffer->_20ms[i - 1];
	}
	Buffer->_20ms[0] = newValue;
	Buffer->time += 20;		// add 20ms to time value

	if (Buffer->time % 100 == 0)
	{
		Avg_UpdateS32Buffer_100ms(Buffer, Avg_GetS32_100msAverage(Buffer));

		if (Buffer->time % 1000 == 0)
		{
			S32 avg1s = Avg_GetS32_1sAverage(Buffer);
         Avg_UpdateS32Buffer_1s(Buffer, avg1s);
         Avg_UpdateS32Buffer_3s(Buffer, avg1s);

			if (Buffer->time % 30000 == 0)
			{
				Avg_UpdateS32Buffer_30s(Buffer, Avg_GetS32_30sAverage(Buffer));
				Buffer->time = 0;
			}
		}
      else
      {
         Avg_UpdateS32Buffer_1s(Buffer, Avg_GetS32_1sAverage(Buffer));
      }
	}
}

//*******************************************************************************



/*
//*******************************************************************************
// U32
//*******************************************************************************

// must be called in 20ms task
public void Avg_UpdateU32Buffer(U32Buffer* Buffer, U32 newValue)
{
	// do the shifting
	int i = Avg_BufLen20ms - 1;
	for (i; i > 0; i--)
	{
		Buffer->_20ms[i] = Buffer->_20ms[i - 1];
	}
	Buffer->_20ms[0] = newValue;
	Buffer->time += 20;		// add 20ms to time value

	if (Buffer->time % 100 == 0)
	{
		UpdateU32Buffer_100ms(Buffer, Avg_GetU32_100msAverage());

		if (Buffer->time % 1000 == 0)
		{
			UpdateU32Buffer_1s(Buffer, Avg_GetU32_1sAverage());

			if (Buffer->time % 3000 == 0)
			{
				UpdateU32Buffer_3s(Buffer, Avg_GetU32_3sAverage());

				if (Buffer->time % 30000 == 0)
				{
					UpdateU32Buffer_30s(Buffer, Avg_GetU32_30sAverage());
					Buffer->time = 0;
				}
			}
		}
	}
}


public void Avg_ClearU32Buffer(U32Buffer* Buffer)
{
	int i = 0;

	for (i; i < Avg_BufLen20ms; i++)
	{
		Buffer->_20ms[i] = 0;
	}

	i = 0;
	for (i; i < Avg_BufLen100ms; i++)
	{
		Buffer->_100ms[i] = 0;
	}

	i = 0;
	for (i; i < Avg_BufLen1s; i++)
	{
		Buffer->_1s[i] = 0;
	}

	i = 0;
	for (i; i < Avg_BufLen3s; i++)
	{
		Buffer->_3s[i] = 0;
	}

	i = 0;
	for (i; i < Avg_BufLen30s; i++)
	{
		Buffer->_30s[i] = 0;
	}

	Buffer->time = 0;
}


private void Avg_UpdateU32Buffer_100ms(U32Buffer* Buffer, U32 newValue)
{
	// do the shifting
	int i = Avg_BufLen100ms - 1;
	for (i; i > 0; i--)
	{
		Buffer->_100ms[i] = Buffer->_100ms[i - 1];
	}
	Buffer->_100ms[0] = newValue;
}

public U32 Avg_GetU32_100msAverage(U32Buffer* Buffer)
{
	U64 Sum = 0;

	int i = 0;
	for (i; i < Avg_BufLen20ms; i++)
	{
		Sum += Buffer->_20ms[i];
	}
	return Sum / Avg_BufLen20ms;
}

public U32 Avg_GetU32_1sAverage(U32Buffer* Buffer)
{
	U64 Sum = 0;

	int i = 0;
	for (i; i < Avg_BufLen100ms; i++)
	{
		Sum += Buffer->_100ms[i];
	}
	return Sum / Avg_BufLen100ms;
}

public U32 Avg_GetU32_3sAverage(U32Buffer* Buffer)
{
	U64 Sum = 0;

	int i = 0;
	for (i; i < Avg_BufLen1s; i++)
	{
		Sum += Buffer->_1s[i];
	}
	return Sum / Avg_BufLen1s;
}

public U32 Avg_GetU32_30sAverage(U32Buffer* Buffer)
{
	U64 Sum = 0;

	int i = 0;
	for (i; i < Avg_BufLen3s; i++)
	{
		Sum += Buffer->_3s[i];
	}
	return Sum / Avg_BufLen3s;
}

public U32 Avg_GetU32_10minAverage(U32Buffer* Buffer)
{
	U64 Sum = 0;

	int i = 0;
	for (i; i < Avg_BufLen30s; i++)
	{
		Sum += Buffer->_30s[i];
	}
	return Sum / Avg_BufLen30s;
}

//*******************************************************************************
*/
