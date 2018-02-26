#include "datetime.h"

#include <util/system/yassert.h>
#include <util/system/platform.h>
#include <util/datetime/systime.h>

#include <time.h>
#include <errno.h>
#include <string.h>

ui64 ToMicroSeconds(const struct timeval& tv) {
    return (ui64) tv.tv_sec * 1000000 + (ui64) tv.tv_usec;
}

#if defined _linux_ || defined _freebsd_
ui64 ToMicroSeconds(const struct timespec& ts) {
    return (ui64) ts.tv_sec * 1000000 + (ui64) ts.tv_nsec / 1000;
}
#endif

#if defined _win_
ui64 ToMicroSeconds(const FILETIME& ft) {
    return (((ui64)ft.dwHighDateTime << 32) + (ui64)ft.dwLowDateTime) / (ui64)10;
}
#endif

ui64 millisec() {
    return MicroSeconds() / (ui64)1000;
}

ui64 MicroSeconds() {
    struct timeval tv;
    gettimeofday(&tv, 0);

    return ToMicroSeconds(tv);
}

ui64 ThreadCPUUserTime() {
#if defined _win_
    FILETIME creationTime, exitTime, kernelTime, userTime;
    GetThreadTimes(GetCurrentThread(), &creationTime, &exitTime, &kernelTime, &userTime);
    return ToMicroSeconds(userTime);
#else
    return 0;
#endif
}

ui64 ThreadCPUSystemTime() {
#if defined _win_
    FILETIME creationTime, exitTime, kernelTime, userTime;
    GetThreadTimes(GetCurrentThread(), &creationTime, &exitTime, &kernelTime, &userTime);
    return ToMicroSeconds(kernelTime);
#else
    return 0;
#endif
}

ui64 ThreadCPUTime() {
#if defined _win_
    FILETIME creationTime, exitTime, kernelTime, userTime;
    GetThreadTimes(GetCurrentThread(), &creationTime, &exitTime, &kernelTime, &userTime);
    return ToMicroSeconds(userTime) + ToMicroSeconds(kernelTime);
#elif defined _darwin_
    return 0; // no clock_gettime on MacOS, and no way at all to get per-thread CPU times
#else
    struct timespec ts;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
    return ToMicroSeconds(ts);
#endif
}

ui32 Seconds() {
    struct timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec;
}

void NanoSleep(ui64 ns) {
#ifdef _win_
    Sleep(ns / 1000000);
#else
    const ui64 NS = 1000 * 1000 * 1000;
    struct timespec req;
    req.tv_sec = ns / NS;
    req.tv_nsec = ns % NS;
    struct timespec left;
    while (nanosleep(&req, &left) < 0) {
        YASSERT(errno == EINTR);
        req = left;
    }
#endif
}
