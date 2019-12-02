#include "SigHandler.h"
#include <iostream>
using namespace std;


timer_t init_timer(handler_t myHandler, void* Data)
{
	struct sigaction sa;
	sa.sa_flags= SA_SIGINFO;
	sa.sa_sigaction= myHandler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGRTMIN, &sa, NULL);


	struct sigevent sev;
	sev.sigev_notify= SIGEV_SIGNAL;
	sev.sigev_signo= SIGRTMIN;
	sev.sigev_value.sival_ptr=Data;


	timer_t tid;
	timer_create(CLOCK_REALTIME, &sev, &tid);
	return tid;

}

void myHandler(int, siginfo_t* si, void*)
{	
	int* compt=(int*)si->si_value.sival_ptr;
	cout<<" [SigHandler] Counter: "<<*compt<< endl;
	*compt+=1;
}
