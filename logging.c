#include <syslog.h>
#include <stdarg.h>

#include "common_headers.h"
#include "logging.h"

static void WriteToSysLog(LOGLEVEL logLevel, char *message);
static void WriteToTerminal(LOGLEVEL logLevel, char *message);

void WriteToLog(LOGLEVEL logLevel, char *format, ...)
{
    char message[1024] = { 0 };
    va_list argList;

    va_start(argList, format);
    char *string = va_arg(argList, char *);
    va_end(argList);

    snprintf(message, 1024, format, string);

    switch (rMode)
    {
    case FOREGROUND:
        WriteToTerminal(logLevel, message);
        break;
    case BACKGROUND:
        WriteToSysLog(logLevel, message);
        break;
    }
}

static void WriteToSysLog(LOGLEVEL logLevel, char *message)
{
    openlog("DMServer", LOG_PID, LOG_USER);

    switch(logLevel)
    {
    case INFORMATION:
        syslog(LOG_INFO, "%s", message);
        break;
    case WARNING:
        syslog(LOG_WARNING, "%s", message);
        break;
    case ERROR:
        syslog(LOG_ERR, "%s", message);
        break;
    }

    closelog();
}

static void WriteToTerminal(LOGLEVEL logLevel, char *message)
{
    switch(logLevel)
    {
    case INFORMATION:
        fprintf(stderr, "\x1b[1m\x1b[36m%s\x1b[0m\n", message);
        break;
    case WARNING:
        fprintf(stderr, "\x1b[1m\x1b[33m%s\x1b[0m\n", message);
        break;
    case ERROR:
        fprintf(stderr, "\x1b[1m\x1b[31m%s\x1b[0m\n", message);
        break;
    }
}
