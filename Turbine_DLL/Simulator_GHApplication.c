//***********************************************************************
//
//                        Copyright (c) Eleon a/s
//
//***********************************************************************
//
// $Date: 2014/09/15 20:00:00 $
// $Author: Hindrik $
// $RCSfile: Simulator_GHApplication.h,v $
// $Revision: 1.0 $
//
//***********************************************************************

//***********************************************************************
#include <Simulator.h>
#include <Simulator_GHApplication.h>

#define PI 3.14159265359
#define PITCH_FEATHER_RAD 1.570796




// pointers to actual variable values in variable database structures
// pointers are used in this code, to make accessing database variables easier (and faster)

// values as inputs to this module
BOOL * GH_CO_AlgPcsSynchroniseRequest_value;
BOOL * GH_CO_AlgWaitForStartup_value;
F32 * GH_CO_AlgPitchPositionDemand1_value;
F32 * GH_CO_AlgPitchPositionDemand2_value;
F32 * GH_CO_AlgPitchPositionDemand3_value;
F32 * GH_CO_AlgPcsTorqueDemand_value;

// values as outputs to this module
BOOL * GH_CI_AlgWaitForStartup_value;
BOOL * GH_CI_AlgStartupTurbine_value;
BOOL * GH_CI_AlgNormalShutdown_value;
BOOL * GH_CI_AlgPcsSynchronised_value;
BOOL * GH_CI_AlgBladeLoadsOk_value;
BOOL * GH_CI_AlgAllBladesAtFeather_value;
F32 * GH_CI_AlgGeneratorSpeed_value;
F32 * GH_CI_AlgAverageWindSpeed_value;
F32 * GH_CI_AlgSpeedSetpointLimit_value;
F32 * GH_CI_AlgPowerSetpointLimit_value;
F32 * GH_CI_AlgPitchPosition1_value;
F32 * GH_CI_AlgPitchPosition2_value;
F32 * GH_CI_AlgPitchPosition3_value;
F32 * GH_CI_AlgGeneratorSpeed_value;
F32 * GH_CI_AlgRotorAzimuth_value;
F32 * GH_CI_AlgElectricalTorque_value;
F32 * GH_CI_AlgRealPower_value;






//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++							FUNCTIONS								++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




//**************************************************************************
// Conversion degree to rad
//**************************************************************************
float Deg_To_Rad(float inVal) { return (inVal / 180) * (float)PI; }
//**************************************************************************
//**************************************************************************



//**************************************************************************
// Conversion rad to degree
//**************************************************************************
float Rad_To_Deg(float inVal) { return (inVal  / (float)PI ) * 180; }
//**************************************************************************
//**************************************************************************



//**************************************************************************
// Conversion rad/s to RPM
//**************************************************************************
float RadS_To_Rpm(float inVal) { return (inVal / (float)PI) * 30; }
//**************************************************************************
//**************************************************************************



//**************************************************************************
// Conversion RPM to rad/s
//**************************************************************************
float Rpm_To_RadS(float inVal) { return (inVal * (float)PI) / 30; }
//**************************************************************************
//**************************************************************************



//**************************************************************************
// Pitch movement dynamics simulation
//**************************************************************************
static void PitchControl()
{
	// simulate pitch movement by feeding the pitch demand output back to pitch position input
	*GH_CI_AlgPitchPosition1_value = *GH_CO_AlgPitchPositionDemand1_value;
	*GH_CI_AlgPitchPosition2_value = *GH_CO_AlgPitchPositionDemand2_value;
	*GH_CI_AlgPitchPosition3_value = *GH_CO_AlgPitchPositionDemand3_value;
}
//**************************************************************************
//**************************************************************************



//**************************************************************************
// Rotor rotation dynamics simulation
//**************************************************************************
static void RotorRotation()
{
	// simulate generator speed[rad/s], calculated based on pitch position
	*GH_CI_AlgGeneratorSpeed_value = ((PITCH_FEATHER_RAD + 0.01) - *GH_CI_AlgPitchPosition1_value) / (F32)1.18;
	
	// update rotor azimuth value, calculate just based on speed
	F32 rad20ms = *GH_CI_AlgGeneratorSpeed_value / 50;
	*GH_CI_AlgRotorAzimuth_value += rad20ms;
	if (*GH_CI_AlgRotorAzimuth_value > (F32)(2*PI))
	{
		*GH_CI_AlgRotorAzimuth_value = 0;
	}
}
//**************************************************************************
//**************************************************************************



//**************************************************************************
// Power converter operation simulation
//**************************************************************************
#define PCONV_DISCONNECTED 0
#define PCONV_CONNECTED 1
#define PCONV_CONNECTING 2
#define PCONV_DISCONNECTING 3
static U8 PowerConverter_State;

