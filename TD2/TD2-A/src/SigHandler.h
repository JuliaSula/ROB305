/**@file SigHandler.h
 * @brief Implements function in order to configure and create timer
 */
#ifndef SigHandler_h_INCLUDED
#define SigHangler_h_INCLUDED
#include <signal.h>
#include <time.h>

/**@brief  Definition of handler function
 * 
 * @param siginfo_t* si: data structure containing signal information
 * from the timer
 */ 
typedef void(*handler_t)(int, siginfo_t* si,void* data);

/**@brief Counter to 15
 * Action to be done at the timer expiration
 * 
 * @param siginfo_t *si: si data structure containing signal information
 * from the timer
 * @param data pointer to the information from the timer signal (data), 
 * that'll be changed by the myHandler function
 */ 
void myHandler(int, siginfo_t* si, void* data);


/**@brief Initiates and creates a POSIX per-process timer
 * Definition of the timer through the action (sigAction/myHandler) to
 * be done in the expiration of the timer and the event (sigEvent) when 
 * the timer expires
 * Creation of the timer thanks to librarys signal and timer
 * 
 * @param myHandler: pointer to be called by the timer
 * @param Data: data to be transmitted to the handler
 * @return tid: pointer to timer created
 */ 
timer_t init_timer(handler_t myHandler, void* Data);

#endif
