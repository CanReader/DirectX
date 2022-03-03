#ifndef _DEBUGGER_H_
#define _DEBUGGER_H_

#include <chrono>  // chrono::system_clock
#include <ctime>
#include <iostream>
#include "Log.h"

#define END(hr) if(FAILED(hr)) return false;

static std::string GetTime()
{
	std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	tm m;
	localtime_s(&m,&t);

	char buffer[11];
	strftime(buffer, 11,"%T",&m);

	return buffer;
}

#endif // !1