static void PowerConverter()
{
	// changing of converter state
	if(PowerConverter_State == PCONV_DISCONNECTED && *GH_CO_AlgPcsSynchroniseRequest_value)
	{
		PowerConverter_State = PCONV_CONNECTING;
	}
	else if(PowerConverter_State == PCONV_CONNECTED && !*GH_CO_AlgPcsSynchroniseRequest_value)
	{
		PowerConverter_State = PCONV_DISCONNECTING;
	}
	
	// power converter state machine
	switch(PowerConverter_State)
	{
		case PCONV_DISCONNECTED:
		
			// do nothing
			break;
		
		case PCONV_CONNECTED:
		
			// calculate simulated electrical torque value
			*GH_CI_AlgElectricalTorque_value = *GH_CO_AlgPcsTorqueDemand_value * 0.995;
			*GH_CI_AlgRealPower_value = *GH_CI_AlgElectricalTorque_value * *GH_CI_AlgGeneratorSpeed_value;
			break;
		
		case PCONV_CONNECTING:
		
			*GH_CI_AlgPcsSynchronised_value = true;
			PowerConverter_State = PCONV_CONNECTED;
			break;
		
		case PCONV_DISCONNECTING:
		
			*GH_CI_AlgElectricalTorque_value = 0;
			*GH_CI_AlgRealPower_value = 0;
			*GH_CI_AlgPcsSynchronised_value = false;
			PowerConverter_State = PCONV_DISCONNECTED;
			break;
	}
	
}
//**************************************************************************
//**************************************************************************



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++






//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//**************************************************************************
// SIMULATION MODE STATE MACHINE - GH algorithm only
//**************************************************************************
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// state functions declarations
static void State_WaitStart();
static void State_Startup();
static void State_NormalShutdown();
static void State_PowerProduction();

static void (*Active_State)(void) = State_WaitStart;
static void (*State_Prev)(void) = NULL;		// indicates the previous mode(sometimes it could affect the behaviour of new mode)

static BOOL StateChanged = true;		// indicates if the function/state is called the first time (startup or state change)

#define NORMALSHUTDOWN_DISCONNECTING 0
#define NORMALSHUTDOWN_COMPLETESTOP 1
static U8 State_NormalShutdown_Step = 0;






//**************************************************************************
// This function must be called once, before using other functions
// Initialize database variables pointers
//**************************************************************************
void Simulator_GHApplication_Initialize()
{
	// get database variables IDs (pointers to database variable structs) and then
	// assign pointers to direct to the value fields of the variables (for easy direct database value access from application)
	struct os_db_variable * varID;

	OS_VarDB_GetVariableID("GH_CO_AlgPcsSynchroniseRequest", &varID);
	GH_CO_AlgPcsSynchroniseRequest_value = &(varID->c.Value.bool);
	OS_VarDB_GetVariableID("GH_CI_AlgPcsSynchronised", &varID);
	GH_CI_AlgPcsSynchronised_value = &(varID->c.Value.bool);
	OS_VarDB_GetVariableID("GH_CI_AlgBladeLoadsOk", &varID);
	GH_CI_AlgBladeLoadsOk_value = &(varID->c.Value.bool);
	OS_VarDB_GetVariableID("GH_CI_AlgAllBladesAtFeather", &varID);
	GH_CI_AlgAllBladesAtFeather_value = &(varID->c.Value.bool);
	OS_VarDB_GetVariableID("GH_CI_AlgGeneratorSpeed", &varID);
	GH_CI_AlgGeneratorSpeed_value = &(varID->c.Value.f32);
	OS_VarDB_GetVariableID("GH_CI_AlgAverageWindSpeed", &varID);
	GH_CI_AlgAverageWindSpeed_value = &(varID->c.Value.f32);
	OS_VarDB_GetVariableID("GH_CI_AlgSpeedSetpointLimit", &varID);
	GH_CI_AlgSpeedSetpointLimit_value = &(varID->c.Value.f32);
	OS_VarDB_GetVariableID("GH_CI_AlgPowerSetpointLimit", &varID);
	GH_CI_AlgPowerSetpointLimit_value = &(varID->c.Value.f32);
	OS_VarDB_GetVariableID("GH_CI_AlgPitchPosition1", &varID);
	GH_CI_AlgPitchPosition1_value = &(varID->c.Value.f32);
	OS_VarDB_GetVariableID("GH_CO_AlgPitchPositionDemand1", &varID);
	GH_CO_AlgPitchPositionDemand1_value = &(varID->c.Value.f32);
	OS_VarDB_GetVariableID("GH_CI_AlgRotorAzimuth", &varID);
	GH_CI_AlgRotorAzimuth_value = &(varID->c.Value.f32);
	OS_VarDB_GetVariableID("GH_CO_AlgPcsTorqueDemand", &varID);
	GH_CO_AlgPcsTorqueDemand_value = &(varID->c.Value.f32);
	OS_VarDB_GetVariableID("GH_CI_AlgElectricalTorque", &varID);
	GH_CI_AlgElectricalTorque_value = &(varID->c.Value.f32);
	OS_VarDB_GetVariableID("GH_CI_AlgRealPower", &varID);
	GH_CI_AlgRealPower_value = &(varID->c.Value.f32);
	OS_VarDB_GetVariableID("GH_CO_AlgWaitForStartup", &varID);
	GH_CO_AlgWaitForStartup_value = &(varID->c.Value.bool);
	OS_VarDB_GetVariableID("GH_CI_AlgNormalShutdown", &varID);
	GH_CI_AlgNormalShutdown_value = &(varID->c.Value.bool);
	OS_VarDB_GetVariableID("GH_CI_AlgStartupTurbine", &varID);
	GH_CI_AlgStartupTurbine_value = &(varID->c.Value.bool);
	/*OS_VarDB_GetVariableID("", &varID);
	_value = &(varID->c.Value.);*/
}






