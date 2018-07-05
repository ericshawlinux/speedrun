# Makefile
# 
# Created by Eric Shaw Jr on 2018-03-23
# Copyright (c) 2018 Eric Shaw Jr.
#
# This file is part of speedrun. It is subject to the license terms
# in the LICENSE file found in the top-level directory of this distribution.
# No part of speedrun, including this file, may be copied, modified, propagated,
# or distributed except according to the terms contained in the LICENSE file.

CC       := gcc
CFLAGS   := -Wall -Wextra -Werror -g
LIBRARYS := -lncurses
INCLUDES := -I./include
OBJECTS  := obj/srun_split.o obj/srun.o obj/srun_stopwatch.o obj/command.o obj/usage.o obj/main.o
PROGRAM  := speedrun

vpath %.c src

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $(PROGRAM) $(LIBRARYS)

obj/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -vf $(PROGRAM) $(OBJECTS)
