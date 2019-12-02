#include "Mutex.h"
#include "TimeSpec.h"
#include <iostream>
#include <stdexcept>
#include <string.h>
using namespace std;
Mutex::Mutex()
{
	pthread_mutexattr_t mutexAttribute;									/*Creation atribute mutex*/
	pthread_mutexattr_init(&mutexAttribute);							/*Initialization atribute mutex*/
	pthread_mutexattr_settype(&mutexAttribute, PTHREAD_MUTEX_RECURSIVE);/*Definition du type mutex*/
	pthread_mutex_t posixId;
	pthread_mutex_init(&posixId, &mutexAttribute);
	pthread_cond_init(&posixCondId,nullptr);
	pthread_mutexattr_destroy(&mutexAttribute);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&posixId);
	pthread_cond_destroy(&posixCondId);

}

void Mutex::lock()
{
	
	pthread_mutex_lock(&posixId); //If the mutex is already locked, the calling thread blocks until the mutex becomes available
}

void Mutex::unlock()
{
	pthread_mutex_unlock(&posixId);		//If the mutex object referenced by mutex is currently locked (by any thread, including the current thread),
										//the call returns immediately. 
}

bool Mutex::lock(double timeout_ms)
{
	timespec timeout_tspec=timespec_from_ms(timeout_ms)+timespec_now();
	bool ret=pthread_cond_timedwait(&posixCondId, &posixId, &timeout_tspec);
	return ret;
}

bool Mutex::trylock()
{
	bool ret=pthread_mutex_trylock(&posixId);
	return (bool)ret;
}


Mutex::Monitor::Monitor(Mutex& m): m(m)
{
	
}

void Mutex::Monitor::notify()
{
	pthread_cond_signal(&m.posixCondId);								//call unblocks  one of the threads that are blocked 
																		//waiting on a specified condition variable cond
										
}

void Mutex::Monitor::notifyAll()
{
	pthread_cond_broadcast(&m.posixCondId);								// unblocks all threads currently blocked on waiting a specified condition variable cond
}

bool Mutex::Monitor::wait(double timeout_ms)
{
	timespec timeout_tspec=(timespec_now())+timespec_from_ms(timeout_ms);
	bool ret=pthread_cond_timedwait(&m.posixCondId, &m.posixId, &timeout_tspec);	//used to block on a condition variable untill an absolute time has passed
																					//Releases the mutex , untill condition variable changes (waits on condition)
	return (bool)ret;																	
}

void Mutex::Monitor::wait()
{
	pthread_cond_wait(&m.posixCondId, &m.posixId);						//used to block on a condition variable
																		//Releases the mutex , untill condition variable changes (waits on condition)
}

Mutex::Lock::Lock(Mutex &m): Mutex::Monitor::Monitor(m)
{
	m.lock();
}

Mutex::Lock::~Lock()
{
	m.unlock();
}

Mutex::Lock::Lock(Mutex &m, double timeout_ms) : Mutex::Monitor::Monitor(m)
{
	 int ret = m.lock(timeout_ms);
	 if (ret != 0) 
	 {
		throw Mutex::Monitor::TimeoutException();
	 }
}


Mutex::TryLock::TryLock(Mutex& m): Mutex::Monitor::Monitor(m)
{
	int ret=m.trylock();
	if (ret != 0) 
	{
		throw Mutex::Monitor::TimeoutException();
	}
}

Mutex::TryLock::~TryLock()
{
}




