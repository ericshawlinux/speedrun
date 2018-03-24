/* command.h
 *  
 * Created by Eric Shaw Jr on 2018-03-23
 * Copyright (c) 2018 Eric Shaw Jr.
 * 
 * This file is part of speedrun. It is subject to the license terms
 * in the LICENSE file found in the top-level directory of this distribution.
 * No part of speedrun, including this file, may be copied, modified, propagated,
 * or distributed except according to the terms contained in the LICENSE file.
 */

#ifndef COMMAND_DEFINED
#define COMMAND_DEFINED

struct Command
{
    const char *name;
    void (*fn)(int argc, const char **argv);
};

struct Command *GetCommand(const char *s);
void HelpCommand(int argc, const char **argv);
void StubCommand(int argc, const char **argv);
void TestCommand(int argc, const char **argv);

#endif // Command.h included
