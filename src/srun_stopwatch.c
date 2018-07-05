/* srun_stopwatch.c
 *  
 * Created by Eric Shaw Jr on 2018-03-23
 * Copyright (c) 2018 Eric Shaw Jr.
 * 
 * This file is part of speedrun. It is subject to the license terms
 * in the LICENSE file found in the top-level directory of this distribution.
 * No part of speedrun, including this file, may be copied, modified, propagated,
 * or distributed except according to the terms contained in the LICENSE file.
 */

#include <stdio.h>
#include <time.h>

#include "srun_stopwatch.h"

#define SECONDS_PER_MINUTE  60
#define SECONDS_PER_HOUR    (SECONDS_PER_MINUTE * 60)
#define NANOS_PER_MSECOND   1000000
#define NANOS_PER_SECOND    NANOS_PER_MSECOND * 1000

struct srun_stopwatch srun_stopwatch_start()
{
    struct srun_stopwatch stopwatch = {0};
    clock_gettime(CLOCK_MONOTONIC, &(stopwatch.start));
    return stopwatch;
}

void srun_stopwatch_tick_time(struct srun_stopwatch *stopwatch)
{
    struct timespec now = {0};
    clock_gettime(CLOCK_MONOTONIC, &now);
    
    struct timespec currtime = {
        now.tv_sec - stopwatch->start.tv_sec,
        now.tv_nsec - stopwatch->start.tv_nsec
    };
    
    if (currtime.tv_nsec < 0) {
        currtime.tv_sec -= 1;
        currtime.tv_nsec = NANOS_PER_SECOND + currtime.tv_nsec;
    }
    
    stopwatch->hours        = (int) (currtime.tv_sec / SECONDS_PER_HOUR);
    stopwatch->minutes      = (int) (currtime.tv_sec / SECONDS_PER_MINUTE);
    stopwatch->seconds      = (int) (currtime.tv_sec - stopwatch->hours * SECONDS_PER_HOUR - stopwatch->minutes * SECONDS_PER_MINUTE);
    stopwatch->milliseconds = (int) (currtime.tv_nsec / NANOS_PER_MSECOND);
}
