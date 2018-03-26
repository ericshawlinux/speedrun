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
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "srun_split.h"
#include "srun_stopwatch.h"

static int current_split = 0;

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static char **splits = NULL;

static int splits_length = 0;

static size_t longest_split_name = 0;

#define MAX_SPLIT_LENGTH 100

int SpeedrunSplitLoadFromDisk(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    
    if (fp == NULL) {
        perror("SpeedrunSplitLoadFromDisk");
        return 0;
    }
    
    char buffer[MAX_SPLIT_LENGTH] = {0};
    
    while (fgets(buffer, MAX_SPLIT_LENGTH, fp) != NULL) {
        size_t size = strlen(buffer) + 1;
        buffer[strcspn(buffer, "\r\n")] = 0;
        splits_length += 1;
        splits = realloc(splits, splits_length * sizeof (char*));
        
        if (splits == NULL) {
            perror("SpeedrunSplitLoadFromDisk realloc");
            return 0;
        }
        
        int idx = splits_length - 1;
        splits[idx] = malloc(size);
        
        if (splits[idx] == NULL) {
            perror("SpeedrunSplitLoadFromDisk malloc");
            return 0;
        }
        
        strncpy(splits[idx], buffer, size);
        
        if (longest_split_name < size)
            longest_split_name = size;
    }
    
    return 1;
}

void SpeedrunSplitStart()
{
    current_split = 0;
    SpeedrunSplitDrawEmpty(0);
    SpeedrunStopwatchStart();
}

void SpeedrunSplitNext()
{
    int max_split = splits_length - 1;
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
    
    for (i = start; i < (int) splits_length; i++)
        mvprintw(i, 0, "%-*s %11c  ", longest_split_name, splits[i], '-');
    
    refresh();
}

void SpeedrunSplitDraw()
{
    if (current_split >= splits_length) {
        mvprintw(0, 0, "no splits defined ");
        return;
    }
    int hours, minutes, seconds, milliseconds;
    SpeedrunStopwatchGetTime(&hours, &minutes, &seconds, &milliseconds);
    mvprintw(current_split, 0, "%-*s %02d:%02d:%02d.%03d  ", longest_split_name, splits[current_split], hours, minutes, seconds, milliseconds);
}
