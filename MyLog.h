#ifndef MY_LOG_H
#define MY_LOG_H

#include <stdio.h>
#include <QDebug>
#include <QDateTime>

#define LOG_LEVEL_ERROR     "E"
#define LOG_LEVEL_WARNING   "W"
#define LOG_LEVEL_INFO      "I"
#define LOG_LEVEL_VERBOSE   "V"
#define LOG_LEVEL_DEBUG     "D"

#define CHAR(string) qUtf8Printable(string)

#define AWLOG(level, fmt, arg...)  \
do { \
    QDateTime _dateTime0 = QDateTime::currentDateTime(); \
    QString _date0 = _dateTime0.toString("yyyy-MM-dd"); \
    QString _time0 = _dateTime0.toString("hh:mm:ss.zzz"); \
    char _tempStr0[10240] = {0}; \
    sprintf(_tempStr0, "%s %s %s " fmt, CHAR(_date0), CHAR(_time0), level, ##arg); \
    printf("%s\n", _tempStr0); \
    if (false) { \
        FILE *_fp = fopen("log.log", "ab"); \
        fprintf(_fp, "%s\n", _tempStr0); \
        fflush(_fp); \
        fclose(_fp); \
    } \
} while (0)

#define logv(fmt, arg...) AWLOG(LOG_LEVEL_VERBOSE, fmt, ##arg)
#define logd(fmt, arg...) AWLOG(LOG_LEVEL_DEBUG, fmt, ##arg)
#define logi(fmt, arg...) AWLOG(LOG_LEVEL_INFO, fmt, ##arg)
#define logw(fmt, arg...) AWLOG(LOG_LEVEL_WARNING, fmt, ##arg)
#define loge(fmt, arg...) AWLOG(LOG_LEVEL_ERROR, fmt, ##arg)

#endif // MY_LOG_H
