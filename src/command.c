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
#include "srun_timer.h" // for TestCommand
#include <time.h> // for nanosleep

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static struct Command Commands[] =
{
    {"help", HelpCommand},
    {"stub", StubCommand},
    {"test", TestCommand},
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

void StubCommand(int argc __attribute__((unused)), const char **argv __attribute__((unused)))
{
    SpeedrunInit();
    SpeedrunRoutine();
    SpeedrunEnd();
}

void TestCommand(int argc __attribute__((unused)), const char **argv __attribute__((unused)))
{
    struct timespec sleeptime = {0, 1000000};
    
    SpeedrunSetTimerStart();
    char time[1024] = {0};
    
    while(1) {
        SpeedrunGetTimeString(time, 1024);
        printf("%s\n", time);
        nanosleep(&sleeptime, NULL);
    }
}