//**************************************************************************
// Call the appropriate state function depending on simulation state
//**************************************************************************
void Simulator_GHApplication_Control()
{
	//--------------------------------------------------------------------------
	// MODE FIRST ENTRY
	//--------------------------------------------------------------------------
	if(Sim_ModeChanged)
	{
		Sim_ModeChanged = false;
		strcpy(V_SimulationModeTxt_value, "GH app only");
		StateChanged = true;
		
		// initialize some values for simulation
		F32 x = 6;
		OS_VarDB_UpdateVariableByName("GH_CI_AlgAverageWindSpeed", &x, 4);
		x = 1.31;
		OS_VarDB_UpdateVariableByName("GH_CI_AlgSpeedSetpointLimit", &x, 4);
		x = 3654900;
		OS_VarDB_UpdateVariableByName("GH_CI_AlgPowerSetpointLimit", &x, 4);
		U8 y = 1;
		OS_VarDB_UpdateVariableByName("GH_CI_AlgBladeLoadsOk", &y, 1);
		y = 1;
		OS_VarDB_UpdateVariableByName("GH_CI_AlgAllBladesAtFeather", &y, 1);
	}
	//--------------------------------------------------------------------------
	
	
	//--------------------------------------------------------------------------
	// MODE OPERATION LOOP
	//--------------------------------------------------------------------------
	(*Active_State)();	// call the GH simulation function according to current turbine state
	//--------------------------------------------------------------------------
}


//**************************************************************************
// GH STATE - Wait start command from OS menu
//**************************************************************************
static void State_WaitStart()
{
	//--------------------------------------------------------------------------
	// STATE FIRST ENTRY
	//--------------------------------------------------------------------------
	if(StateChanged)
	{
		StateChanged = false;
		strcpy(V_SimulationStateTxt_value, "Waiting for start");
		
		*GH_CI_AlgStartupTurbine_value = false;
		*GH_CI_AlgNormalShutdown_value = false;
		
		
		//GH_CI_AlgAllBladesAtFeather = true;
		*GH_CI_AlgPitchPosition1_value = (F32)PITCH_FEATHER_RAD;
		*GH_CI_AlgPitchPosition2_value = (F32)PITCH_FEATHER_RAD;
		*GH_CI_AlgPitchPosition3_value = (F32)PITCH_FEATHER_RAD;
		*GH_CI_AlgGeneratorSpeed_value = 0;
	}
	//--------------------------------------------------------------------------
	
	
	//--------------------------------------------------------------------------
	// STATE OPERATION LOOP
	//--------------------------------------------------------------------------
	// DO NOTHING
	//--------------------------------------------------------------------------
	
	
	//--------------------------------------------------------------------------
	// STATE EXIT CONDITIONS
	//--------------------------------------------------------------------------
	if(*V_SimStartTurbine_value)	// start command received
	{
		*V_SimStartTurbine_value = false;
		
		StateChanged = true;
		State_Prev = Active_State;
		Active_State = State_Startup;
		
		*GH_CI_AlgStartupTurbine_value = true;
	}
	//--------------------------------------------------------------------------
}


