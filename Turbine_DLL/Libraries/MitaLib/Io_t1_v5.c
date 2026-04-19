#include <Io_t1_v5.h>

/********************************************************************

 STURCT NAME      InputNamesStruct
 -----------
An array of this struct is made in the application, the first will be initalised
with "MaxUpdateTime" and "Threshold" if the "Module"-string is not empty.
This is used to initialise an input if it is used for a inputdriver.
For further information see the struct "IoDriverStruct".

If one of the values in the array changes the driver function will run again.

 FEELDS
 ------
   Name           Name of the input variable. Is initialised to a string name.

   Id             Id-number for the Name. This is automaticaly filled out when
				  the "InitIoDriver"-function is called.

   LocalSubscription
				  Subscription for the input. This is used by a queue in Iodrv.c

 HISTORY
 -------
	NAME         DATE        REMARKS
	BN           2001-12-17  New struct.
*******************************************************************/

//struct InputNamesStruct
//{
//	const char *Name;
//	varid_t Id;
//	SUBSCRIPTION LocalSubscription;
//};

/********************************************************************

 STURCT NAME      OutputNamesStruct
 -----------
An array of this struct is made in the application.

 FEELDS
 ------
   Name           Name of the output variable. Is initialised to a string name.

   Id             Id-number for the Name. This is automaticaly filled out when
				  the "InitIoDriver"-function is called.

 HISTORY
 -------
	NAME         DATE        REMARKS
	BN           2001-12-17  New struct.
*******************************************************************/

//struct OutputNamesStruct
//{
	//const char *Name;
	//varid_t Id;
//};

/********************************************************************

 STURCT NAME      IoDriverStruct
 -----------

 FEELDS
 ------
   Module         Input module name. If it is an empty string, no module will be
				  initialised. Then "MaxUpdateTime" and "Threshold" will not be
				  used.

   MaxUpdateTime  Max update time[ms] for the input(For further information see
				  the struct "InputNamesStruct".). It is sendt to the
				  WP-line module.

   Threshold      If the input(For further information see the struct
				  "InputNamesStruct".) value has changed more or equal to this
				  value, the WP-line module will send a new value.

   InputName      Array of the struct "InputNamesStruct". The last string in
				  the array is normally set to NULL.
				  The first in the array will be initalised with "MaxUpdateTime"
				  and "Threshold" if the "Module"-string is not empty. This is
				  used to initialise an input if it is used for a inputdriver.

   IoDriverFunc   I/O driver function. The function uses the "InputName" array
				  as inputs and the "OutputName" array for the results.
				  The function is called if one of the inputs changes.

   OutputName     Array of the struct "OutputNamesStruct". The last string in
				  the array is normally set to NULL.

 HISTORY
 -------
	NAME         DATE        REMARKS
	BN           2001-12-17  New struct.
*******************************************************************/

//struct IoDriverStruct
//{
//	const char Module[30];
//	const U32  MaxUpdateTime;
//	const U32  Threshold;
//	struct InputNamesStruct *InputName;
//	STATUS(*IoDriverFunc)(U16 Counter, struct IoDriverStruct *IoDriverTable);
//	struct OutputNamesStruct *OutputName;
//};

// ---------------------------------------------------------------------
// Only this module uses these variables and functions. (xx_lib.c and xx_app.c)
// ---------------------------------------------------------------------

/********************************************************************

 FUNCTION NAME    InitIoDriver
 -------------
 DESCRIPTION
 -----------      Initiating the I/O drivers.
				  Starts a taske that handles the I/O drivers.
				  Creates a I/O queue.
				  Creates contens of "InputNamesStruct.Id".
				  Creates contens of "OutputNamesStruct.Id".

 ARGUMENTS
 ---------
   MemoryPool     Memory pool to allocate memory from.

   Entries        Number of entries for the I/O queue.

   MyQueue        Queue start address.

   LocalSubscription:
				  Array of blocks of memory used by the
				  subscription handler to store information
				  about the subscriptions.

   NumberIoDrivers
				  Number of I/O-drivers.

   Message        Pointer to the message destination. For the queue.

   MessageSize    Size og the recieved message. For the queue.

   IoDriverTable  Pointer to the I/O-driver array.

 RETURN VALUES
 -------------
	0            Success.
	> 0          Failure.

 HISTORY
 -------
	NAME         DATE        REMARKS
	BN           2001-12-05  New function.
*******************************************************************/

STATUS InitIoDriver(OS_MEMORY_POOL *MemoryPool,const U16 Entries,UNSIGNED *MyQueue,SUBSCRIPTION *LocalSubscription,
	const U16 NumberOfIoDrivers,UNSIGNED *Message,U8 MessageSize,struct IoDriverStruct *IoDriverTable,U8 AppState) 
{

	//TODO
	return 0;
}