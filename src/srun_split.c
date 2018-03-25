/* srun_split.c
 *  
 * Created by Eric Shaw Jr on 2018-03-25
 * Copyright (c) 2018 Eric Shaw Jr.
 * 
 * This file is part of speedrun. It is subject to the license terms
 * in the LICENSE file found in the top-level directory of this distribution.
 * No part of speedrun, including this file, may be copied, modified, propagated,
 * or distributed except according to the terms contained in the LICENSE file.
 */

#include <curses.h>

#include "srun_split.h"
#include "srun_stopwatch.h"

static int current_split = 0;

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static char *test_splits[] = {
    "Torture Skip",
    "Exit Torture",
    "Comm Twr A",
    "Wolf 2",
    "Raven 2",
    "PAL Card",
    "PAL Card (Hot)",
    "MG REX",
    "Liquid",
    "Escape",
    "Score"
};

void SpeedrunSplitStart()
{
    current_split = 0;
    SpeedrunSplitDrawEmpty(0);
    SpeedrunStopwatchStart();
}

void SpeedrunSplitNext()
{
    int max_split = ARRAY_SIZE(test_splits) - 1;
    current_split = (current_split >= max_split ? max_split : current_split + 1);
}

void SpeedrunSplitUndo()
{
    current_split = (current_split <= 0 ? 0 : current_split - 1);
    SpeedrunSplitDrawEmpty(current_split);
}


void SpeedrunSplitDrawEmpty(int start)
{
    int i;
    
    for (i = start; i < (int) ARRAY_SIZE(test_splits); i++)
        mvprintw(i, 0, "%-15s %11c  ", test_splits[i], '-');
    
    refresh();
}

void SpeedrunSplitDraw()
{
    int hours, minutes, seconds, milliseconds;
    SpeedrunStopwatchGetTime(&hours, &minutes, &seconds, &milliseconds);
    mvprintw(current_split, 0, "%-15s %02d:%02d:%02d.%03d  ", test_splits[current_split], hours, minutes, seconds, milliseconds);
}
