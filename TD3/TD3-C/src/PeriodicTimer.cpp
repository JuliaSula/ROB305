#include "PeriodicTimer.h"

#include "TimeSpec.h"

#include <iostream>

void PeriodicTimer::start(double duration_ms)
{
	
	itimerspec its;
	timespec   duration_tspec = timespec_from_ms(duration_ms);
	its.it_value	 = {duration_tspec.tv_sec, duration_tspec.tv_nsec};
	its.it_interval  = its.it_value;
	
	timer_settime(tid, 0, &its, NULL);
	
}
