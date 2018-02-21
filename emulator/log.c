#include "log.h"

void log_init(uint8_t mode)
{
    log_mode = mode;

    if (_log_mode_file())
    {
#ifdef WINDOWS
        fopen_s(&log_file, LOG_FILE, "w");
#else
        log_file = fopen(LOG_FILE, "w");
#endif
    }
}

void log_destroy()
{
    if (_log_mode_file())
    {
        fclose(log_file);
    }
}

void log_set_level(uint8_t level)
{
    log_current = level;
}

void log_message(const char* msg, ...)
{
   char buffer[0xFF];
   va_list argptr;
   va_start(argptr, msg);
#ifdef WINDOWS
   vsprintf_s(buffer, 0xFF, msg, argptr);
#else
   vsprintf(buffer, msg, argptr);
#endif
   _log_l(LOG_MESSAGE, buffer);
   va_end(argptr);
}

void log_error(const char* msg, ...)
{
    char buffer[0xFF];
    va_list argptr;
    va_start(argptr, msg);
#ifdef WINDOWS
    vsprintf_s(buffer, 0xFF, msg, argptr);
#else
    vsprintf(buffer, msg, argptr);
#endif
    _log_l(LOG_ERROR, buffer);
    va_end(argptr);
}

void log_debug(const char * msg, ...)
{
    char buffer[0xFF];
    va_list argptr;
    va_start(argptr, msg);
#ifdef WINDOWS
    vsprintf_s(buffer, 0xFF, msg, argptr);
#else
    vsprintf(buffer, msg, argptr);
#endif
    _log_l(LOG_DEBUG, buffer);
    va_end(argptr);
}

void log_cpu(const char* msg, ...)
{
    char buffer[0xFF];
    va_list argptr;
    va_start(argptr, msg);
#ifdef WINDOWS
    vsprintf_s(buffer, 0xFF, msg, argptr);
#else
    vsprintf(buffer, msg, argptr);
#endif
    _log_m("CPU", buffer);
    va_end(argptr);
}

// Currently all logs go to stdout, but this method will also be able to send it
// somewhere else
void _log_m(const char* ch, const char * msg)
{
    if (_log_mode_stdout())
        printf(" [%s] %s\n", ch, msg);

    if (_log_mode_file())
        fprintf(log_file, " [%s] %s\n", ch, msg);
}

void _log_l(uint8_t level, const char * msg)
{
    if (log_current > level)
        return;

    _log_m(LEVELS[level], msg);
}
