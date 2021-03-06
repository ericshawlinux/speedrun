/* srun_stopwatch.h
 *  
 * Created by Eric Shaw Jr on 2018-03-23
 * Copyright (c) 2018 Eric Shaw Jr.
 * 
 * This file is part of speedrun. It is subject to the license terms
 * in the LICENSE file found in the top-level directory of this distribution.
 * No part of speedrun, including this file, may be copied, modified, propagated,
 * or distributed except according to the terms contained in the LICENSE file.
 */

#include <time.h>
 
#ifndef SRUN_STOPWATCH_DEFINED
#define SRUN_STOPWATCH_DEFINED

struct srun_time {
    int hours;
    int minutes;
    int seconds;
    int milliseconds;
};

struct srun_stopwatch {
    struct timespec start;
    int hours;
    int minutes;
    int seconds;
    int milliseconds;
};

struct srun_stopwatch srun_stopwatch_start();
void srun_stopwatch_tick_time(struct srun_stopwatch *);

#endif
