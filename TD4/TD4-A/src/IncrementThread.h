/**@file IncrementThread.h
 * @brief Implements IncrementThread class derived from Thread
 */
#ifndef INCREMENTTHREAD_INCLUDED
#define INCREMENTTHREAD_INCLUDED

#include "Thread.h"

/**@brief Increment Thread characteristic run function is an
 * increment
 */
class IncrementThread: public Thread
{
private:
	/**@brief Number of times to increment
	 */
	unsigned int nLoops;
	
	/**@brief Variable to be incremented
	 */
	volatile double *counter;
	
public:
	/**@brief Increment thread constructor
	 * Sets its scheduling policy and priority and the main arguments for its
	 * run function
	 *
	 * @param nLoop: number of times to increment
	 * @param *counter: pointer to the variable to be incremented
	 * @param schedPolicy :defines how the scheduler treats the thread after it gains control of the CPU
	 * @param schedPriority:defines the relative importance of the work being done by each thread
	 */
	IncrementThread(unsigned int nLoops, volatile double *counter, int schedPolicy, int schedPriority);
	
	/**@brief Increment thread destructor
	 */
	~IncrementThread();
	
	/**@brief Increments counter 
	 */
	void run();

};

#endif
