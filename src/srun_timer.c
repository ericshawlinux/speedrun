#include <stdio.h>
#include <time.h>
#include <string.h>

static struct timespec start = {0};

void SpeedrunSetTimerStart()
{
    clock_gettime(CLOCK_MONOTONIC, &start);
}

void SpeedrunGetTimeString(char *destination, size_t max_size)
{
    // timespecs are used for getting nanoseconds. which need converted to milliseconds later.
    struct timespec now = {0};
    // get some arbitrary time that represents now. CLOCK_MONOTONIC has a resolution of 1 nanosecond!
    clock_gettime(CLOCK_MONOTONIC, &now);
    
    // ts and buf are used for getting the time with a mere 1 second resolution
    struct tm *ts;
    char buf[15];
    
    // get the differene between now, and whatever start has been set to.
    time_t diff = now.tv_sec - start.tv_sec;
    
    // get the time as a string hh:mm:ss and store it in buf
    ts = gmtime(&diff);
    strftime(buf, sizeof(buf), "%H:%M:%S", ts);
    
    // get the thousandth of a second aka milliseconds. 0.001
    long milliseconds = now.tv_nsec / 1000000;
    
    // combine hh:mm:ss and computed milliseconds then return it.
    snprintf(destination, max_size, "%s.%03ld", buf, milliseconds);
}
