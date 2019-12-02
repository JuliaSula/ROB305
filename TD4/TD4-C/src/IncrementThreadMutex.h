/**@file IncrementThreadMutex.h
 * @brief Implements IncrementThreadMutex class
 */
#ifndef INCREMENTTHREADMUTEX_INCLUDED
#define INCREMENTTHREADMUTEX_INCLUDED

#include "Thread.h"
#include "Mutex.h"

/**@brief Thread that increments a variable safely guaranteing it 
 * the coordinated access to the variable through mutex
 */
class IncrementThreadMutex: public Thread
{
private:

	/**@brief Number of times to increment
	 */
	unsigned int nLoops;
	
	/**@brief Variable to be incremented
	 */
	volatile double *counter;
	
	/**@brief Mutex that will allowed coordinated access to counter
	 */
	Mutex *m;
	
public:

	/**@brief Increment thread Mutex constructor
	 * Sets its scheduling policy and priority and the main arguments for its
	 * run function
	 *
	 * @param nLoop: number of times to increment
	 * @param *counter: pointer to the variable to be incremented
	 * @param schedPolicy :defines how the scheduler treats the thread after it gains control of the CPU
	 * @param m: mutex for thread-safety
	 */
	IncrementThreadMutex(unsigned int nLoops, volatile double *counter,int schedPolicy,  Mutex *m);
	
	/**@brief Increment thread Mutex destructor
	 */
	~IncrementThreadMutex();
	
	/**@brief Safely increments counter 
	 */
	void run();
	
	/**@brief Allows to access counter from main
	 * 
	 * @return counter value
	 */
	 double getCounter();

};

#endif
