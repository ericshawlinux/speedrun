/* srun.c
 *  
 * Created by Eric Shaw Jr on 2018-03-23
 * Copyright (c) 2018 Eric Shaw Jr.
 * 
 * This file is part of speedrun. It is subject to the license terms
 * in the LICENSE file found in the top-level directory of this distribution.
 * No part of speedrun, including this file, may be copied, modified, propagated,
 * or distributed except according to the terms contained in the LICENSE file.
 */

#include <curses.h>
#include <time.h> // for nanosleep

#include "srun.h"
#include "srun_stopwatch.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static char *TestSplits[] = {
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

int current_split = 0;

void SpeedrunInit()
{
    initscr();
    noecho();
    refresh();
    SpeedrunDrawSplits(0);
    SpeedrunStopwatchStart();
}

void SpeedrunRoutine()
{
    struct timespec sleeptime = {0, 1000000};

    int ch;
    nodelay(stdscr, TRUE);

    for (;;) {
        
        if ((ch = getch()) != ERR) switch (ch) {
            case '1':
            case 'N':
            case 'n':
                current_split += (current_split >= (int) ARRAY_SIZE(TestSplits) - 1 ? 0 : 1);
                break;
            
            case 'U':
            case 'u':
                current_split -= (current_split <= 0 ? 0 : 1);
                SpeedrunDrawSplits(current_split);
                break;
            
            case '0':
                current_split = 0;
                SpeedrunDrawSplits(0);
                SpeedrunStopwatchStart();
                break;
            
            case KEY_F(5):
            case 'R':
            case 'r':
                SpeedrunDrawSplits(current_split);
                break;
                
            case 'Q':
            case 'q':
                return;
                break;
        }
        
        SpeedrunUpdateSplit(current_split);
        refresh();
        
        // this program is resource intensive in a way so slow it down to conserve energy.
        // still screaming fast.
        nanosleep(&sleeptime, NULL);
    }
}

void SpeedrunEnd()
{
    endwin();
}

void SpeedrunDrawSplits(int start)
{
    int i;
    
    for (i = start; i < (int) ARRAY_SIZE(TestSplits); i++)
        mvprintw(i, 0, "%-15s %11c  ", TestSplits[i], '-');
    
    refresh();
}

void SpeedrunUpdateSplit(int split)
{
    int hours, minutes, seconds, milliseconds;
    SpeedrunStopwatchGetTime(&hours, &minutes, &seconds, &milliseconds);
    mvprintw(split, 0, "%-15s %02d:%02d:%02d.%03d  ", TestSplits[split], hours, minutes, seconds, milliseconds);
}
