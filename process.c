#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "process.h"
#include "prompt.h"
#include "sighan.h"
#include "jobs.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int foreground(char *args[], int flag)
{
    int pipefd1[2];
    pipe(pipefd1);
    char ok[10] = "ok";
    char aok[10] = "a";
    char test[20] = "";
    //char time[100];
    int *wstatus;
    int k, e;
    wstatus = &k;
    write(pipefd1[1], aok, 1);
    int id = fork();
    runpid = id;
    strcpy(runningprocess, args[0]);
    if (id == 0)
    {
        close(pipefd[1][1]);
        close(pipefd[0][0]);
        if (flag == 1)
        {
            dup2(pipefd[0][1], 1);
        }
        else if (flag == 2)
        {
            dup2(pipefd[0][1], 1);
            dup2(pipefd[1][0], 0);
        }
        else if (flag == 3)
        {
            dup2(pipefd[1][0], 0);
        }
        signal(SIGINT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
        e = execvp(args[0], args);
        if (e < 0)
        {
            printf("%s: command not found\n", args[0]);
            write(pipefd1[1], ok, 2);
        }
        exit(0);
    }
    else
    {
        waitpid(id, wstatus, 0 | WUNTRACED);
        runpid = 0;
        read(pipefd1[0], test, 100);
        // printf("%s", test);
        close(pipefd1[0]);
        close(pipefd1[1]);
        //close(pipefd[1][0]);
        //close(pipefd[0][1]);
        if (flag == 1)
        {
            read(pipefd[0][0], inout, 900000);
            //printf("%s", inout);
            write(pipefd[1][1], inout, sizeof(inout));
        }
        else if (flag == 2)
        {
            read(pipefd[0][0], inout, 900000);
            // printf("%s", inout);
            write(pipefd[1][1], inout, sizeof(inout));
        }

        if (test[0] == 'a' && test[1] == 'o' && test[2] == 'k')
            return -1;
        else
        {
            //printf("\n");
            return 0;
        }
    }
}
int background(char *args[], int flag)
{

    int *wstatus;
    int k, e;
    wstatus = &k;
    int id = fork();
    //int id2;
    addnode(args[0], id, "running");
    if (id == 0)
    {

        signal(SIGINT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
        e = execvp(args[0], args);
        if (e < 0)
        {
            printf("\n");
            perror("");
        }
        exit(0);
    }
    else
    {
        k = waitpid(id, 0, WNOHANG);
        printf("%d\n", id);
        return id;
    }
}
void backhandler(int num)
{
    int *wstatus;
    int k;
    wstatus = &k;
    int id = waitpid(-1, wstatus, WNOHANG);
    if (id > 0)
    {
        // prompt(homepath);
        deletenodepid(id);
        if (WIFEXITED(*wstatus))
        {
            printf("\nprocess with pid %d exited normally\n", id);
            prompt(homepath);
            printf("\n");
        }
        else
        {
            printf("\nprocess with pid %d exited abnormally\n", id);
            prompt(homepath);
        }
    }
    return;
}