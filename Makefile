CC       := gcc
CFLAGS   := -Wall -Wextra -Werror
LIBRARYS := -lncurses
INCLUDES := -I./include
OBJECTS  := obj/srun.o obj/srun_timer.o obj/command.o obj/usage.o obj/main.o
PROGRAM  := speedrun

vpath %.c src

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $(PROGRAM) $(LIBRARYS)

obj/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -vf $(PROGRAM) $(OBJECTS)
