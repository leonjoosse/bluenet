/**
 * Author: Anne van Rossum
 * Copyright: Distributed Organisms B.V. (DoBots)
 * Date: 10 Oct., 2014
 * License: LGPLv3+, Apache License, or MIT, your choice
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Commonly LOG functionality is provided with as first parameter the level of severity of the message. Subsequently
 * the message follows, eventually succeeded by content if the string contains format specifiers. This means that this
 * requires a variadic macro as well, see http://www.wikiwand.com/en/Variadic_macro. The two ## are e.g. a gcc
 * specific extension that removes the , after __LINE__, so log(level, msg) can also be used without arguments.
 */
#define DEBUG                0
#define INFO                 1
#define WARN                 2
#define ERROR                3
#define FATAL                4
#define NONE                 5


#ifndef SERIAL_VERBOSITY
#error "You have to specify SERIAL_VERBOSITY"
#endif

#if SERIAL_VERBOSITY<NONE
	#include "string.h"
	#define _FILE (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

	#define log(level, fmt, ...) \
			   write("[%-30.30s : %-5d] " fmt "\r\n", _FILE, __LINE__, ##__VA_ARGS__)

	#define _log(level, fmt, ...) \
			   write(fmt, ##__VA_ARGS__)
#else
	#define log(level, fmt, ...) 

	#define _log(level, fmt, ...)
#endif

#define LOGd(fmt, ...) log(DEBUG, fmt, ##__VA_ARGS__)
#define LOGi(fmt, ...) log(INFO, fmt, ##__VA_ARGS__)
#define LOGw(fmt, ...) log(WARN, fmt, ##__VA_ARGS__)
#define LOGe(fmt, ...) log(ERROR, fmt, ##__VA_ARGS__)
#define LOGf(fmt, ...) log(FATAL, fmt, ##__VA_ARGS__)

#if SERIAL_VERBOSITY>DEBUG
#undef LOGd
#define LOGd(fmt, ...)
#endif

#if SERIAL_VERBOSITY>INFO
#undef LOGi
#define LOGi(fmt, ...)
#endif

#if SERIAL_VERBOSITY>WARN
#undef LOGw
#define LOGw(fmt, ...)
#endif

#if SERIAL_VERBOSITY>ERROR
#undef LOGe
#define LOGe(fmt, ...)
#endif

/**
 * General configuration of the serial connection. This sets the pin to be used for UART, the baudrate, the parity 
 * bits, etc.
 */
void config_uart();

/**
 * Write a string to the serial connection. Make sure you end with `\n` if you want to have new lines in the output. 
 * Also flushing the buffer might be done around new lines.
 */
//void write(const char *str);

/**
 * Write a string with printf functionality.
 */
int write(const char *str, ...);

#ifdef __cplusplus
}
#endif
