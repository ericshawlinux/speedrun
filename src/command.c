/* command.c
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
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "usage.h"

#include "srun.h"
#include "srun_split.h"
#include "srun_stopwatch.h" // for TestCommand
#include <time.h> // for nanosleep

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static struct Command Commands[] =
{
    {"help",    HelpCommand},
    {"start",   StartCommand},
    {"stub",    StubCommand},
    {"test",    TestCommand},
};

struct Command *GetCommand(const char *s)
{
    unsigned int i;
    for(i = 0; i < ARRAY_SIZE(Commands); i++) {
        struct Command *p = Commands + i;
        if (!strcmp(s, p->name))
            return p;
    }
    return NULL;
}

void HelpCommand(int argc __attribute__((unused)), const char **argv __attribute__((unused)))
{
    usage_fmt_s(usage_string, argv[0]);
}

void StartCommand(int argc, const char **argv)
{
    const char *filename = "default-splits.txt";
    
    if (argc == 3) {
        filename = argv[2];
    }
    else if (argc > 3) {
        usage_fmt_s(usage_string, argv[0]);
        return;
    }

    SpeedrunInit();
    if (SpeedrunSplitLoadFromDisk(filename))
        SpeedrunRoutine();
    SpeedrunEnd();
}

void StubCommand(int argc __attribute__((unused)), const char **argv __attribute__((unused)))
{
    
}

void TestCommand(int argc __attribute__((unused)), const char **argv __attribute__((unused)))
{
    struct timespec sleeptime = {0, 1000000};
    
    SpeedrunStopwatchStart();
    
    int hours, minutes, seconds, milliseconds;
    
    while(1) {
        SpeedrunStopwatchGetTime(&hours, &minutes, &seconds, &milliseconds);
        printf("%02d:%02d:%02d.%03d\n", hours, minutes, seconds, milliseconds);
        nanosleep(&sleeptime, NULL);
    }
}
