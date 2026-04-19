#include <Timer_t1_v3.h>


S8 StandardTimer(struct StandardTimerVarStruct *StandardTimerVars)
{
	StandardTimerVars->StandardTimerCalled = 1;
	switch (StandardTimerVars->Start) {

		case TIMER_UP:


			StandardTimerVars->TimerValue += StandardTimerVars->IntervalTime;
			if (StandardTimerVars->TimerValue > *StandardTimerVars->TimeOutPointer) {
				
				return TIMER_UP_END;
			}
			else
			{
				return TIMER_NONE_END;
			}
			break;
		case TIMER_STOP:
			return TIMER_NONE_END;
		case TIMER_DOWN:
			if (StandardTimerVars->TimerValue < StandardTimerVars->IntervalTime) {
				return TIMER_DOWN_END;
			}
			StandardTimerVars->TimerValue -= StandardTimerVars->IntervalTime;
			if (StandardTimerVars->TimerValue == 0) {

				return TIMER_DOWN_END;
			}
			else
			{
				return TIMER_NONE_END;
			}
			break;	
	}
}

U8 StandardTimerNotCalled(struct StandardTimerVarStruct *StandardTimerVars)
{
	if(StandardTimerVars->StandardTimerCalled){
		StandardTimerVars->StandardTimerCalled = 0;
		return 1;
	}
	else {
	return 0;

	}
}

void StopTimer(struct StandardTimerVarStruct *StandardTimerVars)
{
	StandardTimerVars->OldStart = StandardTimerVars->Start;
	StandardTimerVars->Start = TIMER_STOP;
}

void SetTimer(struct StandardTimerVarStruct *StandardTimerVars, U32 SetValue)
{
	StandardTimerVars->TimerValue = SetValue;
	return StandardTimerVars->TimerValue;
}

U32 GetTimer(struct StandardTimerVarStruct *Delay)
{
	return Delay->TimerValue;
}

void ResetTimer(struct StandardTimerVarStruct *StandardTimerVars)
{
	StopTimer(StandardTimerVars);
	SetTimer(StandardTimerVars, 0);
	return 0;
}

void StartTimer(struct StandardTimerVarStruct *StandardTimerVars)
{
	StandardTimerVars->OldStart = StandardTimerVars->Start;
	StandardTimerVars->Start = TIMER_UP;

}

void StartTimerUp(struct StandardTimerVarStruct *StandardTimerVars)
{
	StandardTimerVars->OldStart = StandardTimerVars->Start;
	StandardTimerVars->Start = TIMER_UP;
}

void StartTimerDown(struct StandardTimerVarStruct *StandardTimerVars)
{
	StandardTimerVars->OldStart = StandardTimerVars->Start;
	StandardTimerVars->Start = TIMER_DOWN;
}

S8 VdbTimer(struct VdbTimerVarStruct *VdbTimerVars)
{
	//TODO
	return 0;
}

U8 VdbTimerNotCalled(struct VdbTimerVarStruct *VdbTimerVars)
{
	//TODO
	return 0;
}

void StopVdbTimer(struct VdbTimerVarStruct *VdbTimerVars)
{
	//TODO
}

void SetVdbTimer(struct VdbTimerVarStruct *VdbTimerVars, U32 SetValue)
{
	//TODO

}

U32 GetVdbTimer(struct VdbTimerVarStruct *VdbTimerVars)
{
	//TODO
	return 0;
}

void ResetVdbTimer(struct VdbTimerVarStruct *VdbTimerVars)
{
	//TODO

}

void StartVdbTimer(struct VdbTimerVarStruct *VdbTimerVars)
{
	//TODO

}

void StartVdbTimerUp(struct VdbTimerVarStruct *VdbTimerVars)
{
	//TODO

}

void StartVdbTimerDown(struct VdbTimerVarStruct *VdbTimerVars)
{
	//TODO

}

STATUS InitVdbTimerSave(struct VdbTimerVarStruct *Delay, char *VdbName)
{
	//TODO
	return 0;
}
