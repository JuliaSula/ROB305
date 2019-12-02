/**@file TakeThread.h
 * @brief Implements TakeThread Class
 */
#ifndef TAKETHREAD_INCLUDED
#define TAKETHREAD_INCLUDED


#include "Semaphore.h"
#include "Thread.h"

/**@brief This class takes tokens from the semaphore
 */
class TakeThread: public Thread
{
private:
	
	/**@brief Semaphore from which take tokens
	 */
	Semaphore *semaphore;
	
	/**@brief Number of tokens taken
	 */
	volatile int taken;
public:

	/**@brief TakeThread Constructor 
	 * 
	 * @param semaphore:pointer to the semaphore
	 */
	TakeThread(Semaphore *semaphore);
	
	/**@brief TakeThread Destructor
	 */
	~TakeThread();
	
	/**@brief Takes token from the semaphore
	 */
	void run();
	
	/**@brief Return number of taken tokens
	 * 
	 * @return number of tokens taken
	 */
	unsigned int getTaken();

};

#endif
