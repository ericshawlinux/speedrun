#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "usage.h"

#include "srun.h"

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

}
