#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <cstdarg>
#include <cstdio>

#include "mutex.hpp"

using namespace std;
using namespace tailio;

enum Level {
	FATAL,
	ERROR,
	WARN,
	INFO,
	DEBUG,
	TRACE
};

inline void log(Level level,const char* fmt, ...) {
#ifdef _DEBUG_
	va_list argp;
	va_start(argp, fmt);
	log(level,fmt,argp);
	va_end(argp);
#endif	
}

extern Mutex logMutex;

inline void log(Level level,const char* fmt, va_list argp) {
#ifdef _DEBUG_
	logMutex.lock();
	vfprintf(stderr, fmt, argp);
	fprintf(stderr, "\n");
	logMutex.unlock();
#endif	
	
}

inline void debug(const char* fmt, ...) {
#ifdef _DEBUG_
	va_list argp;
	va_start(argp, fmt);
	log(DEBUG, fmt, argp);
	va_end(argp);
#endif	
}


#endif