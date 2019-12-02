/**@file CpuLoop.h
 * @brief Implements class CpuLoop
 */

#ifndef CPULOOP_INCLUDED
#define CPULOOP_INCLUDED
#include "Calibrator.h"

/**@brief Class that uses callibrator to know how
 * many loops is needs to do for a certain time wait
 * and uses loop to do this amount of loops
 */
class CpuLoop : public Looper
{
private:

	/**@brief Calibrator to calculate estimated number of loops
	 */
	Calibrator calibrator;
public:
	
	/**@brief CpuLoop Constructor
	 * It initializes calibrator
	 * 
	 * @param calibrator: pointer to a calibrator object
	 */ 
	CpuLoop(Calibrator& calibrator);
	
	/**@brief Estimated number of loops to have a pause of duration_ms, 
	 * run this number of loops
	 * 
	 * @param duration_ms :time interval
	 */
	void runTime(double duration_ms);
};

#endif
