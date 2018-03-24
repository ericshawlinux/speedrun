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
