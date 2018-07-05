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

static struct srun_command commands[] =
{
    {"help",    srun_help_command},
    {"start",   srun_start_command},
    {"stub",    srun_stub_command},
    {"test",    srun_test_command},
};

struct srun_command *get_command(const char *s)
{
    unsigned int i;
    for(i = 0; i < ARRAY_SIZE(commands); i++) {
        struct srun_command *p = commands + i;
        if (!strcmp(s, p->name))
            return p;
    }
    return NULL;
}

void srun_help_command(int argc __attribute__((unused)), const char **argv __attribute__((unused)))
{
    usage_fmt_s(usage_string, argv[0]);
}

void srun_start_command(int argc, const char **argv)
{
    const char *filename = "default-splits.txt";
    
    if (argc == 3) {
        filename = argv[2];
    }
    else if (argc > 3) {
        usage_fmt_s(usage_string, argv[0]);
        return;
    }

    srun_init();
    if (srun_split_load_from_disk(filename))
        srun_routine();
    srun_end();
}

void srun_stub_command(int argc __attribute__((unused)), const char **argv __attribute__((unused)))
{
    
}

void srun_test_command(int argc __attribute__((unused)), const char **argv __attribute__((unused)))
{
    struct timespec sleeptime = {0, 1000000};
    struct srun_stopwatch stopwatch = srun_stopwatch_start();
    struct srun_stopwatch *s = &stopwatch;
    
    while(1) {
        srun_stopwatch_tick_time(s);
        printf("%02d:%02d:%02d.%03d\n", s->hours, s->minutes, s->seconds, s->milliseconds);
        nanosleep(&sleeptime, NULL);
    }
}
