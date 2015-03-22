#ifndef GDM_TIMEUTILS
#define GDM_TIMEUTILS

#include <sys/time.h>
#include <string>
#include <sstream>

namespace gdm
{

typedef uint64_t gdmtime_t;

static gdmtime_t getTimeNow() {
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*1000000+tv.tv_usec;
}

static std::string getTimeAsStr(gdmtime_t time)
{
    int sec = time/1000000;
    int msec = time%1000000;
    std::ostringstream oss;
    oss << sec << "." << msec;
    return oss.str();

}

static std::string getTimeNowAsStr()
{
    gdmtime_t time = getTimeNow();
    int sec = time/1000000;
    int msec = time%1000000;
    std::ostringstream oss;
    oss << sec << "." << msec;
    return oss.str();

}



} // close namespace gdm


#endif

