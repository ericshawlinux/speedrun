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
#include <string.h>

#include "srun_stopwatch.h"

#define SECONDS_PER_MINUTE  60
#define SECONDS_PER_HOUR    (SECONDS_PER_MINUTE * 60)
#define NANOS_PER_MSECOND   1000000

static struct timespec start = {0};

void SpeedrunStopwatchStart()
{
    clock_gettime(CLOCK_MONOTONIC, &start);
}

void SpeedrunStopwatchGetTime(int *hours, int *minutes, int *seconds, int *milliseconds)
{
    struct timespec now = {0};
    
    clock_gettime(CLOCK_MONOTONIC, &now);
    
    struct timespec currtime = {now.tv_sec - start.tv_sec, now.tv_nsec};
    
    *hours          = (int) (currtime.tv_sec / SECONDS_PER_HOUR);
    *minutes        = (int) (currtime.tv_sec / SECONDS_PER_MINUTE);
    *seconds        = (int) (currtime.tv_sec - *hours * SECONDS_PER_HOUR - *minutes * SECONDS_PER_MINUTE);
    *milliseconds   = (int) (currtime.tv_nsec / NANOS_PER_MSECOND);
}
