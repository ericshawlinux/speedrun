/* srun_timer.c
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

#include "srun_timer.h"

#define SECONDS_PER_MINUTE  60
#define SECONDS_PER_HOUR    (SECONDS_PER_MINUTE * 60)
#define MSECONDS_PER_SECOND 1000000

static struct timespec start = {0};

void SpeedrunSetTimerStart()
{
    clock_gettime(CLOCK_MONOTONIC, &start);
}

void SpeedrunGetTimeString(char *destination, size_t max_size)
{
    int hours, minutes, seconds, milliseconds;
    
    struct timespec now = {0};
    
    clock_gettime(CLOCK_MONOTONIC, &now);
    
    struct timespec diff = {now.tv_sec - start.tv_sec, now.tv_nsec};
    
    SpeedrunSimplestFormFromSeconds(diff, &hours, &minutes, &seconds, &milliseconds);
    
    snprintf(destination, max_size, "%02d:%02d:%02d.%03d", hours, minutes, seconds, milliseconds);
}

void SpeedrunSimplestFormFromSeconds(struct timespec time, int *hours, int *minutes, int *seconds, int *milliseconds)
{
    *hours          = (int) (time.tv_sec / SECONDS_PER_HOUR);
    *minutes        = (int) (time.tv_sec / SECONDS_PER_MINUTE);
    *seconds        = (int) (time.tv_sec - *hours * SECONDS_PER_HOUR - *minutes * SECONDS_PER_MINUTE);
    *milliseconds   = (int) (time.tv_nsec / MSECONDS_PER_SECOND);
}
