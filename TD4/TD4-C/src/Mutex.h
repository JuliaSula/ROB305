/**@file Mutex.h
 * @brief Implements Mutex class
 */
#ifndef MUTEX_INCLUDED
#define MUTEX_INCLUDED

#include <exception>
#include <pthread.h>
#include <cerrno>
#include <ctime>
#include <stdexcept>


/**@brief Class that represents a mutex in object oriented programming
 */
class Mutex
{
private:
	/**@brief Used to identify a mutex
	 */
	pthread_mutex_t posixId;
	
	/**@brief Identifies condition variables 
	 * if it is false, the threads blocks and is allowed to acces the ressource
	 * Else, when the condition changes, it is signaled by another thread, then the threads in waiting
	 * can try to acquire the mutex
	 */
	pthread_cond_t posixCondId; 
public:
	/**@brief Class that monitors the mutex
	 * It is responsable for the managing of the condition variables
	 */
	class Monitor;
	
	/**@brief Class that implements the lock and unlock of the mutex, managing exceptions
	 */
	class Lock;
	
	/**@brief Class that implements the trying to lock and unlock of the mutex, managing exceptions
	 */
	class TryLock;
public:
	/**@brief Mutex constructor
	 * It sets mutex atributes to default values
	 */
	Mutex();
	
	/**@brief Mutex destructor
	 * Destroy mutex through the value of posixId of the object mutex
	 */
	~Mutex();
private:

	/**@brief Locking mutex 
	 * Acquires mutex access to a ressource
	 * If the mutex is already lock, it waits untill is unlock
	 */
	void lock();
	
	/**@brief Locking mutex with timeout
	 * Acquires mutex access to a ressource 
	 * If the mutex is already locks, it waits a certaint time before 
	 * returning false
	 * 
	 * @param timeout_ms: absolute waiting time in ms
	 * @return true if mutex is acquire, false otherwise
	 */
	bool lock(double timeout_ms);
	
	/**@brief Tries to obtain the mutex lock
	 * If the mutex is already acquire, the trying to obtain is abandoned
	 * 
	 * @return true if mutex is acquired, false otherwise
	 */
	bool trylock();
	
	/**@brief Unlocks mutex
	 * Realeases access to a ressource
	 */
	void unlock();

};

/**@brief Class that monitors the mutex
	 * It is responsable for the managing of the condition variables
	 */
class Mutex::Monitor
{
public:
	/**@brief Monitor exception, if an time-out process exceeds the 
	 * time out time
	 */
	class TimeoutException : std::exception
	{
		public:
			const char *error();
	};
protected:
	
	/**@brief Mutex which ressources access will be monitored
	 */
	Mutex &m;
	
	/**@brief Monitor constructor
	 * 
	 * @param &m :mutex that'll be monitored
	 */
	Monitor(Mutex& m);
public:

	/**@brief Waits for a condition 
	 * Mutex is realeased while waiting for a signal 
	 */
	void wait();
	
	/**@brief Time-out waiting for a condition 
	 * Mutex is realeased for a time while waiting for a signal 
	 * 
	 * @param timeout_ms: absolute time of waiting in ms
	 */
	bool wait(double timeout_ms);
	
	/**@brief Sends signal (notifies) a waiting thread 
	 * It says that thread can pursue acquiring the mutex
	 */
	void notify();
	
	/**@brief Sends signal (notifies) to all waiting threads 
	 * It says that threads can pursue acquiring the mutex
	 */
	void notifyAll();

};

/**@brief Class that implements the trying to lock and unlock of the mutex, managing exceptions
	 */
class Mutex::TryLock : public Monitor
{
public:

	/**@brief Constructor TryLock
	 * 
	 * @param & m: mutex for which the TryLock function will be implemented
	 */
	TryLock(Mutex& m);
	
	/**@brief Destructor TryLock
	 */
	~TryLock();
};


/**@brief Class that implements the lock and unlock of the mutex, managing exceptions
 */
class Mutex::Lock : public Monitor
{
public: 
	
	/**@brief Default Constructor Lock
	 * 
	 * @param & m: mutex for which the Lock function will be implemented
	 */
	Lock(Mutex& m);
	
	
	/**@brief Constructor Lock
	 * 
	 * @param & m: mutex for which the Lock function will be implemented
	 * @param timeout_ms: absolute time to wait before abandoning the locking mutex
	 */
	Lock(Mutex& m, double timeout_ms);
	
	/**@brief Destructor Lock
	 * Releases lock mutex
	 */
	~Lock();
		
};
#endif