//**************************************************************************
// GH STATE - Startup
//**************************************************************************
static void State_Startup()
{
	//--------------------------------------------------------------------------
	// STATE FIRST ENTRY
	//--------------------------------------------------------------------------
	if(StateChanged)
	{
		StateChanged = false;
		strcpy(V_SimulationStateTxt_value, "Startup");
		
		*GH_CI_AlgStartupTurbine_value = false;
		*GH_CI_AlgAllBladesAtFeather_value = false;
	}
	//--------------------------------------------------------------------------
	
	
	//--------------------------------------------------------------------------
	// STATE OPERATION LOOP
	//--------------------------------------------------------------------------
	PitchControl();
	RotorRotation();
	PowerConverter();
	//--------------------------------------------------------------------------
	
	
	//--------------------------------------------------------------------------
	// STATE EXIT CONDITIONS
	//--------------------------------------------------------------------------
	//U8 y;
	//OS_VarDB_ReadVariable(GH_CI_AlgGeneratorSpeed_varID, &y, 1, dummyTimeStamp);
	
	if( *V_SimStopTurbine_value )	// if OS normal shutdown command
	{
		*V_SimStopTurbine_value = false;
	
		StateChanged = true;
		State_Prev = Active_State;
		Active_State = State_NormalShutdown;
		
		*GH_CI_AlgNormalShutdown_value = true;
	}
	else if(*GH_CI_AlgPcsSynchronised_value)	// if converter synchronised
	{
		StateChanged = true;
		State_Prev = Active_State;
		Active_State = State_PowerProduction;
	}
	//--------------------------------------------------------------------------
}


//**************************************************************************
// GH STATE - Power production
//**************************************************************************
static void State_PowerProduction()
{
	//--------------------------------------------------------------------------
	// STATE FIRST ENTRY
	//--------------------------------------------------------------------------
	if(StateChanged)
	{
		StateChanged = false;
		strcpy(V_SimulationStateTxt_value, "Production");
		
		*GH_CI_AlgPcsSynchronised_value = true;
	}
	//--------------------------------------------------------------------------
	
	
	//--------------------------------------------------------------------------
	// STATE OPERATION LOOP
	//--------------------------------------------------------------------------
	PitchControl();
	RotorRotation();
	PowerConverter();
	//--------------------------------------------------------------------------
	
	
	//--------------------------------------------------------------------------
	// STATE EXIT CONDITIONS
	//--------------------------------------------------------------------------
	if(*V_SimStopTurbine_value)	// normal shutdown
	{
		*V_SimStopTurbine_value = false;
	
		StateChanged = true;
		State_Prev = Active_State;
		Active_State = State_NormalShutdown;
		
		*GH_CI_AlgNormalShutdown_value = true;
	}
	//--------------------------------------------------------------------------
}


//**************************************************************************
// GH STATE - Normal shutdown
//**************************************************************************
static void State_NormalShutdown()
{	
	//--------------------------------------------------------------------------
	// STATE FIRST ENTRY
	//--------------------------------------------------------------------------
	if(StateChanged)
	{
		StateChanged = false;
		strcpy(V_SimulationStateTxt_value, "Normal shutdown");
		
		*GH_CI_AlgNormalShutdown_value = false;
		
		// select different behaviour based on previous state
		if(State_Prev == State_Startup)	// if previous state was Startup then skip grid disconnecting step
		{
			State_NormalShutdown_Step = NORMALSHUTDOWN_COMPLETESTOP;
		}
	}
	
	
	//--------------------------------------------------------------------------
	// STATE OPERATION LOOP
	//--------------------------------------------------------------------------
	PitchControl();
	RotorRotation();
	PowerConverter();

	switch(State_NormalShutdown_Step)
	{
		case NORMALSHUTDOWN_DISCONNECTING:
		
			// step exit condition
			//--------------------------------------------------------------------------
			if( !(*GH_CO_AlgPcsSynchroniseRequest_value) )	// wait for deactivation of Pcs sync request
			{
				State_NormalShutdown_Step = NORMALSHUTDOWN_COMPLETESTOP;
			}
			//--------------------------------------------------------------------------
			break;
		
		case NORMALSHUTDOWN_COMPLETESTOP:
		
			// check if all blades are in feather position (tolerance +/-0,3 degrees)
			if((*GH_CI_AlgPitchPosition1_value <= (PITCH_FEATHER_RAD + 0.005236) && *GH_CI_AlgPitchPosition1_value >= (PITCH_FEATHER_RAD - 0.005236)) &&
				(*GH_CI_AlgPitchPosition2_value <= (PITCH_FEATHER_RAD + 0.005236) && *GH_CI_AlgPitchPosition2_value >= (PITCH_FEATHER_RAD - 0.005236)) &&
				(*GH_CI_AlgPitchPosition3_value <= (PITCH_FEATHER_RAD + 0.005236) && *GH_CI_AlgPitchPosition3_value >= (PITCH_FEATHER_RAD - 0.005236)))
			{
				*GH_CI_AlgAllBladesAtFeather_value = true;
			}
			
			//--------------------------------------------------------------------------
			// STATE EXIT CONDITIONS
			//--------------------------------------------------------------------------
			if(*GH_CO_AlgWaitForStartup_value)		// shutdown procedure completed
			{	
				StateChanged = true;
				State_Prev = Active_State;
				Active_State = State_WaitStart;
			}
			//--------------------------------------------------------------------------
			break;
	}
	//--------------------------------------------------------------------------
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//**************************************************************************
//**************************************************************************
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
