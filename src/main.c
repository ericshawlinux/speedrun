#include <stdio.h>

#include "command.h"
#include "usage.h"

int main(int argc, const char **argv)
{
    struct Command *cmd = NULL;
    
    if (argc >= 2)
        cmd = GetCommand(argv[1]);
    
    if (cmd == NULL)
        usage_fmt_s(usage_string, argv[0]);
    
    else
        cmd->fn(argc, argv);
    
    return 0;
}
