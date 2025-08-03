#ifndef _LOG_H_
#define _LOG_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LOG_FILE "log.txt"

#define LOG_MODE_STDOUT 0x01
#define LOG_MODE_FILE 0x02

enum
{
  LOG_VERBOSE = 0,
  LOG_DEBUG,
  LOG_MESSAGE,
  LOG_ERROR,
};

static const uint8_t* LEVELS[4] = {"VERBOSE", "DEBUG", "MESSAGE", "ERROR"};
static uint8_t log_current;
static uint8_t log_mode;
static FILE* log_file;

void log_init(uint8_t mode);
void log_destroy();

static inline bool _log_mode_stdout() { return log_mode & LOG_MODE_STDOUT; }
static inline bool _log_mode_file() { return log_mode & LOG_MODE_FILE; }

void log_set_level(uint8_t level);

void log_message(const char* msg, ...);
void log_debug(const char* msg, ...);
void log_error(const char* msg, ...);
void log_cpu(const char* msg, ...);

static void _log_l(uint8_t level, const char* msg);
static void _log_m(const char* ch, const char* msg);

#endif
