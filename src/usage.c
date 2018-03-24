/* usage.c
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
#include <malloc.h>
#include <string.h>

#include "usage.h"

const char *usage_string = "usage: %s <command> <options>";

void usage_fmt_s(const char *fmt, const char *arg1)
{
    char *usage_complete = malloc(strlen(fmt) + strlen(arg1) + 1);
    if (usage_complete == NULL)
        return;
    sprintf(usage_complete, fmt, arg1);
    puts(usage_complete);
    free(usage_complete);
}
