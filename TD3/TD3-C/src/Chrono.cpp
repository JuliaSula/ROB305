#include "Chrono.h"


Chrono::Chrono() : startTime_ts(timespec_now()), stopTime_ts(startTime_ts) {}

void Chrono::restart()
{
	startTime_ts=timespec_now();
	stopTime_ts= startTime_ts;	
}
	
void Chrono::stop()
{
	stopTime_ts=timespec_now();
}

bool Chrono::isActive()
{
	return startTime_ts == stopTime_ts;
}

double Chrono::startTime()
{
	return timespec_to_ms(startTime_ts);
}

double Chrono::stopTime()
{
	return timespec_to_ms(stopTime_ts);
}

double Chrono::lap()
{
	if (!isActive())
		return timespec_to_ms(stopTime_ts-startTime_ts);
	else
		return timespec_to_ms(timespec_now()-startTime_ts);
			
}
