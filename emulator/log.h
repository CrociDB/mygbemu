#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

enum
{
    LOG_VERBOSE = 0,
    LOG_MESSAGE,
    LOG_ERROR,
};

static const uint8_t* LEVELS[3] = {"VERBOSE", "MESSAGE", "ERROR"};
static uint8_t log_current;

void log_set_level(uint8_t level);

void log_message(const char* msg, ...);
void log_error(const char* msg, ...);
void log_cpu(const char* msg, ...);

static void _log_l(uint8_t level, const char* msg, ...);
static void _log_m(const char* ch, const char* msg, ...);

#endif
