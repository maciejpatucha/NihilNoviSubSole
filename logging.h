#ifndef LOGGING_H
#define LOGGING_H

typedef enum {
    INFORMATION,
    WARNING,
    ERROR
} LOGLEVEL;

void WriteToLog(LOGLEVEL logLevel, char *format, ...);

#endif // LOGGING_H

