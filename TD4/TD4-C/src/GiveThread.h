/**@file GiveThread.h
 * @brief Implements GiveThread class
 */
#ifndef GIVETHREAD_INCLUDED
#define GIVETHREAD_INCLUDED


#include "Semaphore.h"
#include "Thread.h"

/**@brief This class gives tokens from the semaphore
 */
class GiveThread: public Thread
{
private:

	/**@brief number of tokens to be given
	 */
	unsigned int nProds;
	
	/**@brief Semaphore from which take tokens
	 */
	Semaphore *semaphore;
	
	/**@brief Number of tokens given
	 */
	unsigned int given;
public:

	/**@brief GivenThread constructor 
	 * 
	 * @param nProds: number of tokens to be given
	 * @param *semaphore: semaphore to which to give
	 */
	GiveThread(unsigned int nProds, Semaphore *semaphore);
	
	/**@brief GivenThread destructors
	 */
	~GiveThread();
	
	/**@brief Gives token from the semaphore
	 */
	void run();
	
	/**@brief Return number of given tokens
	 * 
	 * @return number of tokens given
	 */
	unsigned int getGiven();
};

#endif
