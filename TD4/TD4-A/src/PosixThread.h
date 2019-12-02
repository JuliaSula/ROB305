/**@file PosixThread.h
 * @brief Implements class PosixThread
 */

#ifndef POSIXTHREAD_INCLUDED
#define POSIXTHREAD_INCLUDED

#include <exception>
#include <pthread.h>
#include <cerrno>
#include <ctime>
#include <stdexcept>

/**@brief Class that represents a Thread (through an object)
 */
class PosixThread
{
private:

	/**@brief Structure that identifies a Thread
	 */
	pthread_t posixId;
	
	/**@brief Structure that identifies thread attribute object
	 */
	pthread_attr_t posixAttr; 
	
	/**@brief Structure that represents an Invalid Thread (one that does not have an Id)
	 */
	static pthread_t INVALID_PTHREAD;
	
	/**@brief Bool that represents if the thread/task is active or not
	 */
	volatile bool Active=false;
public:

	/**@brief Class exception
	 * To be thrown when the thread does not exist /it's not active
	 */
    class Exception : std::exception
		{
			public:
				const char *what() const noexcept;
		};
		
	/**@brief PosixThread default constructor
	 * It sets thread atributes to default values
	 */
	PosixThread();
	
	/**@brief Verifies if the thread is active/exists or not
	 * 
	 * @return bool that represent isActive or not
	 */ 
	bool isActive();
	
	/**@brief PosixThread constructor
	 * It sets thread atributes of an already existing thread
	 * It creates an object thread from posixId
	 * 
	 * @param posixId: structure that identifies a Thread
	 */
	PosixThread(pthread_t posixId);
	
	/**@brief PosixThread destructor
	 * Destroy thread through the value of posixId of the object posixThread
	 */
	~PosixThread();
	
	/**@brief Runs a function in a thread
	 * Creates a thread that calls threadFunc and uses threadArg
	 * 
	 * @param threadFunc: function that will be run by the thread
	 * @param threadArg: data that will be transmitted to the thread
	 * and used by the tread function
	 */
	void start(void *(*threadFunc)(void *), void *threadArg);
	
	/**@brief Joins the thread
	 * It will wait for the thread to be finish and join it to the main program
	 */
	void join();
	
	/**@brief Joins the thread with time-out 
	 * If it terminates before the timeout, it joins it, if it doesn't 
	 * throws an error
	 * 
	 * @param timeout_ms: time to be waited before throwing an error
	 * Must be in absolute time (not an interval)
	 * @return true if join sucessuful , false if not
	 */
	bool join(double timeout_ms);
	
	/**@brief Set schedPolicy and priority for an existing thread
	 * 
	 * @param schedPolicy: defines how the scheduler treats the thread after it gains control of the CPU
	 * @param priority: defines the relative importance of the work being done by each thread
	 * @return true if the task is active, false if not
	 */
	bool setScheduling(int schedPolicy, int priority);
	
	/**@brief Gets schedPolicy and priority for an existing thread
	 * 
	 * @param *schedPolicy: pointer for int that defines how the scheduler treats the thread after it gains control of the CPU
	 * @param *priority: pointer for int that defines the relative importance of the work being done by each thread
	 * @return true if the task is active, false if not
	 */
	bool getScheduling(int* p_schedPolicy= NULL, int* priority=NULL);
	
	/**@brief Function to be called by a phoney Thread
	 */
	static void* dummyFunction(void*);
	
	/**@brief Function that verifies thread Id
	 * One of the ways to initialize a thread as invalid without causing a SEGFAULT
	 * is to use an ID of an ancient thread (already terminated)
	 * Therefore this function runs a thread, with a dummy function, allowing us to have a 
	 * pthreadId that will not cause a segmentation fault
	 * 
	 * @return the pthread ID
	 */
	 pthread_t get_INVALID_PTHREAD();
};

#endif
