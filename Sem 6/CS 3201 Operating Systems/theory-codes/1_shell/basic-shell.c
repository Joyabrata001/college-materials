#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>
#include <stdbool.h>

#define MAXLINE 256 //max line length
#define MAXARGS 128 //max number of auguments

void eva(char *cmdline);                 //evaluates and executes the command
bool parseline(char *buf, char *argv[]); // parses the command given and saves it into char* argv[]
bool builtin_command(char *argv[]);      //checks if a given command in one of the buitlin "quit" or not

int main()
{
    char cmdline[MAXLINE];

    while (true)
    {
        printf("Ready>");
        fgets(cmdline, MAXLINE, stdin); // read commandline

        if (feof(stdin))
            exit(0);

        eva(cmdline); // evaluate the commandline
    }
}

bool builtin_command(char *argv[])
{
    if (strcmp(argv[0], "quit") == 0)
        exit(0);

    if (strcmp(argv[0], "&") == 0)
        return true;

    return false; // not a built-in command
}

void eva(char *cmdline)
{

    char *argv[MAXARGS]; // argument list execve()
    char buf[MAXLINE];   // holds modified commandline
    bool bg;             // background job?
    pid_t pid;           // process id

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);

    if (argv[0] == NULL || argv[0][0] == ' ') //' ' can happen if we provide "\n" only
        return;

    if (!builtin_command(argv)) // expecting user executable
    {
        pid = fork();
        if (pid == 0) // let the child run the user program
        {
            int status = execve(argv[0], argv, __environ);
            // printf("%d", status);
            if (status < 0)
                printf("%s: Command not found\n", argv[0]);
            exit(0);
        }

        if (!bg)
        {
            int status;
            if (waitpid(pid, &status, 0) < 0)
                fprintf(stderr, "waitpid error\n");
            // unix_error("waitpid error");
        }
        else
            printf("%d %s", pid, cmdline); // if command line has '&' in the end
    }
    return;
}

bool parseline(char *buf, char *argv[]) // parse command line and build argv array
{
    char *delim; // points to first space delim
    int argc;
    bool bg;

    buf[strlen(buf) - 1] = ' '; // replace trailing '\n' with space

    while (buf && (*buf == ' '))
        buf++; // skip past leading spaces

    argc = 0; // build argv's

    while ((delim = strchr(buf, ' ')))
    {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;

        while (buf && (*buf == ' '))
            buf++; // skips past trailing space
    }

    argv[argc] == NULL;

    if (argc == 0)
        return true; // ignore blank line

    bg = (*argv[argc - 1] == '&'); // appending command with & -> do the work in background

    if (bg == true) // should job in the bg mode delete the last parameter '&'
        argv[--argc] = NULL;

    return bg;
}