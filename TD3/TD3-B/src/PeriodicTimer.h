/**@file PeriodicTimer.h
 * @brief Implements class PeriodicTimer derived from Timer
 */
#ifndef PERIODIC_TIMER_INCLUDED
#define PERIODIC_TIMER_INCLUDED

#include "Timer.h"

/**@brief Implements a periodic timer
 */
class PeriodicTimer : public Timer
{

	public:
		/**@brief Starts the periodic timer
		 * Configures timer through itimerspec values
		 * 
		 * @param duration_ms: timer interval
		 */
		void start(double duration_ms);
};

#endif
