#ifndef SIMTIMER_H
#define SIMTIMER_H
// Header files /////
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include "configops.h"
// Global Constants ///
enum TIMER_CTRL_CODES { ZERO_TIMER, LAP_TIMER, STOP_TIMER };
extern const char RADIX_POINT;
extern const char SPACE;
// Function Prototyp
void runTimer(int milliseconds);
double accessTimer(int controlCode, char* timeStr);
double processTime(double startSec, double endSec,
	double startUSec, double endUSec, char* timeStr);
void timeToString(int secTime, int uSecTime, char* timeStr);
#endif // ifndef SIMTIMER_H