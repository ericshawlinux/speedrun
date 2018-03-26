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

static struct srun_stopwatch stopwatch = {0};

static struct srun_split    *splits = NULL;
static int                  splits_count = 0;
static int                  current_split_idx = 0;
static size_t               split_name_width = 0;

#define MAX_SPLIT_NAME_LENGTH 100

int SpeedrunSplitLoadFromDisk(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    
    if (fp == NULL) {
        perror("SpeedrunSplitLoadFromDisk");
        return 0;
    }
    
    char buffer[MAX_SPLIT_NAME_LENGTH] = {0};
    
    while (fgets(buffer, MAX_SPLIT_NAME_LENGTH, fp) != NULL) {
        
        struct srun_split current_split = {0};
        
        size_t size = strlen(buffer) + 1;
        buffer[strcspn(buffer, "\r\n")] = 0;
        splits_count += 1;
        
        splits = realloc(splits, splits_count * sizeof current_split);
        
        if (splits == NULL) {
            perror("SpeedrunSplitLoadFromDisk realloc");
            return 0;
        }
        
        int idx = splits_count - 1;
        splits[idx].name = malloc(size);
        
        if (splits[idx].name == NULL) {
            perror("SpeedrunSplitLoadFromDisk malloc");
            return 0;
        }
        
        strncpy(splits[idx].name, buffer, size);
        
        if (split_name_width < size)
            split_name_width = size;
    }
    
    return 1;
}

void SpeedrunSplitStart()
{
    current_split_idx = 0;
    SpeedrunSplitDrawEmpty(0);
    stopwatch = SpeedrunStopwatchStart();
}

void SpeedrunSplitNext()
{
    int max_split = splits_count - 1;
    current_split_idx = (current_split_idx >= max_split ? max_split : current_split_idx + 1);
}

void SpeedrunSplitUndo()
{
    current_split_idx = (current_split_idx <= 0 ? 0 : current_split_idx - 1);
    SpeedrunSplitDrawEmpty(current_split_idx);
}

void SpeedrunSplitDrawEmpty(int start)
{
    int i;
    
    for (i = start; i < (int) splits_count; i++)
        mvprintw(i, 0, "%-*s %11c  ", split_name_width, splits[i].name, '-');
    
    refresh();
}

void SpeedrunSplitDraw()
{
    if (current_split_idx >= splits_count) {
        mvprintw(0, 0, "no splits defined ");
        return;
    }
    SpeedrunStopwatchTickTime(&stopwatch);
    mvprintw(current_split_idx, 0, "%-*s %02d:%02d:%02d.%03d  ", split_name_width, splits[current_split_idx].name, stopwatch.hours, stopwatch.minutes, stopwatch.seconds, stopwatch.milliseconds);
}
