#include "csapp.h"

// #define MAXLINE 100
#define MAXARGS 128 // appropriate .h files to
// char **environ;
// be included before this
void eval(char *cmdline); // function prototypes
int parseline(char *buf, char *argv[]);
int builtin_command(char *argv[]);
int main()
{
    char cmdline[MAXLINE];

    while (1)
    {
        printf("Ready>");
        fgets(cmdline, MAXLINE, stdin); // Read commandline
        if (feof(stdin))
            exit(0);
        eval(cmdline); // evaluate the commandline
    }
}

void eval(char *cmdline)
{
    char *argv[MAXARGS]; // Argument list execve()
    // char *envp[MAXARGS];
    char buf[MAXLINE]; // holds modified command line
    int bg;            /* background job? */
    pid_t pid;         // process id

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if (argv[0] == NULL)
        return;
    if (!builtin_command(argv))
    { // expecting users executable
        if ((pid = fork()) == 0)
        { // let the child runs user program
            if (execve(argv[0], argv, environ) < 0)
            {
                printf("Command not found\n");
                exit(0);
            }
        }
        if (!bg)
        {
            int status;
            if (waitpid(pid, &status, 0) < 0)
                printf("waitpid error\n");
        }
        else
            printf("%d %s ", pid, cmdline);
    }
    return;
}

int builtin_command(char *argv[])
{
    if (!strcmp(argv[0], "quit"))
    {
        printf("done\n");
        exit(0);
    }
    if (!strcmp(argv[0], "&"))
        return 1;
    return 0; // not a built-in command
}

int parseline(char *buf, char *argv[])
{
    // parse command line and build argv array
    char *delim; /* points to first space delim.*/
    int argc;
    int bg;
    buf[strlen(buf) - 1] = ' ';
    while (*buf && (*buf == ' '))
        buf++; // skip past leading spaces
    argc = 0;  // build argvs’
    while ((delim = strchr(buf, ' ')))
    {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' '))
            buf++;
    } // skip past trailing
    argv[argc] = NULL;
    if (argc == 0)
        return 1; // ignore blank line
    if ((bg = (*argv[argc - 1] == '&')) != 0)
        // should job in the bg mode
        argv[--argc] = NULL;
    return bg;
}
