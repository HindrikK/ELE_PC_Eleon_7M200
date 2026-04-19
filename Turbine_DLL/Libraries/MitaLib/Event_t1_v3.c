#include <Event_t1_v3.h>

static struct EventTextStruct *EventStructures;

static struct EventTextStruct *EventStructures_Locals_for_Debug[1024];
static int EventTextStruct_Locals_count = 0;

//struct EventTextStruct
//{
//	U16 EventNo;
//	char *EventText;
//};
STATUS UserEvent(struct EventTextStruct Event)
{
	OS_EVENTLOG_make_entry(Event.EventNo, Event.EventText);
	//TODO
	return 0;
}

STATUS GetEventNumber(struct EventTextStruct *Event, char *EventText)
{
	Event->EventNo= EventTextStruct_Locals_count++;
	EventTextStruct_Locals_count++;
	Event->EventText = EventText;
	return 0;
}
