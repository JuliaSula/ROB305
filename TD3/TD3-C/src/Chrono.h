/**@file Chrono.h
 * @brief Implements the class Chrono
 */
 
#ifndef CHRONO_INCLUDED
#define CHRONO_INCLUDED
#include "TimeSpec.h"

/**@brief Class that represents a chronometer
 */
class Chrono
{
	
private:
	/**@brief startTime: the times the chronometer starts
	 */
	timespec startTime_ts;
	/**@brief stopTime: the times the chronometer stops
	 */
	timespec stopTime_ts;

public:
	/**@brief Chrono constructor
	 * Sets and starts a chronometer
	 */
	Chrono();
	
	/**@brief Stops the chronometer
	 * Sets chronometer stopTime
	 */
	void stop();
	
	/**@brief Restarts the chronometer
	 * Reset startTime and stopTime
	 */
	void restart();
	
	/**@brief Verifies if the chronometer is active
	 * Checks if stop and start time are equals
	 */
	bool isActive();
	
	/**@brief Returns startTime
	 * 
	 * @return startTime in ms
	 */
	double startTime();
	
	/**@brief Returns stopTime
	 * 
	 * @return stopTime in ms
	 */
	double stopTime();
	
	/**@brief Return time passed since the start of the chronometer
	 * 
	 * @return timeStop-timeStart in ms
	 */
	double lap();
};

#endif
