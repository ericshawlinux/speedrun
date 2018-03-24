/* main.c
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
