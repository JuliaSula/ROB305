#include "PosixThread.h"
#include "TimeSpec.h"
#include <iostream>
using namespace std;

void* PosixThread::dummyFunction(void*)
{
	return nullptr;
}


pthread_t PosixThread::get_INVALID_PTHREAD()
{
	static pthread_t INVALID_PTHREAD = 0;
	if (INVALID_PTHREAD == 0)
	{
		pthread_create(&INVALID_PTHREAD, nullptr, dummyFunction, nullptr);
		timespec_wait(timespec_from_ms(1)); 							// Waits for one millisecond.
	}
	return INVALID_PTHREAD;
}


PosixThread::PosixThread()
{
	pthread_attr_init(&posixAttr);										//Initialize thread attributes
	posixId=get_INVALID_PTHREAD();
	
	pthread_attr_setinheritsched(&posixAttr, PTHREAD_EXPLICIT_SCHED);	//Defines that the scheduling policy must be explicitly defined,
																		//there is no inherintance
	pthread_attr_setschedpolicy(&posixAttr, SCHED_OTHER);				//Defines the default scheduling policy
	
	sched_param schedParams;
	schedParams.sched_priority = 0;										//Defines default scheduling priority
	pthread_attr_setschedparam(&posixAttr, &schedParams);				//Sets the scheduling parameters
}

PosixThread::PosixThread(pthread_t posixId): posixId(posixId)
{
	
	
	pthread_attr_init(&posixAttr);										//Initializes thread attributes
						
	
	
	pthread_attr_setinheritsched(&posixAttr, PTHREAD_EXPLICIT_SCHED); 	//Defines that the scheduling policy must be explicitly defined, 
																		//there is no inherintance

	sched_param schedParams;
	
	if(isActive())														//If thread Id does not exists throws exceptions
	{
		throw PosixThread::Exception(); 
	}
	
	pthread_attr_getschedparam(&posixAttr, &schedParams);				//Gets the scheduling parameter					
	pthread_attr_setschedparam(&posixAttr, &schedParams);				//Sets the scheduling parameters
	
}
bool PosixThread::isActive()
{
	
	sched_param schedParams;
	int policy;
	int err=pthread_getschedparam(posixId, &policy, &schedParams);  	//Returns 0 if, sucessuful, returns ESRCH if
	return err!=ESRCH;													// no thread with the ID thread could be found.
}

PosixThread::~PosixThread()
{
	pthread_attr_destroy(&posixAttr);	
}

void PosixThread::start(void *(*threadFunc)(void *), void *threadArg)
{
	pthread_create(&posixId, &posixAttr, threadFunc, threadArg);
}
	
void PosixThread::join()
{	 
	  pthread_join(posixId, nullptr);
}
	

bool PosixThread::join(double timeout_ms)
{
	timespec timeout_tspec=timespec_from_ms(timeout_ms);
	int ret=pthread_timedjoin_np(posixId, NULL, &timeout_tspec);

	return !(bool)ret;

}

bool PosixThread::setScheduling(int schedPolicy, int priority)
{
	bool setPolicy;
	bool setSched;
	sched_param schedParams;
	
	schedParams.sched_priority = priority;
	

	setPolicy=(bool)pthread_attr_setschedpolicy(&posixAttr, schedPolicy);//Verifies whether the setting of the policy
																		 //was sucessful or not
	
	setSched =(bool)pthread_attr_setschedparam(&posixAttr, &schedParams);//Verifies whether the setting of the schedParam
																		 //was sucessful or not

	return !(setPolicy || setSched);									//If there was an error during the setting it is returns false
	
}
bool PosixThread::getScheduling(int* schedPolicy, int* priority) 
{	
	
	bool getPolicy;
	bool getSched;
	
	sched_param schedParams;

	getPolicy =(bool)pthread_attr_getschedpolicy(&posixAttr, schedPolicy);//Verifies if the get was successeful(returns 0)

	getSched =(bool)pthread_attr_getschedparam(&posixAttr, &schedParams);//Verifies if the get was successeful

	*priority = schedParams.sched_priority;

	return !(getPolicy || getSched);									//If there was an error during the setting it is returns false
	
}

const char *PosixThread::Exception::what() const noexcept
{
		return " [PosixThread] PosixThread does not exist";
}
