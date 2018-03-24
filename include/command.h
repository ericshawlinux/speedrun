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
