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
#include "srun_split.h"

void SpeedrunInit()
{
    initscr();
    noecho();
    refresh();
    nodelay(stdscr, TRUE);
}

void SpeedrunRoutine()
{
    struct timespec sleeptime = {0, 1000000};

    int ch;
    
    SpeedrunSplitStart();

    for (;;) {
        
        if ((ch = getch()) != ERR) switch (ch) {
            case '1':
            case 'N':
            case 'n':
                SpeedrunSplitNext();
                break;
            
            case 'U':
            case 'u':
                SpeedrunSplitUndo();
                break;
            
            case '0':
                SpeedrunSplitStart();
                break;
            
            case KEY_F(5):
            case 'R':
            case 'r':
                // SpeedrunSplitDrawEmpty(0);
                break;
                
            case 'Q':
            case 'q':
                return;
                break;
        }
        
        SpeedrunSplitDraw();
        refresh();
        
        nanosleep(&sleeptime, NULL);
    }
}

void SpeedrunEnd()
{
    endwin();
}
